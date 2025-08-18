#include "bcm.h"
#include "libpi.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define time 50

void pwm_start(float div) {
  // Habilita a PWM
  if (div <= 0 || div >= 4096) {
    div = DEFAULT_DIV; // Se divisor estiver fora dos 32 bits, usa o divisor
                       // padrão
  }

  uint32_t divi = (uint32_t)div;

  float frac_part = div - (float)divi;

  uint32_t divf =
      (uint32_t)(frac_part * 4096); // multiplica por 2¹² para tirar os 12
                                    // primeiros bits da parte fracionária

  // Mata o clock da PWM
  CM_PWM_REG(ctl) = CM_PWM_CTL_KILL | CM_PWM_PASSWORD;

  // Seta o divisor
  CM_PWM_REG(div) = CM_PWM_PASSWORD | (divi << 12) | divf;

  // Habilita clock da PWM com o oscillator como fonte
  CM_PWM_REG(ctl) = CM_PWM_CTL_ENABLE | CM_PWM_CTL_SRC_OSC | CM_PWM_PASSWORD;
}

void pwm_config(unsigned int channel, bool use_fifo, bool repeat_on_empty) {
  if (channel != 0 && channel != 1) {
    return;
  }

  uint32_t settings = 0;

  if (channel == 0) {
    // Sempre habilitar o canal (PWMEN1=bit 0) e o modo Mark/Space (MSEN1=bit 7)
    settings = (1 << 7) | (1 << 0);
    if (use_fifo) {
      settings |= (1 << 5); // Habilita USEF1 (bit 5)
      if (repeat_on_empty) {
        settings |= (1 << 2); // Habilita RPTL1 (bit 2)
      }
    }
  } else {
    // Sempre habilitar o canal (PWMEN2=bit 8) e o modo Mark/Space (MSEN2=bit
    // 15)
    settings = (1 << 15) | (1 << 8);
    if (use_fifo) {
      settings |= (1 << 13); // Habilita USEF2 (bit 13)
      if (repeat_on_empty) {
        settings |= (1 << 10); // Habilita RPTL2 (bit 10)
      }
    }
  }

  PWM_REG(ctl) |= settings;
}

void pwm_set_duty_cycle(unsigned channel, int range, int data) {
  if (channel != 0 && channel != 1) {
    return;
  }

  if (channel == 0) {
    PWM_REG(rng1) = range;
    PWM_REG(dat1) = data;

  } else {
    PWM_REG(rng2) = range;
    PWM_REG(dat2) = data;
  }
}

void pwm_set_polarity(int channel, int polarity) {
  if (channel != 0 && channel != 1) {
    return;
  }

  if (channel == 0) {
    PWM_REG(ctl) = (PWM_REG(ctl) & ~0b000100000) | (polarity << 4);
  } else {
    PWM_REG(ctl) = (PWM_REG(ctl) & ~0b0001000000000000) | (polarity << 12);
  }
}

void pwm_clear_queue(void) { PWM_REG(ctl) |= (1 << 6); }

int pwm_write_queue(uint32_t data) {
  if (pwm_full_queue()) {
    return -1;
  }

  PWM_REG(fif1) = data;

  return 0;
}

int pwm_full_queue() {
  if (PWM_REG(sta) & (1 << 0)) {
    return 1;
  } else {
    return 0;
  }
}
