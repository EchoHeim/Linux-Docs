CC := arm-linux-gcc

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR :=  /root/Desktop/tools/linux-3.5

all:
	arm-linux-gcc font.c bmp.c main.c clock.c lcd_init.c lcd_api.c usart.c -o touch
	cp touch /hsl/rootfs
	cp 1.bmp HZK64 HZK48 HZK40 HZK32 HZK24 HZK16 /hsl/rootfs
clean:
	rm -f touch

