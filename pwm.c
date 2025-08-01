#include "bcm.h"
#include <stdint.h>
#include <stdlib.h>




void pwm_init(unsigned channel) {
  if (channel != 0 && channel != 1) {
    return; // Apenas canais 0 e 1 são suportados
  }

  // Configura o PWM_CTL para o canal especificado

  // Lê o valor atual: PWM_REG(ctl)
  // Limpa os 8 primeiros bits:  & ~0xFF
  // Seta os 8 primeiros bits como descrito acima: | 0x81
  if (channel == 0) {
    PWM_REG(ctl) = (PWM_REG(ctl) & ~0xFF) | 0x80; // Configura PWM0
    // 
    // Bit 0 (PWMEN1):     1 → Habilita o canal PWM 0
    // Bit 1 (MODE1):      0 → Modo PWM padrão (não serializer)
    // Bit 2 (RPTL1):      0 → Ignorado (só tem efeito se FIFO for usada, que não será)
    // Bit 3 (SBIT1):      0 → Sem uso (bit de silêncio), manter 0
    // Bit 4 (POLA1):      0 → Polaridade normal (nível alto durante pulso ativo)
    // Bit 5 (USEF1):      0 → FIFO não será usada
    // Bit 6 (CLRF):       0 → Não limpar FIFO (não usada, então manter 0)
    // Bit 7 (MSEN1):      0 → Habilita modo Mark-Space (recomendado para controle preciso de duty cycle)
    //
    // Resultado final dos bits: 0b10000001 (0x81)
  } else {
    // 
    // Bit 8 (PWMEN2):      1 → Habilita o canal PWM 1
    // Bit 9 (MODE2):       0 → Modo PWM padrão (não serializer)
    // Bit 10 (RPTL2):      0 → Ignorado (só tem efeito se FIFO for usada, que não será)
    // Bit 11 (SBIT2):      0 → Sem uso (bit de silêncio), manter 0
    // Bit 12 (POLA2):      0 → Polaridade normal (nível alto durante pulso ativo)
    // Bit 13 (USEF2):      0 → FIFO não será usada
    // Bit 14 (reserved):   0 → Reservado, deixar como 0
    // Bit 15 (MSEN2):      0 → Habilita modo Mark-Space (recomendado para controle preciso de duty cycle)
    //
    // Resultado final dos bits: 0b10000001 00000000 (0x8100)
    PWM_REG(ctl) = (PWM_REG(ctl) & ~0xFF00) | 0x8000; // Configura PWM1
  }
}

  void pwm_set_duty_cycle(unsigned channel, int range, int data){
    if (channel != 0 && channel != 1) {
        return; // Apenas canais 0 e 1 são suportados
    }

    if(channel == 0) {
        PWM_REG(rng1) = range; // Define o intervalo do canal 0
        PWM_REG(dat1) = data;  // Define o valor de dados do canal 0
        unsigned range = PWM_REG(rng2);
        unsigned data = PWM_REG(dat2);
        while(1){

        }
    } else {
        PWM_REG(rng2) = range; // Define o intervalo do canal 1
        PWM_REG(dat2) = data;  // Define o valor de dados do canal 1
    }
  



}