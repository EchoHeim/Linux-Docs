all: 
	arm-linux-gcc font_8x16.c main.c lcd_init.c lcd_api.c -o lcd_app
	cp lcd_app /hsl/rootfs
	cp *.bmp HZK16 /hsl/rootfs
	@rm  -vf  *.o *~
clean:
	@rm  -vf  *_app *.o *~
