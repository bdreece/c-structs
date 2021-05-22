CC		:= gcc
FLAGS		:= -g -O2 -fPIC
CFLAGS		:= -std=c99 -Wall
IFLAGS		:= -I./inc

AR		:= ar rcs

BIN_DIR		:= ./bin
SRC_DIR		:= ./src
LIB_DIR		:= ./lib
DEMO_DIR	:= $(SRC_DIR)/demo

OBJS		= $(patsubst %.c, %.o, $(notdir $(wildcard $(SRC_DIR)/*.c)))
DEMO		= $(patsubst %_demo.c, ./bin/%_demo, $(notdir $(wildcard $(DEMO_DIR)/*.c)))

SHARED_LIB	:= $(LIB_DIR)/lib_datastructures.so
STATIC_LIB	:= $(LIB_DIR)/lib_datastructures.a

LIST_LIB	:= $(LIB_DIR)/lib_list.a
LINKEDLIST_LIB	:= $(LIB_DIR)/lib_linkedlist.a
STACK_LIB	:= $(LIB_DIR)/lib_stack.a
QUEUE_LIB	:= $(LIB_DIR)/lib_queue.a
HEAP_LIB	:= $(LIB_DIR)/lib_heap.a
MAP_LIB		:= $(LIB_DIR)/lib_map.a
HASHMAP_LIB	:= $(LIB_DIR)/lib_hashmap.a

default: lib clean

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -c -o $@ $^

$(BIN_DIR)/%_demo: $(DEMO_DIR)/%_demo.c lib_%.a
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -o $@ $^

$(STATIC_LIB): $(OBJS)
	$(AR) $@ $^

$(SHARED_LIB): $(OBJS)
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) --shared -o $@ $^

$(LIST_LIB): list.o
	$(AR) $@ $^

$(LINKEDLIST_LIB): linkedlist.o
	$(AR) $@ $^

$(STACK_LIB): stack.o list.o
	$(AR) $@ $^

$(QUEUE_LIB): queue.o linkedlist.o
	$(AR) $@ $^

$(HEAP_LIB): heap.o list.o
	$(AR) $@ $^

$(MAP_LIB): map.o list.o
	$(AR) $@ $^

$(HASHMAP_LIB): hashmap.o map.o list.o
	$(AR) $@ $^

lib: $(STATIC_LIB) $(LIST_LIB) $(LINKEDLIST_LIB) $(STACK_LIB) $(QUEUE_LIB) $(MAP_LIB) $(HASHMAP_LIB) $(SHARED_LIB)

demo: $(DEMO)

all: lib demo clean

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: remove
remove: clean
	rm -f $(BIN_DIR)/* $(LIB_DIR)/*
