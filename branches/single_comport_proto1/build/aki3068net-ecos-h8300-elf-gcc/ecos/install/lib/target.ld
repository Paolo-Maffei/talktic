STARTUP(vectors.o)
ENTRY(__start)

INPUT(extras.o)


GROUP(libtarget.a libgcc.a libsupc++.a)
OUTPUT_FORMAT("elf32-h8300")
OUTPUT_ARCH(h8300h)

MEMORY
{
    ram : ORIGIN = 0x400000, LENGTH = 0x200000
    iram : ORIGIN = 0xffbf20, LENGTH = 0x4000-0x100
}

SECTIONS
{
   
    .text 0x400000 : { __stext = ABSOLUTE(.); *(.text*) *(.gnu.warning) *(.gnu.linkonce*) *(.init) } > ram __etext = .; PROVIDE (etext = .);
    .fini ALIGN (0x1) : { . = .; *(.fini) } > ram
    .rodata ALIGN (0x1) : { . = .; *(.rodata*) } > ram
    .rodata1 ALIGN (0x1) : { . = .; *(.rodata1) } > ram
    .fixup ALIGN (0x1) : { . = .; *(.fixup) } > ram
    .gcc_except_table ALIGN (0x1) : { . = .; *(.gcc_except_table) } > ram
    .data ALIGN (0x4) : { ___ram_data_start = ABSOLUTE (.); *(.data*) *(.data1) . = ALIGN(4); KEEP(*( SORT (.ecos.table.*))) ; . = ALIGN(4); __GOT1_START_ = ABSOLUTE (.); *(.got1) __GOT1_END_ = ABSOLUTE (.); __GOT2_START_ = ABSOLUTE (.); *(.got2) __GOT2_END_ = ABSOLUTE (.); . = ALIGN (4); ___CTOR_LIST__ = ABSOLUTE (.); KEEP (*(SORT (.ctors*))) ___CTOR_END__ = ABSOLUTE (.); ___DTOR_LIST__ = ABSOLUTE (.); KEEP (*(SORT (.dtors*))) ___DTOR_END__ = ABSOLUTE (.); __GOT_START = ABSOLUTE (.); __GLOBAL_OFFSET_TABLE_ = ABSOLUTE (.) + 32768; __SDA_BASE_ = ABSOLUTE (.); *(.got.plt) *(.got) __GOT_END_ = ABSOLUTE (.); *(.eh_frame) *(.dynamic) *(.sdata*) *(.sbss*) } > ram ___rom_data_start = LOADADDR (.data); ___ram_data_end = .; PROVIDE (___ram_data_end = .); __edata = .; PROVIDE (edata = .);
    .bss ALIGN (0x4) : { ___bss_start = ABSOLUTE (.); *(.scommon) *(.dynbss) *(.bss.*) *(COMMON) ___bss_end = ABSOLUTE (.); } > ram
    .int_hook_table 0x00FFFD20 : AT ((LOADADDR (.data) + SIZEOF (.data) + 4 - 1) & ~ (4 - 1)) { ___int_hook_start = ABSOLUTE (.); . = .; *(.int_hook_table) } > iram ___rom_int_hook_table = LOADADDR(.int_hook_table); ___int_hook_end = .;
    . = ALIGN(4); _end = .; PROVIDE (end = .);
}


_hal_virtual_vector_table = 0xfffe20;
