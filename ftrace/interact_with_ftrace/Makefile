TARGETS=$(subst .c,.exe,$(wildcard *.c))

.PHONY: all
all: ${TARGETS}

.PHONY: clean
clean:
	rm ${TARGETS}

%.exe: %.c
	gcc -Wall $^ -o $@
 