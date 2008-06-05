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
JSC = ../../jsc/jsc

## Testing enviroment
TEST_COMPORT = com6

## Source path
SRC_DIR = ../../src

## ecos Options
ECOS_REPOSITORY = ecos_cvshead/packages
ECOS_DIR = ecos

## Build options
NET = 1
#DNS = 1

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
	b_globals.o	\
	b_hello.o	\
	$(NULL)

## Objects explicitly added by the user
LINKONLYOBJECTS =



### aki3086net ext libraries

## C macro flags
CFLAGS += -D_AKI3068NET

## Includes
INCLUDES += -I$(SRC_DIR)/aki3068net

## Objects
OBJECTS += 		\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/aki3068net/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<

## Libraries
ifdef NET
CFLAGS += -D_AKI3068NET_NET
OBJECTS += b_net.o base64.o
endif # NET

ifdef DNS
INCLUDES += -I$(SRC_DIR)/aki3068net/ares
CFLAGS += -D_AKI3068NET_DNS
OBJECTS +=		\
	ares__close_sockets.o	\
	ares_compat.o	\
	ares_destroy.o	\
	ares_expand_name.o	\
	ares_fds.o	\
	ares_free_errmem.o	\
	ares_free_hostent.o	\
	ares_free_string.o	\
	ares_gethostbyaddr.o	\
	ares_gethostbyname.o	\
	ares_init.o	\
	ares_mkquery.o	\
	ares_parse_a_reply.o	\
	ares_parse_ptr_reply.o	\
	ares_process.o	\
	ares_query.o	\
	ares_search.o	\
	ares_send.o	\
	ares_strerror.o	\
	ares_timeout.o	\
	$(NULL)
%.o: $(SRC_DIR)/aki3068net/ares/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
endif # DNS



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
	b_math.o	\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/js/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<



### Common

## Includes
INCLUDES += -I$(SRC_DIR)

## Build
all: $(TARGET) size
	echo $(OBJECTS)

## Compile
%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	$(JSC) -C$@ $<

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

## Testing target
test: console
init_console:
	mode.com $(TEST_COMPORT): BAUD=38400 PARITY=N DATA=8 STOP=1
console: init_console
	cat /dev/$(TEST_COMPORT)

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
