obj-m += spo_module.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: build

build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

load:
	insmod spo_module.ko

	if [ ! -e /dev/spo_driver_1 ]; then \
		mknod /dev/spo_driver_1 c $$(grep "spo_device" /proc/devices | awk '{print $$1}') 0; \
		chmod ugo+rw /dev/spo_driver_1; \
 	fi

unload:
	rmmod spo_module
	if [ -e /dev/spo_driver_1 ]; then \
		unlink /dev/spo_driver_1; \
	fi

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

run:
	cat /dev/spo_driver_1
	sudo dmesg

