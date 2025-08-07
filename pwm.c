#include "bcm.h"
#include "libpi.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define time 50

void pwm_start(float div) {
  // Não é necessário zerar o PWM_REG antes
  // PWM_REG(ctl) = 0; // Zerar o pwm reg
  // delay(time);
  // Habilita o PWM
  if (div <= 0 || div >= 4096) {
    div = DEFAULT_DIV; // Se divisor for 0, usa o divisor padrão
  }

  uint32_t divi = (uint32_t)div;

  float frac_part = div - (float)divi;

  uint32_t divf =
      (uint32_t)(frac_part * 4096); // multiplica por 2¹² para tirar os 12
                                    // primeiros bits da parte fracionária

  // Kill PWM clock
  CM_PWM_REG(ctl) = CM_PWM_CTL_KILL | CM_PWM_PASSWORD;

  // Set divisor
  CM_PWM_REG(div) = CM_PWM_PASSWORD | (divi << 12) | divf;

  // Enable PWM clock with oscillator source
  // uint32_t temp = CM_PWM_CTL_ENABLE | CM_PWM_CTL_SRC_OSC | CM_PWM_PASSWORD;
  CM_PWM_REG(ctl) = CM_PWM_CTL_ENABLE | CM_PWM_CTL_SRC_OSC | CM_PWM_PASSWORD;
  // delay(time);

  // For debugging
  // uint32_t cm_pwm_ctl = CM_PWM_REG(ctl);
  uint32_t cm_pwm_div = CM_PWM_REG(div);

  // PWM_REG(ctl) = PWM_REG(ctl) | 0x1; ?
}

void pwm_config(unsigned int channel, bool use_fifo, bool repeat_on_empty) {
  if (channel != 0 && channel != 1) {
    return; // Apenas canais 0 e 1 são suportados
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
  } else { // channel == 1
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

  // Escreve a configuração final no registrador de controle.
  // O operador |= garante que não estamos desabilitando um canal ao configurar
  // o outro.
  PWM_REG(ctl) |= settings;

  // Configura o PWM_CTL para o canal especificado

  // Lê o valor atual: PWM_REG(ctl)
  // Limpa os 8 primeiros bits:  & ~0xFF
  // Seta os 8 primeiros bits como descrito acima: | 0x81

  // if (channel == 0) {
  //   PWM_REG(ctl) = (PWM_REG(ctl) & ~0xFF) | 0b10000001; // Configura PWM0
  //   //
  //   // Bit 0 (PWMEN1):     1 → Habilita o canal PWM 0
  //   // Bit 1 (MODE1):      0 → Modo PWM padrão (não serializer)
  //   // Bit 2 (RPTL1):      0 → Ignorado (só tem efeito se FIFO for usada, que
  //   // não será) Bit 3 (SBIT1):      0 → Sem uso (bit de silêncio), manter 0
  //   Bit
  //   // 4 (POLA1):      0 → Polaridade normal (nível alto durante pulso ativo)
  //   // Bit 5 (USEF1):      0 → FIFO não será usada
  //   // Bit 6 (CLRF):       0 → Não limpar FIFO (não usada, então manter 0)
  //   // Bit 7 (MSEN1):      0→ Utiliza o algorítmo explicitado na documentação
  //   1
  //   // → Habilita modo Mark-Space, algorítmo padrão de PWM
  //   //
  //   // Resultado final dos bits: 0b00000001 (0x81)
  // } else {
  //   //
  //   // Bit 8 (PWMEN2):      1 → Habilita o canal PWM 1
  //   // Bit 9 (MODE2):       0 → Modo PWM padrão (não serializer)
  //   // Bit 10 (RPTL2):      0 → Ignorado (só tem efeito se FIFO for usada,
  //   que
  //   // não será) Bit 11 (SBIT2):      0 → Sem uso (bit de silêncio), manter 0
  //   // Bit 12 (POLA2):      0 → Polaridade normal (nível alto durante pulso
  //   // ativo) Bit 13 (USEF2):      0 → FIFO não será usada Bit 14 (reserved):
  //   0
  //   // → Reservado, deixar como 0 Bit 15 (MSEN2):      0→ Utiliza o algorítmo
  //   // explicitado na documentação   1 → Habilita modo Mark-Space, algorítmo
  //   // padrão de PWM
  //   //
  //   // Resultado final dos bits: 0b10000001 00000000 (0x8100)
  //   PWM_REG(ctl) =
  //       (PWM_REG(ctl) & ~0xFF00) | (0b10000001 << 8); // Configura PWM1
  // }
}

void pwm_set_duty_cycle(unsigned channel, int range, int data) {
  if (channel != 0 && channel != 1) {
    return; // Apenas canais 0 e 1 são suportados
  }

  if (channel == 0) {
    PWM_REG(rng1) = range; // Define o intervalo do canal 0
    PWM_REG(dat1) = data;  // Define o valor de dados do canal 0

  } else {
    PWM_REG(rng2) = range; // Define o intervalo do canal 1
    PWM_REG(dat2) = data;  // Define o valor de dados do canal 1
  }
}

// PWM pin polarity
void pwm_set_polarity(int channel, int polarity) {
  if (channel != 0 && channel != 1) {
    return; // Apenas canais 0 e 1 são suportados
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
