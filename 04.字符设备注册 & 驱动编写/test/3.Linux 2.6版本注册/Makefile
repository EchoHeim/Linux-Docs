KERN_DIR = /root/Desktop/tools/linux-3.5
all:
	make -C $(KERN_DIR) M=`pwd` modules
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
obj-m += led_drv.o

