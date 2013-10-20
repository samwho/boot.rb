ENTRY (loader)

SECTIONS
{
    . = 0x00100000;

    .mboot ALIGN(0x1000) :
    {
        *(.mboot)
    }

    .text ALIGN (0x1000) :
    {
        _TEXT_START = .;
		*(.text)
        _TEXT_END = .;
    }

    .rodata ALIGN (0x1000) :
    {
        _RODATA_START = .;
        *(.rodata*)
        _RODATA_END = .;
    }

    .data ALIGN (0x1000) :
    {
        _DATA_START = .;
        *(.data)
        _DATA_END = .;
    }

    .bss :
    {
        _BSS_START = .;
        *(COMMON)
        *(.bss)
        _BSS_END = .;
    }
}
