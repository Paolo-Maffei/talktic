## General Options
PROJECT = talktic
MCU = atmega128
TARGET = $(PROJECT).elf $(PROJECT).hex $(PROJECT).eep $(PROJECT).lst
CC = avr-gcc
SIZE = avr-size
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
NM = avr-nm
AVRDUDE = avrdude
AVRDUDE_COMPORT = com6
TEST_COMPORT = com5
SRC_DIR = ../../src

MOXA = 1
# MOXA_SERIAL = 1
MOXA_RADIO = 1

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -Os -fsigned-char -gstabs -mcall-prologues
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

ifdef MOXA
CFLAGS += -D_MOXA
endif
ifdef MOXA_SERIAL
CFLAGS += -D_MOXA_SERIAL
endif
ifdef MOXA_RADIO
CFLAGS += -D_MOXA_RADIO
endif

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map

## Memory map
# |internal SRAM       |extrenal SRAM(32K)       |
# |0x1000        0x10FF|0x1100             0x90FF|
# |data,bss--> <--stack|heap                     |
#LDFLAGS += -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x8090FF

# |internal SRAM       |extrenal SRAM(32K)       |
# |0x1000        0x10FF|0x1100             0x90FF|
# |            <--stack|data,bss,heap            |
LDFLAGS += -Wl,-section-start=.data=0x801100,--defsym=__heap_end=0x8090FF


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

ifdef MOXA_SERIAL
MAIN_OBJECTS += serial.o
endif
ifdef MOXA_RADIO
MAIN_OBJECTS += radio.o chip_cc2420.o
endif

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
%.lst: %.elf
	$(NM) -n $< > $@
size: $(PROJECT).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

## Writing chip
AVRDUDE_OPTIONS = -p m128 -c stk500v2 -v -P $(AVRDUDE_COMPORT) -V
write: erase flash eep
erase:
	$(AVRDUDE) $(AVRDUDE_OPTIONS) -e
flash: $(PROJECT).hex
	$(AVRDUDE) $(AVRDUDE_OPTIONS) -U flash:w:$<:i
eep: $(PROJECT).eep
	$(AVRDUDE) $(AVRDUDE_OPTIONS) -U eeprom:w:$<:i

## Testing target
test: flash eep console
console: 
	cat /dev/$(TEST_COMPORT)

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) $(PROJECT).map dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

