CC			= gcc
FLAGS		= -g -O2
CFLAGS	=

INC_PATH = ../inc
SRC_PATH = ../src



$(SRC_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_PATH) -c -o $@ $^

arraylist : $(SRC_PATH)/arraylist.o example_arraylist.c
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_PATH) -o $@ $^
