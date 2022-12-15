obj-m := timedrv.o
KDIR := /root/linux-3.5
all:
	@make -C $(KDIR) M=$(PWD) modules	
	@rm -f *.o *.mod.o *.mod.c *.symvers *.markers *~ *.order
	
clean:
	@rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.markers *~ *_app *.order

