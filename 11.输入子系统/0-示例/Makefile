KERN_DIR = /xydzz/kernel/linux-3.5 

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	arm-linux-gcc inputapp.c -o inputapp
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order  
obj-m += input_key.o


