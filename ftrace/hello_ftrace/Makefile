obj-m = hello_ftrace.o

KERN_BUILD := /lib/modules/$(shell uname -r)/build
MODULE_DIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST})))

modules modules_install clean:
	make -C ${KERN_BUILD} M=${MODULE_DIR} $@
