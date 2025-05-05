CROSS_COMPILE ?= arm-rockchip830-linux-uclibcgnueabihf-

SRCS := entry.c
SRCS += units/kmalloc_kernel.c
#SRCS += units/dump_backtrace_kernel.c
#SRCS += units/proc_kernel.c
#SRCS += units/poll_kernel.c

OBJS = $(SRCS:.c=.o)

kprobelabs-objs := $(OBJS)

obj-m += kprobelabs.o

KDIR = /home/prx/project/luckfox-pico/luckfox-pico/sysdrv/source/objs_kernel

all:
	+make -C $(KDIR) M=$(PWD)  ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	+make -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) clean