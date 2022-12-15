KERN_DIR = /root/mybootloader/linux-3.5

all:
	make -C $(KERN_DIR) M=`pwd` modules
	@rm -f *.o *.mod.o *.mod.c *.symvers *.markers *~ *.order
	arm-linux-gcc usartapp.c
	cp *ko a.out /mjp/rootfs/ -f

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m += keydrv.o
obj-m += usart.o
obj-m +=led.o

