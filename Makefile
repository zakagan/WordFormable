#~ WordPercent Makefile ~#


### Definitions Section ###

# Name of the executable to create
EXECUTABLE_1 = WordPercentSort
EXECUTABLE_2 = WordPercentTable
SOURCE_DIR = src
OBJECT_DIR= build

# The command to run for the C++ compiler (here used for C) and linker
CC = gcc

# Basic compiler arguments
CFLAGS = -g -c -Wall
	
# Basic linker arguments
LDFLAGS = -g
CORE_OBJ= WordPercentCore.o
METHOD_1_OBJ = WordSort.o
METHOD_2_OBJ = CharTable.o
CORE_FILE = $(addprefix $(OBJECT_DIR)/, $(CORE_OBJ))
METHOD_1_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_1_OBJ))
METHOD_2_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_2_OBJ))

# Create the object_files directory only if it does not exist. 
	
all: setup $(EXECUTABLE_1) $(EXECUTABLE_2)

rebuild: clean all

setup: | $(OBJECT_DIR)	

$(OBJECT_DIR):
	mkdir -p $@	

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(EXECUTABLE_1): $(CORE_FILE) $(METHOD_1_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

$(EXECUTABLE_2): $(CORE_FILE) $(METHOD_2_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR) $(EXECUTABLE_1) $(EXECUTABLE_2) 


