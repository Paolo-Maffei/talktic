## General Options
PROJECT = talktic
MCU = atmega128
TARGET = $(PROJECT).elf $(PROJECT).cof $(PROJECT).hex $(PROJECT).eep
CC = avr-gcc.exe
SIZE = avr-size.exe
OBJCOPY = avr-objcopy.exe
OBJDUMP = avr-objdump.exe
SRC_DIR = ../../src

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -Os -fsigned-char  -gstabs
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

# CFLAGS += -D_MOXA
# CFLAGS += -D_MOXA_SERIAL
# CFLAGS += -D_MOXA_RADIO

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x8090FF
LDFLAGS += -Wl,-Map=$(PROJECT).map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0

## Include Directories
INCLUDES = -I$(SRC_DIR)

## Libraries
LIBDIRS =
LIBS = -lc

## Objects that must be built in order to link
MAIN_OBJECTS = 	\
	main.o 		\
	$(NULL)
# MAIN_OBJECTS += serial.o              # _MOXA_SERIAL
# MAIN_OBJECTS += radio.o chip_cc2420.o # _MOXA_RADIO
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
OBJECTS = $(MAIN_OBJECTS) $(JS_OBJCETS) $(BOOTLOADER_OBJECTS)

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) size

## Compile
chip_cc2420.o: $(SRC_DIR)/chip_cc2420.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -O0 -c $<
%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h $(SRC_DIR)/bytecode.h
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<
$(SRC_DIR)/bytecode.h: $(SRC_DIR)/bytecode.js
	cd ../bytecodeh && $(MAKE)

##Link
%.elf: $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@
%.cof: %.elf 
	$(OBJCOPY) --debugging -O coff-ext-avr $< $@
%.hex: %.elf
	$(OBJCOPY) -O ihex $(HEX_FLASH_FLAGS)  $< $@
%.eep: %.elf
	$(OBJCOPY) $(HEX_EEPROM_FLAGS) -O ihex $< $@
%.lss: %.elf
	$(OBJDUMP) -h -S $< > $@
size: $(PROJECT).elf
	 $(SIZE) --format=avr --mcu=$(MCU) $<

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) $(PROJECT).map dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

