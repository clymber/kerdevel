TARGET := "user_get_pid.exe"

# Custom Command
GCC:= gcc
RM := rm -f

# Custom Options and Flags
OUTPUT_OPTION = -o $@
CFLAGS        += -Wall
CPPFLAGS      +=
LDFLAGS       +=

# Depended Library that Already Existed
# LDLIBS := -lgmock

# File lists
sources := $(wildcard *.c)
objects := $(subst .c,.o,${sources})
depends = $(wildcard $(subst .o,.d,$(objects)))

# Makefile targets
.PHONY: all clean distclean
all: $(TARGET)

clean:
	$(RM) $(objects) $(depends)

distclean: clean
	$(RM) $(TARGET)

$(TARGET): $(objects)
	$(GCC) $(OUTPUT_OPTION) $(TARGET_ARCH) $^ $(LDFLAGS) $(LDLIBS) $(LOADLIBES)

$(eval $(if $(filter $(MAKECMDGOALS),clean distclean),,include $(depends)))

# Makefile rules
%.o: %.c
	$(GCC) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP -MT $@ -MF $(subst .o,.d,$@) $<
	$(GCC) $(CPPFLAGS) $(CFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c $<