CC := gcc
CFLAGS := -Wall -Wextra
SRC_DIR := src
BIN_DIR := bin
SRCS := $(wildcard $(SRC_DIR)/*.c)
PROGS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

all: $(PROGS)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

install:
	cp -r $(BIN_DIR)/* /usr/local/bin/

