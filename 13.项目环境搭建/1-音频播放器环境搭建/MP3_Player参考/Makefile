# Makefile 2.6
obj-m += mp3_button_driver.o

KDIR :=  /root/workspace/linux-2.6.32.2

all:
	make -C $(KDIR) M=$(PWD) modules
	arm-linux-gcc mp3_arm_app.c mp3_linklist.c mp3_play.c -o mp3_arm_app
	cp mp3_button_driver.ko mp3_arm_app /opt/s3c2440/root_nfs/home/ 

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.bak *.order *.pre *.bak
