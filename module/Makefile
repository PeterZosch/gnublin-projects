obj-m += irmod.o

KDIR := /usr/src/linux-2.6.33-lpc313x/

.PHONY: all clean

all:

	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean
