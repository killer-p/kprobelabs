CROSS_COMPILE ?= arm-rockchip830-linux-uclibcgnueabihf-

kprobelabs-objs := entry.o
kprobelabs-objs += units/kmalloc_kernel.o
kprobelabs-objs += units/dump_backtrace_kernel.o

obj-m += kprobelabs.o

KDIR ?= /home/prx/project/luckfox-pico/luckfox-pico/sysdrv/source/kernel

all:
	+make -C $(KDIR) M=$(PWD)  ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	+make -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) clean