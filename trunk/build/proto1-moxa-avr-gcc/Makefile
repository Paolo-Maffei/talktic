### Build options

## General options
PROJECT = talktic
MCU = atmega128
TARGET = $(PROJECT).elf $(PROJECT).hex $(PROJECT).eep

## Commands
CC = avr-gcc
SIZE = avr-size
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
NM = avr-nm

## Testing enviroment
AVRDUDE = avrdude
AVRDUDE_COMPORT = com6
TEST_COMPORT = com5

## Source path
SRC_DIR = ../../src

## Build options
# MOXA_SERIAL = 1
RADIO = 1
DIGITALIO = 1
ANALOGIO = 1



### Build enviroment

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
#CFLAGS += -gstabs
#CFLAGS += -fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CFLAGS += -gdwarf-2
CFLAGS += -Wall -Os -mcall-prologues
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf-2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map

## Memory map
# |internal SRAM       |extrenal SRAM(32K)       |
# |0x1000        0x10FF|0x1100             0x90FF|
# |data,bss--> <--stack|heap                     |
LDFLAGS += -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x8090FF
# |internal SRAM       |extrenal SRAM(32K)       |
# |0x1000        0x10FF|0x1100             0x90FF|
# |            <--stack|data,bss,heap            |
#LDFLAGS += -Wl,-section-start=.data=0x801100,--defsym=__heap_end=0x8090FF

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0

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



### MOXA libraries

## Includes
INCLUDES += -I$(SRC_DIR)/moxa

## Objects
OBJECTS += 		\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/moxa/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<

## Libraries
ifdef MOXA_SERIAL
CFLAGS += -D_PROTO1_MOXA_SERIAL
OBJECTS += serial.o
endif # MOXA_SERIAL

ifdef RADIO
OBJECTS += radio.o chip_cc2420.o
endif # RADIO

ifdef ANALOGIO
OBJECTS += device_ad.o
endif


### PROTO1 ext libraries

## Includes
INCLUDES += -I$(SRC_DIR)/proto1

## Objects
OBJECTS +=		\
	init1.o		\
	stdio.o		\
	$(NULL)

## Compile
%.o: $(SRC_DIR)/proto1/%.c
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<

## Libraries
ifdef RADIO
CFLAGS += -D_PROTO1_RADIO
OBJECTS += b_radio.o
endif # RADIO

ifdef DIGITALIO
CFLAGS += -D_PROTO1_DIGITALIO
OBJECTS += b_digitalio.o
endif

ifdef ANALOGIO
CFLAGS += -D_PROTO1_ANALOGIO
OBJECTS += b_analogio.o
endif


### Common

## Includes
INCLUDES += -I$(SRC_DIR)

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
init_console:
	mode.com $(TEST_COMPORT): BAUD=9600 PARITY=N DATA=8 STOP=1
console: init_console
	cat /dev/$(TEST_COMPORT)

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(TARGET) $(PROJECT).map dep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
