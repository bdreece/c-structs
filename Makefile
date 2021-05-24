CC							:= gcc
FLAGS						:= -g -O2 -fPIC
CFLAGS					:= -std=c99 -Wall
IFLAGS					:= -I./inc

AR							:= ar rcs

BIN_DIR					:= ./bin
SRC_DIR					:= ./src
LIB_DIR					:= ./lib
DOCS_DIR				:= ./docs
DEMO_DIR				:= $(SRC_DIR)/demo

OBJS						= $(patsubst %.c, %.o, $(notdir $(wildcard $(SRC_DIR)/*.c)))
DEMO						= $(patsubst $(DEMO_DIR)/%_demo.c, ./bin/%_demo, $(wildcard $(DEMO_DIR)/*.c))

SHARED_LIB			:= $(LIB_DIR)/libstructures.so
STATIC_LIB			:= $(LIB_DIR)/libstructures.a

LIST_LIB				:= $(LIB_DIR)/liblist.a
LINKEDLIST_LIB  := $(LIB_DIR)/liblinkedlist.a
STACK_LIB				:= $(LIB_DIR)/libstack.a
QUEUE_LIB				:= $(LIB_DIR)/libqueue.a
HEAP_LIB				:= $(LIB_DIR)/libheap.a
MAP_LIB					:= $(LIB_DIR)/libmap.a
HASHMAP_LIB			:= $(LIB_DIR)/libhashmap.a

default: lib clean

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -c -o $@ $^

$(BIN_DIR)/%_demo: $(DEMO_DIR)/%_demo.c $(LIB_DIR)/lib%.a
	mkdir -p ./bin/
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -o $@ $^

$(STATIC_LIB): $(OBJS)
	mkdir -p ./lib/
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

all: lib demo docs clean

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: remove
remove: clean
	rm -rf $(BIN_DIR) $(LIB_DIR) $(DOCS_DIR)

.PHONY: lib
lib: $(STATIC_LIB) $(SHARED_LIB) $(LIST_LIB) $(LINKEDLIST_LIB) $(STACK_LIB) $(QUEUE_LIB) $(MAP_LIB) $(HASHMAP_LIB)

.PHONY: demo
demo: $(DEMO)

.PHONY: docs
docs:
	mkdir -p ./docs/
	doxygen
