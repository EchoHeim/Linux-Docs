KERN_DIR = /root/Desktop/tools/linux-3.5
all:
	make -C $(KERN_DIR) M=`pwd` modules
	arm-linux-gcc app.c
	cp *ko a.out /hsl/rootfs/ -f
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
	rm a.out -f
obj-m += key_drv.o
