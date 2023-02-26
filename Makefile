CC = gcc
FLAGS = -Wall -O2
TARGET = test
SRCS = main.c register.c library.c instruction.c alu.c branch.c fpu.c grad_list.c read.c WB.c EX.c RF.c IF.c driver.c memory.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): $(SRCS)
	$(CC) $(FLAGS) -c $(SRCS)

all: clean $(OBJS) $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)