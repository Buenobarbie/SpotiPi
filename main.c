#include "bcm.h"
#include "libpi.h"

int main() {
  gpio_init(12, GPIO_FUNC_ALT0);
  gpio_init(13, GPIO_FUNC_ALT0);

  pwm_start(19.2); // Inicia o PWM com divisor 19.2

  pwm_set_duty_cycle(0, 1000000, 100000); // DATA aqui é INUTIL para a FIFO
  pwm_set_duty_cycle(1, 1000000, 100000);

  pwm_config(0, false, false); // Configura o PWM no canal 0
  pwm_config(1, false, false); // Configura o PWM no canal 0

  pwm_set_polarity(1, 1);
  while (1) {
  }

  return 0;
}
