#include <types.h>
#include <screen.h>
#include <lib.h>
#include <idt.h>
#include <timer.h>

void main() {
  init_idt();

  print_string("\n");
  
  asm volatile ("int $0x3");
  /* asm volatile ("int $0x3"); */

  // let's enable interrupts
  //  init_timer(50);
  
  while(1) ; // infinite loop
}
