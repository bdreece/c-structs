CC				:= gcc
FLAGS			:= -g -O2 -fPIC
CFLAGS		:= -std=c99 -Wall
IFLAGS		:= -I./inc/

AR				:= ar rcs

BIN_DIR		:= ./bin
SRC_DIR		:= ./src
LIB_DIR		:= ./lib
DEMO_DIR	= $(SRC_DIR)/demo

OBJS			= $(patsubst %.c, %.o, $(notdir $(wildcard $(SRC_DIR)/*.c)))
DEMO			= $(patsubst %_demo, %.c, $(wildcard $(DEMO_DIR)/*.c))

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -c -o $@ $^

$(BIN_DIR)/%_demo: $(DEMO_DIR)/%_demo.c %.o
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -o $@ $^

$(LIB_DIR)/lib_datastructures.a: $(OBJS)
	$(AR) $@ $^

$(LIB_DIR)/lib_datastructures.so: $(OBJS)
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) --shared $@ $^

lib: $(LIB_DIR)/lib_datastructures.a $(LIB_DIR)/lib_datastructures.so

all: lib $(DEMO) clean

default: $(OBJS) lib clean

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: remove
remove: clean
	rm -f $(BIN_DIR)/* $(LIB_DIR)/* list_demo linkedlist_demo
