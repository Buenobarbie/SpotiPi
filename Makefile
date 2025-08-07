FONTES = pwm.c gpio.c uart.c asm.s main.c boot.s
RPICPU = bcm2836

ifeq (${RPICPU}, bcm2836)
	# Raspberry Pi v.2 ou v.3
	ASMOPTIONS = -g --defsym RPICPU=2
	COPTIONS = -march=armv7-a -mtune=cortex-a7 -g -D RPICPU=2
else
	ifeq (${RPICPU}, bcm2835)
  		# Raspberry Pi v.0 ou v.1
   	ASMOPTIONS = -march=armv6zk -g --defsym RPICPU=0
   	COPTIONS = -march=armv6zk -mtune=arm1176jzf-s -g -D RPICPU=0
	endif
endif

TTY = /dev/ttyUSB1

ALVO = main

OCD_CFG = jtag.cfg

#
# Arquivos de saída 
#
EXEC = ${ALVO}.elf
MAP = ${ALVO}.map
IMAGE = ${ALVO}.img
HEXFILE = ${ALVO}.hex
LIST = ${ALVO}.list
OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

PREFIXO = arm-none-eabi-
LDSCRIPT = linker.ld
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump
ifeq (${RPICPU}, bcm2836)
	# Raspberry Pi v.2 ou v.3
	ASMOPTIONS = -g --defsym RPICPU=2
	COPTIONS = -march=armv7-a -mtune=cortex-a7 -g -D RPICPU=2
else
	ifeq (${RPICPU}, bcm2835)
  		# Raspberry Pi v.0 ou v.1
   	ASMOPTIONS = -march=armv6zk -g --defsym RPICPU=0
   	COPTIONS = -march=armv6zk -mtune=arm1176jzf-s -g -D RPICPU=0
	endif
endif

OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

OPTS = -march=armv7-a -mtune=cortex-a7
LDOPTS = -lgcc -L/usr/lib/gcc/arm-none-eabi/15.1.0/

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

rebuild: clean all

#
# Gerar executável
#
${EXEC}: ${OBJETOS}
	${LD} -T ${LDSCRIPT} -M=${MAP} ${OBJETOS} ${LDOPTS} -o $@

#
# Gerar imagem
#
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}

#
# Gerar intel Hex
#
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

#
# Gerar listagem
#
${LIST}: ${EXEC}
	${OBJDMP} -std ${EXEC} > ${LIST}

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${COPTIONS} -c -o $@ $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} ${ASMOPTIONS} -o $@ $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE}


#
# Gdb via serial
#
gdb: ${EXEC}
	@if pgrep openocd >/dev/null; then \
		gdb ${EXEC} \
			-ex "target extended-remote: 3333" \
			-ex "load"; \
		else gdb -b 115200 ${EXEC} \
		                -ex "target remote ${TTY}" \
	                   -ex "load"; \
	fi

