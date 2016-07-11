#~ WordPercent Makefile ~#

### Definitions Section ###

# Name of the executable to create
EXECUTABLE_1 = WordPercentSort
EXECUTABLE_2 = WordPercentTable
EXECUTABLE_3 = WordPercentPrecomputeSort
EXECUTABLE_4 = WordPercentPrecomputeInts
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

METHOD_1_FLAG=SORT
METHOD_2_FLAG=TABLE
METHOD_3_FLAG=POWERSTRING
METHOD_4_FLAG=POWERINTS

MAIN_1 := $(DEPENDENT_MAIN:.c=)_$(METHOD_1_FLAG).o
MAIN_2 := $(DEPENDENT_MAIN:.c=)_$(METHOD_2_FLAG).o
MAIN_3 := $(DEPENDENT_MAIN:.c=)_$(METHOD_3_FLAG).o
MAIN_4 := $(DEPENDENT_MAIN:.c=)_$(METHOD_4_FLAG).o

MAIN_OBJ:= $(MAIN_1) $(MAIN_2) $(MAIN_3) $(MAIN_4)
MAIN_OBJ:= $(addprefix $(OBJECT_DIR)/,$(MAIN_OBJ))

CORE_OBJ= Parsing.o
METHOD_1_OBJ = $(MAIN_1) $(CORE_OBJ) WordPercentSort.o WordSort.o CheckWordByPartials.o
METHOD_2_OBJ = $(MAIN_2) $(CORE_OBJ) WordPercentTable.o CharTable.o
METHOD_3_OBJ = $(MAIN_3) $(CORE_OBJ) WordPercentPowerString.o HashMapString.o CommunicativeHashFunction.o SinglyLinkedString.o WordSort.o
METHOD_4_OBJ = $(MAIN_4) $(CORE_OBJ) WordPercentPowerInts.o CheckWordByPartials.o HashMapInts.o CommunicativeHashFunction.o SinglyLinkedString.o WordSort.o

METHOD_1_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_1_OBJ))
METHOD_2_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_2_OBJ))
METHOD_3_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_3_OBJ))
METHOD_4_FILE = $(addprefix $(OBJECT_DIR)/, $(METHOD_4_OBJ))

### Rules section
	
all: setup $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3) $(EXECUTABLE_4)

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

.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR) $(EXECUTABLE_1) $(EXECUTABLE_2) $(EXECUTABLE_3) $(EXECUTABLE_4)


