#~ WordPercent Makefile ~#


### Definitions Section ###

# Name of the executable to create
EXECUTABLE_1 = WordPercentSort
EXECUTABLE_2 = WordPercentTable
EXECUTABLE_3 = WordPercentPrecompute
SOURCE_DIR = src
OBJECT_DIR= build

# The command to run for the C++ compiler (here used for C) and linker
CC = gcc

# Basic compiler arguments
CFLAGS = -g -c -Wall
	
# Basic linker arguments
LDFLAGS = -g

CORE_OBJ= Parsing.o
METHOD_1_OBJ = WordPercentSort.o WordSort.o 
METHOD_2_OBJ = WordPercentTable.o CharTable.o
METHOD_3_OBJ = WordPercentPowerSet.o HashMap.o SinglyLinkedList.o CharTable.o
CORE_FILE = $(addprefix $(OBJECT_DIR)/, $(CORE_OBJ))
METHOD_1_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_1_OBJ))
METHOD_2_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_2_OBJ))
METHOD_3_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_3_OBJ))


# Create the object_files directory only if it does not exist. 
	
all: setup $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3)

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

$(EXECUTABLE_3): $(CORE_FILE) $(METHOD_3_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR) $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3)


