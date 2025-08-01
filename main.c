#include "libpi.h"

int main() {
  gpio_init(18, GPIO_FUNC_ALT5); // GPIO 12 como PWM0
  pwm_init(0); // Inicializa o PWM no canal 0
  pwm_set_duty_cycle(0, 5000000, 500000); // Define o duty cycle para 50% 
  while (1) {
  }

  return 0;
}
