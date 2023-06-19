obj-m += .o

PWD := $(shell pwd)
CROSS=/media/hicl/SSD-ext4/Documents/MySource/Embedded-Linux/BeagleBone/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KER_DIR=/media/hicl/SSD-ext4/Documents/MySource/Embedded-Linux/BeagleBone/kernelbuildscripts/KERNEL

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KER_DIR) M=$(PWD) modules

clean:
	make -C $(KER_DIR) M=$(PWD) clean