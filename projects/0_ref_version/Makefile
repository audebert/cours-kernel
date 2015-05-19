KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

obj-m := version.o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install
	depmod -a

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
