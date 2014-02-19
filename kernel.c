#include <types.h>
#include <screen.h>
#include <lib.h>
#include <idt.h>
#include <timer.h>
#include <keyboard.h>
#include <isr.h>

void main() {
  init_idt();
  init_register_isrs();
  
  print_string("\n");
  
  asm volatile ("int $0x3");
  /* asm volatile ("int $0x3"); */

  init_keyboard();


  
  /* asm volatile("int $0x2"); */
  
  // let's enable interrupts
  //  init_timer(50);
  
  while(1) ; // infinite loop
}
