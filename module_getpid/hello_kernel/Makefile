obj-m				= hello_getpid.o
hello_getpid-objs	= hello_initexit.o \
                      hello_module_param.o

BUILD	:= /lib/modules/$(shell uname -r)/build
MODDIR	:= $(abspath $(dir $(lastword ${MAKEFILE_LIST})))

modules modules_install clean:
	make -C ${BUILD} M=${MODDIR} ${@}
