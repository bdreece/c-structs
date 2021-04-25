CC			= gcc
FLAGS		= -g -O2
CFLAGS	=

INC_PATH = ../inc
SRC_PATH = ../src

%.o : %.c
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_PATH) -c -o $@ $^

example_arraylist : $(SRC_PATH)/arraylist.o example_arraylist.o
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $^
