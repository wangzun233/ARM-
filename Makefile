PROG=shell
BIN=$(PROG).bin
OBJS=main.o  uart.o bled.o cmd.o  iic.o mma8653.o itoa.o strcmp.o stack.o start.o  key_irq.o interrupt.o

CC=arm-cortex_a9-linux-gnueabi-gcc
LD=arm-cortex_a9-linux-gnueabi-ld
AS=arm-cortex_a9-linux-gnueabi-as
OBJCOPY=arm-cortex_a9-linux-gnueabi-objcopy

LDFLAGS=-nostartfiles -nostdlib -T shell.lds -e main
CFLAGS= -nostdlib

$(PROG):$(OBJS)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS)
	$(OBJCOPY) -O binary $(PROG) $(BIN)
	cp $(BIN)  /tftpboot/

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o:%.s
	$(AS) -o $@ $<

clean:
	rm -vf $(OBJS) $(PROG) $(BIN)
