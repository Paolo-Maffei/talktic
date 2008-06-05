### Build options

## General options
PROJECT = talktic
MCU = atmega128
TARGET = $(PROJECT)

## Commands
CC = gcc
SIZE = size
OBJCOPY = objcopy
OBJDUMP = objdump
NM = nm
JSC = ../../jsc/jsc

## Source path
SRC_DIR = ../../src



### Build enviroment

## Options common to compile, link and assembly rules
COMMON =

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
#CFLAGS += -gstabs
#CFLAGS += -fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CFLAGS += -gdwarf-2
CFLAGS += -Wall -Os
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf-2

## Linker flags
LDFLAGS = $(COMMON)

## Include Directories
INCLUDES =

## Common Libraries
LIBDIRS =
LIBS = -lc

## Objects that must be built in order to link
OBJECTS = 		\
	main.o 		\
	bytecode.o	\
	b_globals.o	\
	$(NULL)

## Objects explicitly added by the user
LINKONLYOBJECTS = 



### JavaScript libraries

## Includes
INCLUDES += -I$(SRC_DIR)/js

## Objects
OBJECTS +=		\
	alloc.o		\
	debug.o		\
	heap.o		\
	object.o	\
	vm.o		\
	vmswt0.o	\
	utils.o		\
	b_core.o	\
	b_bool.o	\
	b_object.o	\
	b_func.o	\
	b_number.o	\
	b_array.o	\
	mrgsort.o	\
	b_string.o	\
	bc.o		\
	iostream.o	\
	iostream_file.o	\
	b_math.o	\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/js/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<



### Common

## Include
INCLUDES += -I$(SRC_DIR)

## Build
all: $(TARGET) size

## Compile
%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	$(JSC) -C$@ $<

##Link
$(PROJECT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@
size: $(PROJECT)
	$(SIZE) $<

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) $(PROJECT).map dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
