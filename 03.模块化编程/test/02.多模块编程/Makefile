KERN_DIR = /root/Desktop/tools/linux-3.5
all:
	make -C $(KERN_DIR) M=`pwd` modules
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order *o
obj-m += main.o
obj-m += fun.o






