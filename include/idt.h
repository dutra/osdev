#ifndef IDT_H
#define IDT_H

#include <types.h>

// Interrupt descriptor entry
struct idt_entry_struct {
  uint16_t offset_low;              // The lower 16 bits of the offset to jump to when this interrupt fires.
  uint16_t selector;                // Kernel segment selector.
  uint8_t  zero;                    // unused, set to 0
  uint8_t  flags;                   // 7: Present, 6:5: Descriptor Privilege Level, 4: Storage segment
                                    // 3:0 Gate type (0xE 32-bit interrupt gate, 0xF 32-bit trap gate)
  uint16_t offset_high;             // The upper 16 bits of the offset.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
  uint16_t limit;
  uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

extern void idt_flush(uint32_t);
void init_idt();

// External references to Interrupt handlers implemented in assembly
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();

// External references to IRQs implemented in assembly
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


#endif /* IDT_H */
