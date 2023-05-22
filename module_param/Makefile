obj-m = module_param.o
module_param-objs = hello-parameters.o hello-rwv-param.o

KERN_BUILD := /lib/modules/$(shell uname -r)/build
MODULE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

modules clean modules_install:
	make -C $(KERN_BUILD) M=$(MODULE_DIR) $@
