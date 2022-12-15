all: 
	arm-linux-gcc font_8x16.c main.c lcd_init.c lcd_api.c -o read
	cp read /hsl/rootfs
	cp test.txt HZK16 /hsl/rootfs
	@rm  -vf  *.o *~
clean:
	@rm  -vf  *_app *.o *~
