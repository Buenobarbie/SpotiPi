
#define GPIO_FUNC_INPUT 0
#define GPIO_FUNC_OUTPUT 1
#define GPIO_FUNC_ALT5 2
#define GPIO_FUNC_ALT4 3
#define GPIO_FUNC_ALT0 4
#define GPIO_FUNC_ALT1 5
#define GPIO_FUNC_ALT2 6
#define GPIO_FUNC_ALT3 7

#define GPIO_PULL_NONE 0
#define GPIO_PULL_DOWN 1
#define GPIO_PULL_UP 2

#define ARM_MODE_USER 0b10000
#define ARM_MODE_FIQ 0b10001
#define ARM_MODE_IRQ 0b10010
#define ARM_MODE_SVR 0b10011
#define ARM_MODE_MONITOR 0b10110
#define ARM_MODE_ABORT 0b10111
#define ARM_MODE_UNDEF 0b11011
#define ARM_MODE_HYPER 0b11010
#define ARM_MODE_SYSTEM 0b11111

#define DEFAUL_DIV 32
#define CM_PWM_PASSWORD 0x5A000000
#define CM_PWM_CTL_KILL 0x20
#define CM_PWM_CTL_ENABLE 0x10
#define CM_PWM_CTL_SRC_OSC 0x01

/***
 * delay
 * -- parâmetros: r0 (tempo)
 * -- retorno: -
 * Espera r0 loops vazios
 ***/
void delay(unsigned);

/***
 * get_arm_mode
 * -- parâmetros: -
 * -- retorno: r0 (modo atual ARM_MODE_....))
 * Lê o modo do processador no registrador cpsr
 ***/
unsigned get_arm_mode(void);

/***
 * set_arm_mode
 * -- parâmetros: r0 (modo desejado)
 * -- retorno -
 * Muda o modo do processador (ARM_MODE...)
 ***/
void set_arm_mode(unsigned);

/***
 * get_core
 * -- parâmetros: -
 * -- retorno r0 (Índice do núcleo atual (afinidade))
 * Identifica o núcleo (0 a 3) que está executando.
 ***/
unsigned get_core(void);

/***
 * enable_irq
 * -- parâmetros: r0 (booleano habilita ou desabilita)
 * -- retorno -
 * Habilita ou desabilita as interrupções normais (flag I).
 ***/
void enable_irq(unsigned);

/***
 * enable_fiq
 * -- parâmetros: r0 (booleano habilita ou desabilita)
 * -- retorno -
 * Habilita ou desabilita as interrupções rápidas.
 ***/
void enable_fiq(unsigned);

/***
 * gpio_init
 * -- parâmetros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (função desejada GPIO_FUNC_...)
 * -- retorno -
 * Configura um GPIO antes do uso.
 ***/
void gpio_init(unsigned, unsigned);

/***
 * gpio_put
 * -- parâmetros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (valor a escrever, 0 ou 1)
 * -- retorno -
 * Altera o valor de um GPIO configurado como saída
 ***/
void gpio_put(unsigned, unsigned);

/***
 * gpio_get
 * -- parâmetros: r0 (índice do GPIO, de 0 a 53)
 * -- retorno r0 (valor atual do GPIO)
 * Lê o estado atual de um GPIO
 ***/
unsigned gpio_get(unsigned);

/***
 * gpio_toggle
 * -- parâmetros: r0 (índice do GPIO, de 0 a 53)
 * -- retorno -
 * Alterna o estado de um GPIO configurado como saída.
 ***/
void gpio_toggle(unsigned);

/***
 * gpio_set_pulls
 * -- parâmetros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (configuração de pull-up (GPIO_PULL_...))
 * -- retorno -
 * Configura os resistores internos conectados a um GPIO.
 ***/
void gpio_set_pulls(unsigned, unsigned);

/***
 * uart_init
 * -- parâmetros: r0 (baudrate (por exemplo, 9600))
 * -- retorno -
 * Configura a uart antes de sua utilização.
 ***/
void uart_init(unsigned);

/***
 * uart_putc
 * -- parâmetros: r0 (caractere a enviar)
 * -- retorno -
 * Envia um byte através da uart
 ***/
void uart_putc(char);

/***
 * uart_puts
 * -- parâmetros: r0 (ponteiro para um string C)
 * -- retorno -
 * Envia um string terminado por zero através da uart.
 ***/
void uart_puts(char *);

/***
 * uart_getc
 * -- parâmetros: -
 * -- retorno Valor do caractere recebido
 * Lê um byte através da uart.
 ***/
char uart_getc(void);

/***
 * pwm_config
 * -- parâmetros: channel (canal PWM, 0 ou 1)
 * -- retorno -
 * Inicializa o periférico PWM no canal especificado.
 * Deve ser chamado antes de usar pwm_set_duty_cycle.
 ***/
void pwm_config(unsigned channel);

/***
 * pwm_set_duty_cycle
 * -- parâmetros: channel (canal PWM, 0 ou 1)
 * --            range (Período do PWM em ciclos)
 * --            data (Valor do duty cycle em ciclos, de 0 a range)
 * -- retorno -
 * Configura o duty cycle do canal PWM especificado.
 ***/
void pwm_set_duty_cycle(unsigned channel, int range, int data);


/***
 * pwm_start
 * -- parâmetros: div (divisor de clock, passar um inteiro ou 0 para usar o divisor padrão)
 * -- retorno -
 * Habilita o PWM para começar a gerar sinais.
 * Deve ser chamado após pwm_config e pwm_set_duty_cycle.
 ***/
void pwm_start(unsigned div);
