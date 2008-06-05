## General Options
PROJECT = talktic
TARGET = $(PROJECT).exe
CC = gcc.exe
SIZE = size.exe
OBJCOPY = objcopy.exe
OBJDUMP = objdump.exe
SRC_DIR = ../../src

## Options common to compile, link and assembly rules
COMMON =

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -Os -fsigned-char -gstabs
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map

## Include Directories
INCLUDES = -I$(SRC_DIR)

## Libraries
LIBDIRS =
LIBS = -lc

## Objects that must be built in order to link
MAIN_OBJECTS = 	\
	main.o 		\
	$(NULL)

JS_OBJCETS =	\
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
JS_OBJCETS += debug.o
OBJECTS = $(MAIN_OBJECTS) $(JS_OBJCETS) $(BOOTLOADER_OBJECTS)

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) size

## Compile
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	cd ../bytecodeh && $(MAKE)

##Link
%.exe: $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@
%.lss: %.exe
	$(OBJDUMP) -h -S $< > $@
size: $(PROJECT).exe
	 $(SIZE) -A $<

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) $(PROJECT).map dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

