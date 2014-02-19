#include <isr.h>
#include <screen.h>
#include <asm.h>
#include <lib.h>


static void keyboard_callback(registers_t regs) {
  uint8_t keycode;
  char keycode_string[10];
  
  keycode = (uint8_t) inb(0x60);
  
  print_string("Key pressed: ");
  print_string(itoa(keycode, keycode_string, 10));
  print_string("\n");
}

void init_keyboard() {
  
  register_interrupt_handler(IRQ1, &keyboard_callback);

}
