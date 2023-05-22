obj-m              = hello_api.o
hello_api-objs     = hello_api_inexit.o

KERN_BUILD := /lib/modules/$(shell uname -r)/build
MODULE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

modules modules_install clean:
	make -C $(KERN_BUILD) M=$(MODULE_DIR) $@

hello_api-objs += hello_api_test.o

obj-m += hello_feature.o
