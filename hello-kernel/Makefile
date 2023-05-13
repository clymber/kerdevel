obj-m = hello-world.o

KERN_BUILD = /lib/modules/$(shell uname -r)/build
MODULE_DIR = $(PWD)

all:
	make -C $(KERN_BUILD) M=$(MODULE_DIR) modules

clean:
	make -C $(KERN_BUILD) M=$(MODULE_DIR) clean
