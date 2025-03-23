# 编译器
CC = arm-rockchip830-linux-uclibcgnueabihf-gcc

PROJECT_ROOT=$(CURDIR)/../

# 目标可执行文件
TARGET = kprobelabs
# 源文件
SRCS = main.c units/kmalloc_user.c

# 目标文件
OBJS = $(SRCS:.c=.o)


# 头文件路径
INC_DIRS = $(PROJECT_ROOT)/app/include $(PROJECT_ROOT)/include
# 将路径转换为-I选项
INC_FLAGS = $(foreach d, $(INC_DIRS), -I$d)

# 编译选项
CFLAGS = -Wall -Wextra -O2 $(INC_FLAGS)

# 默认目标
all: $(TARGET)

# 编译规则
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标
.PHONY: all clean