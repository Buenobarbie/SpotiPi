#include "libpi.h"
#include "bcm.h"

int main() {
  gpio_init(13, GPIO_FUNC_ALT0); // GPIO 18 como PWM0
  // PWM_REG(ctl) = 0;
  pwm_config(1); // Configura o PWM no canal 0
  pwm_set_duty_cycle(1, 1000000, 500000); // Define o duty cycle para 50% 
  pwm_start(0); // Inicia o PWM com divisor 0 (padrão)
  while (1) {
    // gpio_put(13, 1);
    // delay(5000000); // Mantém o sinal alto por 500ms
    // gpio_put(13, 0);
    // delay(5000000); // Mantém o sinal baixo por 500ms
  }

  return 0;
}
