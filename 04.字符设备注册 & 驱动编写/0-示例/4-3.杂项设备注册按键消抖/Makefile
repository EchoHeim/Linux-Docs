KERN_DIR = /root/linux-3.5 

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	arm-linux-gcc mykeyapp.c -o mykeyapp

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m += mykeydrv.o

