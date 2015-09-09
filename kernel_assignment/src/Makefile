TARGET = numpagefaults.ko

CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m := numpagefaults.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.o numpagefaults.ko .*.cmd .*.flags *.mod.c
