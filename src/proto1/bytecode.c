#include "jsint.h"
#include <avr/eeprom.h>

#include "bytecode.h"

// This file will be linked alternatively $(SRC_DIR)/bytecode, see the
// %.o dependency rule in the Makefile.

#define JS_BC_EEPROM_READ_INT32(cp, var) \
    (var) = eeprom_read_byte(cp); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+1); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+2); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+3)

#define JS_BC_EEPROM_READ_INT16(cp, var) \
    (var) = eeprom_read_byte(cp); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+1)

#define JS_BC_EEPROM_READ_INT8(cp, var) \
    (var) = eeprom_read_byte(cp)

static JSByteCode *read_eeprom_bytecode(unsigned char *data)
{
	JSUInt32 ui = 0;
	JSUInt8 ub = 0;
	unsigned int pos = 0;
	int i, j;
	JSByteCode *bc = NULL;

	while (!eeprom_is_ready()) {
	};

	pos += 4;

	bc = js_calloc(NULL, 1, sizeof(*bc));
	if (bc == NULL)
		return NULL;

	JS_BC_EEPROM_READ_INT32(data + pos, ui);
	bc->num_sects = (unsigned int) ui;
	pos += 4;

	bc->sects = js_calloc(NULL, bc->num_sects, sizeof(JSBCSect));
	if (bc->sects == NULL) {
		js_free(bc);
		return NULL;
	}

	/* Read sections. */
	for (i = 0; i < bc->num_sects; i++) {
		/* Get type. */
		JS_BC_EEPROM_READ_INT32(data + pos, ui);
		bc->sects[i].type = (int) ui;
		pos += 4;

		/* Get section length. */
		JS_BC_EEPROM_READ_INT32(data + pos, ui);
		bc->sects[i].length = (unsigned int) ui;
		pos += 4;

		bc->sects[i].data = js_malloc(NULL, bc->sects[i].length + 1
									  /* +1 to avoid zero allocations */ );
		if (bc->sects[i].data == NULL) {
			for (i--; i >= 0; i--)
				js_free(bc->sects[i].data);

			js_free(bc->sects);
			js_free(bc);
			return NULL;
		}

		for (j = 0; j < bc->sects[i].length; j++) {
			JS_BC_EEPROM_READ_INT8(data + pos + j, ub);
			*(JSUInt8 *) (bc->sects[i].data + j) = ub;
		}
		pos += bc->sects[i].length;
	}
	return bc;
}

JSByteCode *init_bytecode() {
	return read_eeprom_bytecode(0x00);
}
