# Redboot load command
# load -r -v -b 0x400000 -h 192.168.1.11 -m tftp main.bin

### Build options

## General options
PROJECT = talktic
TARGET = $(PROJECT).elf $(PROJECT).bin

## Commands
CC = h8300-elf-gcc
SIZE = h8300-elf-size
OBJCOPY = h8300-elf-objcopy
ECOS_CONFIG = ecosconfig

## Source path
SRC_DIR = ../../src

## ecos Options
ECOS_REPOSITORY = ecos_cvshead/packages
ECOS_DIR = ecos



### Build enviroment

## Options common to compile, link and assembly rules
COMMON = -mh -mint32 -mrelax

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Os -Wall
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Ttarget.ld -nostdlib

## Include Directories
INCLUDES = -I$(ECOS_DIR)/install/include

## Libraries
LIBDIRS = -L$(ECOS_DIR)/install/lib
LIBS =

## Objects that must be built in order to link
OBJECTS = 		\
	main.o 		\
	bytecode.o	\
	b_hello.o	\
	$(NULL)

## Objects explicitly added by the user
LINKONLYOBJECTS =



### JavaScript libraries

## Includes
INCLUDES += -I$(SRC_DIR)/js

## Objects
OBJECTS +=		\
	alloc.o		\
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
	$(NULL)

## Compile
%.o: $(SRC_DIR)/js/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<



### aki3086net ext libraries

## Includes
INCLUDES += -I$(SRC_DIR)/aki3068net

## Objects
OBJECTS += 		\
	net.o		\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/aki3068net/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<



### Common

## Includes
INCLUDES += -I$(SRC_DIR)

## Build
all: $(TARGET) size
	echo $(OBJECTS)

## Compile
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	cd ../bytecodeh && $(MAKE)

## ecos configure
ecostree: $(ECOS_DIR)/ecos.ecc
	cd $(ECOS_DIR); ../$(ECOS_CONFIG) --srcdir="`cd ../$(ECOS_REPOSITORY); pwd`" tree

## Link
%.elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
size: $(PROJECT).elf
	$(SIZE) -A $<

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
