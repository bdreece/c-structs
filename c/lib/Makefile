CC			= gcc
AR			= ar
FLAGS		= -g -O2
CFLAGS	=

INC_PATH = ../inc
SRC_PATH = ../src

%.o : %.c
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_PATH) -fPIC -c -o $@ $^
