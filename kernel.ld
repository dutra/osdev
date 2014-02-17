OUTPUT_FORMAT("binary")
STARTUP(kernel_entry.o)

SECTIONS
{
.text.start (0x40000) : {
kernel_entry.o( .text )
}

.text : ALIGN(512) {
_TEXT_START_ = .;
*(.text)
_TEXT_END_ = .;
}

.data : ALIGN(512) {
_DATA_START_ = .;
*(.data)
_DATA_END_ = .;
}

.bss : ALIGN(512) {
_BSS_START_ = .;
*(.bss)
_BSS_END_ = .;
}

}
