obj-m += blinking_led_timer.o

user=debian
board_ip=192.168.7.2
SOURCE_DIR=/media/hicl/SSD-ext4/Documents/MySource/Embedded-Linux/BeagleBone

PWD := $(shell pwd)
CROSS=$(SOURCE_DIR)/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KER_DIR=$(SOURCE_DIR)/kernelbuildscripts/KERNEL

all:
	echo "Building $(test)...\n"
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KER_DIR) M=$(PWD) modules	
	./copy-to-board.sh $(obj-m) "$(user)@$(board_ip):/home/$(user)/"

clean:
	make -C $(KER_DIR) M=$(PWD) clean