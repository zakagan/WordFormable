#~ WordFormable Makefile ~#

### Definitions Section ###

# Name of the executable to create
EXECUTABLE_1 = WordFormablePartials
EXECUTABLE_2 = WordFormableTable
EXECUTABLE_3 = WordFormablePowerPC
EXECUTABLE_4 = WordFormablePowerHP
EXECUTABLE_5 = WordFormableQueue
SOURCE_DIR = src
OBJECT_DIR = build

# The command to run for the C++ compiler (here used for C) and linker
CC = gcc

# Basic compiler arguments
CFLAGS = -g -c -Wall
	
# Basic linker arguments
LDFLAGS = -g

DEPENDENT_MAIN = main.c
INDEPENDENT_FILES:= $(filter-out $(SOURCE_DIR)/$(DEPENDENT_MAIN), $(wildcard $(SOURCE_DIR)/*.c))
INDEPENDENT_OBJ:= $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(INDEPENDENT_FILES))

METHOD_1_FLAG=PARTIALS
METHOD_2_FLAG=TABLE
METHOD_3_FLAG=POWERSTRING
METHOD_4_FLAG=POWERINTS
METHOD_5_FLAG=QUEUE


MAIN_1 := $(DEPENDENT_MAIN:.c=)_$(METHOD_1_FLAG).o
MAIN_2 := $(DEPENDENT_MAIN:.c=)_$(METHOD_2_FLAG).o
MAIN_3 := $(DEPENDENT_MAIN:.c=)_$(METHOD_3_FLAG).o
MAIN_4 := $(DEPENDENT_MAIN:.c=)_$(METHOD_4_FLAG).o
MAIN_5 := $(DEPENDENT_MAIN:.c=)_$(METHOD_5_FLAG).o

MAIN_OBJ:= $(MAIN_1) $(MAIN_2) $(MAIN_3) $(MAIN_4) $(MAIN_5)
MAIN_OBJ:= $(addprefix $(OBJECT_DIR)/,$(MAIN_OBJ))

METHOD_1_OBJ = $(MAIN_1) Parsing.o WordFormablePartials.o CheckWordByPartials.o WordSort.o
METHOD_2_OBJ = $(MAIN_2) Parsing.o WordFormableTable.o CharTable.o
METHOD_3_OBJ = $(MAIN_3) Parsing.o WordFormablePowerString.o HashMapString.o CommunicativeHashFunction.o SinglyLinkedList.o WordSort.o
METHOD_4_OBJ = $(MAIN_4) Parsing.o WordFormablePowerInts.o CheckWordByPartials.o HashMapInts.o CommunicativeHashFunction.o SinglyLinkedList.o WordSort.o
METHOD_5_OBJ = $(MAIN_5) Parsing.o WordFormableQueue.o DoublyLinkedList.o WordSort.o


METHOD_1_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_1_OBJ))
METHOD_2_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_2_OBJ))
METHOD_3_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_3_OBJ))
METHOD_4_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_4_OBJ))
METHOD_5_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_5_OBJ))

### Rules section
	
all: setup $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3) $(EXECUTABLE_4) $(EXECUTABLE_5)

print-%: ; @echo $*=$($*)

rebuild: clean all

setup: | $(OBJECT_DIR)	

$(OBJECT_DIR):                    # Create the object_files directory only if it does not exist. 
	mkdir -p $@	

$(INDEPENDENT_OBJ): $(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(OBJECT_DIR)/$(MAIN_1): MFLAG = $(METHOD_1_FLAG)
	
$(OBJECT_DIR)/$(MAIN_2): MFLAG = $(METHOD_2_FLAG)
	
$(OBJECT_DIR)/$(MAIN_3): MFLAG = $(METHOD_3_FLAG)
	
$(OBJECT_DIR)/$(MAIN_4): MFLAG = $(METHOD_4_FLAG)

$(OBJECT_DIR)/$(MAIN_5): MFLAG = $(METHOD_5_FLAG)

$(MAIN_OBJ): $(SOURCE_DIR)/$(DEPENDENT_MAIN)
	$(CC) -DUSE_$(MFLAG) $(CFLAGS) -o $@ $<

$(EXECUTABLE_1): $(METHOD_1_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

$(EXECUTABLE_2): $(METHOD_2_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

$(EXECUTABLE_3): $(METHOD_3_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

$(EXECUTABLE_4): $(METHOD_4_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

$(EXECUTABLE_5): $(METHOD_5_FILE)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR) $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3) $(EXECUTABLE_4) $(EXECUTABLE_5)


