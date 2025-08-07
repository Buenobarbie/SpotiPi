#include "bcm.h"
#include "libpi.h"

int main() {
  // gpio_init(18, GPIO_FUNC_ALT5); //
  gpio_init(12, GPIO_FUNC_ALT0); //
  gpio_init(13, GPIO_FUNC_ALT0); //

  pwm_start(19.2); // Inicia o PWM com divisor 0 (padrão)
  // Ordem não importa
  pwm_set_duty_cycle(0, 1000000, 100000); // Define o duty cycle para 50%
  pwm_set_duty_cycle(1, 1000000, 100000); // Define o duty cycle para 50%
  pwm_config(0);                          // Configura o PWM no canal 0
  pwm_config(1);                          // Configura o PWM no canal 0
  while (1) {
    // gpio_put(13, 1);
    // delay(5000000); // Mantém o sinal alto por 500ms
    // gpio_put(13, 0);
    // delay(5000000); // Mantém o sinal baixo por 500ms
  }

  return 0;
}
