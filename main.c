#include "bcm.h"
#include "libpi.h"

int main() {
  gpio_init(12, GPIO_FUNC_ALT0);
  gpio_init(13, GPIO_FUNC_ALT0);

  pwm_start(19.2); // Clock base

  pwm_set_duty_cycle(0, 1000000, 100000);
  pwm_set_duty_cycle(1, 1000000, 100000);

  pwm_config(0, false, false);
  pwm_config(1, false, false);

  int time = 2;
  while (1) {

    // ======= Trecho 1 =======
    pwm_set_duty_cycle(0, 1516, 379);
    delay(250000 * time); // E5
    pwm_set_duty_cycle(0, 1516, 189);
    delay(125000 * time); // E5 12.5%
    pwm_set_duty_cycle(0, 1516, 0);
    delay(125000 * time); // silêncio
    pwm_set_duty_cycle(0, 1516, 379);
    delay(250000 * time); // E5
    pwm_set_duty_cycle(0, 1516, 0);
    delay(125000 * time); // silêncio
    pwm_set_duty_cycle(0, 1911, 478);
    delay(250000 * time); // C5
    pwm_set_duty_cycle(0, 1516, 379);
    delay(250000 * time); // E5
    pwm_set_duty_cycle(0, 1275, 319);
    delay(500000 * time); // G5
    pwm_set_duty_cycle(0, 1516, 0);
    delay(250000 * time); // silêncio
    pwm_set_duty_cycle(0, 3822, 956);
    delay(250000 * time); // G4
    pwm_set_duty_cycle(0, 3822, 0);
    delay(125000 * time); // silêncio
    pwm_set_duty_cycle(0, 1911, 478);
    delay(250000 * time); // C5
    pwm_set_duty_cycle(0, 1911, 0);
    delay(125000 * time); // silêncio
    pwm_set_duty_cycle(0, 3822, 956);
    delay(250000 * time); // G4
    pwm_set_duty_cycle(0, 3822, 0);
    delay(125000 * time); // silêncio
    pwm_set_duty_cycle(0, 4545, 1136);
    delay(250000 * time); // E4
    pwm_set_duty_cycle(0, 3413, 853);
    delay(250000 * time); // A4
    pwm_set_duty_cycle(0, 3061, 765);
    delay(250000 * time); // B4
    pwm_set_duty_cycle(0, 3232, 161);
    delay(125000 * time); // Bb4 12.5%
    pwm_set_duty_cycle(0, 3413, 853);
    delay(500000 * time); // A4

    // ======= Trecho 2 =======
    // pwm_set_duty_cycle(0, 3822, 956); delay(250000*time); // G4
    // pwm_set_duty_cycle(0, 3232, 807); delay(250000*time); // F4
    // pwm_set_duty_cycle(0, 3030, 757); delay(250000*time); // E4
    // pwm_set_duty_cycle(0, 2863, 716); delay(250000*time); // D4
    // pwm_set_duty_cycle(0, 2863, 0);   delay(125000*time); // silêncio
    // pwm_set_duty_cycle(0, 2702, 675); delay(250000*time); // C4
    // pwm_set_duty_cycle(0, 2702, 0);   delay(125000*time); // silêncio

    // Subida
    // pwm_set_duty_cycle(0, 2863, 716); delay(125000*time); // D4
    // pwm_set_duty_cycle(0, 3030, 757); delay(125000*time); // E4
    // pwm_set_duty_cycle(0, 3232, 807); delay(125000*time); // F4
    // pwm_set_duty_cycle(0, 3413, 853); delay(125000*time); // A4
    // pwm_set_duty_cycle(0, 3822, 956); delay(125000*time); // G4
    // pwm_set_duty_cycle(0, 3030, 757); delay(125000*time); // E4
    // pwm_set_duty_cycle(0, 3822, 956); delay(250000*time); // G4
    // pwm_set_duty_cycle(0, 4545, 1136);delay(500000*time); // E4
  }

  return 0;
}
