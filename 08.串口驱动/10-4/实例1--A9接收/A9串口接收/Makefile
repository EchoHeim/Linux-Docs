KER_DRI = /work/linux3.5/linux-3.5
all:
	#make -C $(KER_DRI) M=`pwd` modules
	arm-linux-gcc tiny4412_uart.c -o app
	cp ./app /work/nfs_root/work_code/
	#cp ./*.ko /work/nfs_root/work_code/
	#make -C $(KER_DRI) M=`pwd` modules clean
	rm ./app ./*.ko -rf
clean:
	#make -C $(KER_DRI) M=`pwd` modules clean

obj-m += touch_ft5x06_drv.o
obj-m += touch_ft5x06_dev.o