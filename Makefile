CC			:= gcc
FLAGS		:= -g -O2 -fPIC
CFLAGS		:= -std=c99 -Wall
IFLAGS		:= -I./inc

AR			:= ar rcs

BIN_DIR		:= ./bin
SRC_DIR		:= ./src
LIB_DIR		:= ./lib
DOCS_DIR	:= ./docs
DEMO_DIR	:= $(SRC_DIR)/demo

OBJS		:= $(patsubst %.c, %.o, $(notdir $(wildcard $(SRC_DIR)/*.c)))
DEMO		:= $(patsubst $(DEMO_DIR)/%_demo.c, ./bin/%_demo, $(wildcard $(DEMO_DIR)/*.c))

SHARED_LIB	:= $(LIB_DIR)/libstructures.so
STATIC_LIB	:= $(LIB_DIR)/libstructures.a

default: lib clean

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -c -o $@ $^

$(BIN_DIR)/%_demo: $(DEMO_DIR)/%_demo.c $(LIB_DIR)/libstructures.a
	mkdir -p ./bin/
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) -o $@ $^

$(STATIC_LIB): $(OBJS)
	mkdir -p ./lib/
	$(AR) $@ $^

$(SHARED_LIB): $(OBJS)
	mkdir -p ./lib/
	$(CC) $(FLAGS) $(CFLAGS) $(IFLAGS) --shared -o $@ $^

all: lib docs clean

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: remove
remove: clean
	rm -rf $(BIN_DIR) $(LIB_DIR) $(DOCS_DIR)

.PHONY: lib
lib: $(STATIC_LIB) $(SHARED_LIB)

.PHONY: demo
demo: $(DEMO)

.PHONY: docs
docs:
	mkdir -p ./docs/
	doxygen
