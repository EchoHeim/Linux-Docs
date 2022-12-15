#X86平台测试使用 make EXTRA_CFLAGS+=-DPLATX86 编译，arm平台测试使用make编译
#CFLAGS += -D PLATX86
#EXTRA_CFLAGS += -D PLATX86   //可以用来给编译内核文件时候给C文件传递全局宏定义
CC := arm-linux-gcc

# Makefile 2.6
ifneq ($(KERNELRELEASE),)
obj-m += i2c_device.o
obj-m += i2c_driver.o
else

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR :=  /root/Desktop/tools/linux-3.5

all:
	make  -C $(KDIR) M=$(PWD)  modules 
	rm -rf .*.cmd *.o *.mod.o *.mod.c *.symvers *.cmd *.bak *.order *.unsigned .tmp_versions
	arm-linux-gcc touch_app.c -o touch
	cp *ko touch /hsl/rootfs -f
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.cmd *.bak *.order

endif
