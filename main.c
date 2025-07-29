#include "pi.h"

int main() {
  gpio_init(23, GPIO_FUNC_OUTPUT);
  while (1) {
    gpio_put(23, 0);
    delay(5000000); // 5000000 = 2 segundos
    gpio_put(23, 1);
    delay(5000000);
  }

  return 0;
}
