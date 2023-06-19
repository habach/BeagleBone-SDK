obj-m += misc_device.o


user=debian
board=192.168.7.2

PWD := $(shell pwd)
CROSS=/media/hicl/SSD-ext4/Documents/MySource/Embedded-Linux/BeagleBone/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KER_DIR=/media/hicl/SSD-ext4/Documents/MySource/Embedded-Linux/BeagleBone/kernelbuildscripts/KERNEL

all:
	echo "Building $(test)...\n"
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KER_DIR) M=$(PWD) modules	
	./copy-to-board.sh $(obj-m) "$(user)@$(board):/home/$(user)/"

clean:
	make -C $(KER_DIR) M=$(PWD) clean