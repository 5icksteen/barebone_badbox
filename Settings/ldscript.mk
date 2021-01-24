define LDSCRIPT
/* This linker script is automatically generated by the makefile. */

MEMORY {
    FLASH (xrw) : ORIGIN = $(ROM_START), LENGTH = $(ROM_SIZE)
    RAM (rw)    : ORIGIN = $(RAM_START), LENGTH = $(RAM_SIZE)
}

SECTIONS {
/*------------------------------------------------------------------------------
 * FLASH Sections
------------------------------------------------------------------------------*/
    .vector : {
        KEEP(*(.stack_pointer))
        KEEP(*(.cortex_vectors))
        KEEP(*(.vendor_vectors))
    } >FLASH

    .text : {
        *(.text*)
        *(.rodata)
        *(.rodata*)
    } >FLASH

    .preinit_array : {
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(SORT(.preinit_array.*)))
        KEEP (*(.preinit_array*))
        . = ALIGN(4);
        __preinit_array_end = .;
    } >FLASH

    .init_array : {
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        . = ALIGN(4);
        __init_array_end = .;
    } >FLASH

    .fini_array : {
        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        . = ALIGN(4);
        __fini_array_end = .;
    } >FLASH

    .ARM.extab : ALIGN(4){
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.gcc_except_table)
		*(.eh_frame_hdr)
		*(.eh_frame)
	} >FLASH

	.ARM.exidx : ALIGN(4){
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} >FLASH

    __data_load = .;

/*------------------------------------------------------------------------------
 * RAM Sections
------------------------------------------------------------------------------*/
   .data : AT(__data_load) {
        . = ALIGN(4);
        __data_start = .;
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } >RAM

    .bss : {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } >RAM
    .heap (NOLOAD) : ALIGN(8)
	{
		__heap_start = .;
        __heap_end = __heap_start + 0x400;
	} > RAM
    __stack_top = ORIGIN(RAM) + LENGTH(RAM);
}

endef

.PHONY: all

all: $(OUTFILE)

$(OUTFILE):
	$(file >$@,$(LDSCRIPT))