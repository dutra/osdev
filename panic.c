#include <isr.h>
#include <screen.h>
#include <lib.h>

void panic(registers_t regs) {
  char number_string[10];
  bool halt = false;
  
  puts("######### KERNEL PANIC! #########");

  if(regs.int_no == 8) {
    puts("Double Fault Exception");
    halt = true;
  }
    
  puts("Registers Dump:");
  print_string("EAX: ");
  print_string(itoa(regs.eax, number_string, 16));
  print_string("\n");
  
  
  if(halt) {
    puts("Halting the cpu...");
    __asm__ __volatile__("hlt");
  }
  
  
}
