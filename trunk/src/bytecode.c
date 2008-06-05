#include "jsint.h"

#define EEMEM
#include "bytecode.h"

JSByteCode *init_bytecode()
{
	return js_bc_read_data(_bytecode, _bytecode_size);
}
