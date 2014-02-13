#include <lib.h>
#include <isr.h>
#include <screen.h>
#include <types.h>
#include <asm.h>

isr_t interrupt_handlers[256];

// Handles Interrupt requests. It is called from the assembly interrupts
void isr_handler(registers_t regs) {
  char int_number[10];
  print_string("Interrupt: ");
  print_string(itoa(regs.int_no, int_number, 10));
  print_string("\n");
}

// Handles interrupt requests from the IRQs
void irq_handler(registers_t regs)
{
  // Send an EOI (end of interrupt) signal to the PICs.
  // If this interrupt involved the slave.
  if (regs.int_no >= 40)
    {
      // Send reset signal to slave.
      outb(0xA0, 0x20);
    }
  // Send reset signal to master. (As well as slave, if necessary).
  outb(0x20, 0x20);

  if (interrupt_handlers[regs.int_no] != 0) {
      isr_t handler = interrupt_handlers[regs.int_no];
      (*handler)(regs);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}
