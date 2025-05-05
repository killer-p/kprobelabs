CC = arm-rockchip830-linux-uclibcgnueabihf-gcc

PROJECT_ROOT=$(CURDIR)/../

TARGET = kprobelabs
SRCS += main.c 
SRCS += units/kmalloc_user.c
SRCS += units/dump_backtrace_user.c
SRCS += units/poll_user.c

OBJS = $(SRCS:.c=.o)

INC_DIRS = $(PROJECT_ROOT)/app/include $(PROJECT_ROOT)/include
INC_FLAGS = $(foreach d, $(INC_DIRS), -I$d)

CFLAGS = -Wall -Wextra -g -O0 $(INC_FLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean