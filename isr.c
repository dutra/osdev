#include <lib.h>
#include <isr.h>
#include <screen.h>
#include <types.h>
#include <asm.h>
#include <panic.h>

isr_t interrupt_handlers[256];

// Handles Interrupt requests. It is called from the assembly interrupts
void isr_handler(registers_t regs) {

  // If it is an IRQ,
  // Send an EOI (end of interrupt) signal to the PICs.
  if (regs.int_no >= IRQ0 && regs.int_no <= IRQ15) {
    // If this interrupt involved the slave.
    if (regs.int_no >= IRQ8)
      {
	// Send reset signal to slave.
	outb(0xA0, 0x20);
      }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);
  }

  if (interrupt_handlers[regs.int_no] != 0) {
      isr_t handler = interrupt_handlers[regs.int_no];
      (*handler)(regs);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

// Register interrupts handlers except for IRQs
void init_register_isrs() {
  register_interrupt_handler(0, &print_interrupt_number);
  register_interrupt_handler(1, &print_interrupt_number);
  register_interrupt_handler(2, &print_interrupt_number);
  register_interrupt_handler(3, &print_interrupt_number);
  register_interrupt_handler(4, &print_interrupt_number);
  register_interrupt_handler(5, &print_interrupt_number);
  register_interrupt_handler(6, &print_interrupt_number);
  register_interrupt_handler(7, &print_interrupt_number);
  register_interrupt_handler(8, &panic); // double fault
  register_interrupt_handler(9, &print_interrupt_number);
  register_interrupt_handler(10, &print_interrupt_number);
  register_interrupt_handler(11, &print_interrupt_number);
  register_interrupt_handler(12, &print_interrupt_number);
  register_interrupt_handler(13, &print_interrupt_number);
  register_interrupt_handler(14, &panic); // page fault
  register_interrupt_handler(15, &print_interrupt_number);
  register_interrupt_handler(16, &print_interrupt_number);
  register_interrupt_handler(17, &print_interrupt_number);
  register_interrupt_handler(18, &print_interrupt_number);
}

void print_interrupt_number(registers_t regs) {
  char int_number[10];
  print_string("Interrupt: ");
  print_string(itoa(regs.int_no, int_number, 10));
  print_string("\n");
}
