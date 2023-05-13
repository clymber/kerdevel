obj-m = module_param.o
module_param-objs = hello-parameters.o hello-rwv-param.o

KERN_BUILD = /lib/modules/$(shell uname -r)/build
MODULE_DIR = $(PWD)

modules clean:
	make -C $(KERN_BUILD) M=$(MODULE_DIR) $@
