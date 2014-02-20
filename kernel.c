#include <types.h>
#include <screen.h>
#include <lib.h>
#include <idt.h>
#include <timer.h>
#include <keyboard.h>
#include <isr.h>
#include <paging.h>

void main() {

  char string[10];

  char test[10];

  
  init_idt();
  init_register_isrs();
  
  print_string("\n");
  
  asm volatile ("int $0x3");
  /* asm volatile ("int $0x3"); */

  init_keyboard();
  
  //  asm volatile("int $0x8");
  
  //  init_timer(50);

  init_paging();

  print_string(itoa((uint32_t) &test, string, 16));

  
  
  while(1) ; // infinite loop
}
