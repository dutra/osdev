#include <types.h>
#include <screen.h>
#include <lib.h>
#include <idt.h>
#include <timer.h>
#include <keyboard.h>
#include <isr.h>
#include <paging.h>

void main() {

  char string[40];

  char *test = (char *) 0x0;
  uint32_t addr = 0x0;
  
  
  init_idt();
  init_register_isrs();
  
  print_string("\n");
  
  asm volatile ("int $0x3");
  /* asm volatile ("int $0x3"); */

  init_keyboard();
  
  //  asm volatile("int $0x8");
  
  //  init_timer(50);

  init_paging();


  
  /* print_string(itoa((uint32_t) &test, string, 16)); */

  while(addr < 0xffffffff) {
    print_string("Testing memory position: 0x");
    puts(itoa(((uint32_t) addr), string, 16));
    string[0] = *test;
    test += 0x100000;
    addr += 0x100000;
  }
    
  

  
  
  while(1) ; // infinite loop
}
