KERN_DIR = /root/linux-3.5
all:
	make -C $(KERN_DIR) M=`pwd` modules
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order *o
obj-m += hellodrv1.o
obj-m += hellodrv2.o
