# Redboot load command
# load -r -v -b 0x400000 -h 192.168.1.11 -m tftp main.bin

## General Options
PROJECT = talktic
TARGET = $(PROJECT).elf $(PROJECT).bin
CC = h8300-elf-gcc
SIZE = h8300-elf-size
OBJCOPY = h8300-elf-objcopy
SRC_DIR = ../../src

## ecos Options
#ECOS_CONFIG = ecosconfig.exe
#ECOS_REPOSITORY = ecos_cvshead
ECOS_DIR = ecos

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
INCLUDES += -I$(SRC_DIR)

## Libraries
LIBDIRS = -L$(ECOS_DIR)/install/lib
LIBS =

## Objects that must be built in order to link
MAIN_OBJECTS = 	\
	main.o 		\
	$(NULL)
# MAIN_OBJECTS += js_class.o 
JS_OBJECTS =	\
	alloc.o		\
	b_array.o	\
	b_bool.o	\
	b_core.o	\
	b_func.o	\
	b_number.o	\
	b_object.o	\
	b_string.o	\
	bc.o		\
	debug.o		\
	heap.o		\
	iostream.o	\
	mrgsort.o	\
	object.o	\
	utils.o		\
	vm.o		\
	vmswt0.o	\
	$(NULL)
OBJECTS = $(MAIN_OBJECTS) $(JS_OBJECTS)

## Objects explicitly added by the user
LINKONLYOBJECTS =

## Build
all: $(TARGET) size
# not works well
#ecosconfig: $(ECOS_DIR)/ecos.ecc
#	cd $(ECOS_DIR) && ../$(ECOS_CONFIG) --srcdir=../$(ECOS_REPOSITORY)/packages tree

## Compile
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	cd ../bytecodeh && $(MAKE)

##Link
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

