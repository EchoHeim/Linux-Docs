KERN_DIR =/rec/kernel/linux-3.5

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m   += leddev.o
obj-m   += leddrv.o
