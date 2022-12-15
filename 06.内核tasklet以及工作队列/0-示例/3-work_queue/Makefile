obj-m := hello.o
	
#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /whz/linux/linux-3.5
all:
	@make -C $(KDIR) M=$(PWD) modules	
	@rm -f *.o *.mod.o *.mod.c *.symvers *.markers *~ *.order
	
clean:
	@rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.markers *~ *_app *.order

