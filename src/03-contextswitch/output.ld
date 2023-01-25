MEMORY
{
	ram1(RX)	: ORIGIN = 0x80000000 LENGTH = 64M
	ram2(WI!R)	: ORIGIN = 0x84000000 LENGTH = 64M
}

OUTPUT_FORMAT("elf32-littleriscv","elf32-littleriscv",
	      "elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
	.init : {
		*(.init)
	} > ram1

	.text : {
		_text_start = .;
		*(.text)
		*(.text.*)
		_text_end = .;
	} > ram1

	.rodata : {
		. = ALIGN(16);
		*(.rodata)
		*(.rodata.*)
	} > ram1

	.data : {
		__data_start = .;
		*(.data)
		*(.data.*)
		*(.sdata)
		*(.sdata.*)
		__data_end = .;
	} > ram2

	.bss : {
		__bss_start = .;
		*(.bss)
		*(.bss.*)
		*(.sbss)
		*(.sbss.*)
		*(COMMON)
		__bss_end = .;
	} > ram2
}
