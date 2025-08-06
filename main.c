#include "libpi.h"
#include "bcm.h"

int main() {
  // gpio_init(18, GPIO_FUNC_ALT5); // 
  gpio_init(12, GPIO_FUNC_ALT0); // 

  // Ordem não importa
  pwm_config(0); // Configura o PWM no canal 0
  pwm_set_duty_cycle(0, 1000000, 100000); // Define o duty cycle para 50% 
  pwm_start(10); // Inicia o PWM com divisor 0 (padrão)
  while (1) {
    // gpio_put(13, 1);
    // delay(5000000); // Mantém o sinal alto por 500ms
    // gpio_put(13, 0);
    // delay(5000000); // Mantém o sinal baixo por 500ms
  }

  return 0;
}
