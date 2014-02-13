#include <idt.h>
#include <types.h>
#include <lib.h>

static void idt_set_gate(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_idt()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

  idt_set_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)isr2 , 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)isr3 , 0x08, 0x8E);
 
  idt_flush((uint32_t) &idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags) {
  idt_entries[num].offset_low = offset & 0xFFFF;
  idt_entries[num].offset_high = (offset >> 16) & 0xFFFF;

  idt_entries[num].selector = selector;
  idt_entries[num].zero = 0;

  idt_entries[num].flags = flags;
}
