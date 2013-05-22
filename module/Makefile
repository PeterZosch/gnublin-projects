
ARCH		?= arm
CROSS_COMPILE	?= arm-linux-gnueabi-
export ARCH CROSS_COMPILE

obj-m += gpio-mod.o

KDIR := /home/theito/tmp/lib/modules/2.6.33-rt8-g3b80ac1/build

KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)
all: modules

$(KBUILD_TARGETS):
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
