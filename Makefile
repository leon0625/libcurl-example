# by chat gpt

# 获取当前目录中所有的.c文件
SRCS := $(wildcard *.c)

# 从.c文件生成对应的可执行程序
PROGS := $(patsubst %.c,%,$(SRCS))

# 编译器和编译选项
CC := gcc
LDFLAGS := -lcurl

# 默认目标：编译所有的可执行程序
all: $(PROGS)

# 生成可执行程序的规则
%: %.c
	$(CC) -o $@ $< $(LDFLAGS)

# 清理生成的文件
clean:
	rm -f $(PROGS)
