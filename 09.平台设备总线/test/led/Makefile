KERN_DIR =/root/Desktop/tools/linux-3.5

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	arm-linux-gcc ledapp.c
	cp *.ko /hsl/rootfs -f
	cp a.out /hsl/rootfs -f
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m   += leddev.o
obj-m   += leddri.o
