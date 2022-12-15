CC := arm-linux-gcc

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR :=  /root/Desktop/tools/linux-3.5

all:
	arm-linux-gcc font_8x16.c bmp.c main.c lcd_init.c lcd_api.c -o touch
	cp touch /hsl/rootfs
	cp 1.bmp HZK16 /hsl/rootfs
clean:
	rm -f touch

