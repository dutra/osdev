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


  test[0] = 'a';
  test[1] = 'b';
  test[2] = '\0';

  puts(test);
  
  /* print_string(itoa((uint32_t) &test, string, 16)); */

  while(addr < 0xffffffff) {
    puts(itoa(((uint32_t) addr)/1024/1024, string, 10));
    string[0] = *test;
    test += 0x100000;
    addr += 0x100000;
  }
    
  

  
  
  while(1) ; // infinite loop
}
