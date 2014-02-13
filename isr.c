#include "lib.h"
#include "isr.h"
#include "screen.h"
#include "types.h"

void isr_handler(registers_t regs) {
  char int_number[10];
  print_string("Interrupt: ");
  print_string(itoa(regs.int_no, int_number, 10));
  print_string("\n");
}
