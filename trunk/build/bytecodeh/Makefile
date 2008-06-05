## General Options
SRC_DIR = ../../src
NJS = ./js.exe
JSC2H = ./jsc2header.rb
TARGET = $(SRC_DIR)/bytecode.h

## Build
all: $(TARGET)

## Compile
$(SRC_DIR)/%.jsc: $(SRC_DIR)/%.js
	$(NJS) -c $<
$(SRC_DIR)/%.h: $(SRC_DIR)/%.jsc
	$(JSC2H) $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(TARGET)
