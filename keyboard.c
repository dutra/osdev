#include <isr.h>
#include <screen.h>
#include <asm.h>
#include <lib.h>
#include <keyboard.h>

// contains mapping from scancodes to ascii
uint8_t scancode[88];

static void keyboard_callback(registers_t regs) {

  uint8_t keycode;
  char keycode_string[10];
  char key[4];
  
  keycode = (uint8_t) inb(0x60);

  if(keycode & 0x80) {
    print_string("Key lifted: ");
    keycode -= 0x80;
  } else
    print_string("Key pressed: ");

  key[0] = scancode[keycode];
  key[1] = '\0';

  
  print_string(itoa(scancode[keycode],keycode_string, 10));
  print_string("  ");
  print_string(key);
  print_string("  ");
  print_string(itoa(keycode, keycode_string, 10));
  print_string("\n");

}

// initializes the scancodes mapping and registers our keyboard handler
void init_keyboard() {

    /* less efficient than scancode[] = {}, but easier to catch a bug. Will change later */
  scancode[KEY_A] = 'a';
  scancode[KEY_B] = 'b';
  scancode[KEY_C] = 'c';
  scancode[KEY_D] = 'd';
  scancode[KEY_E] = 'e';
  scancode[KEY_F] = 'f';
  scancode[KEY_G] = 'g';
  scancode[KEY_H] = 'h';
  scancode[KEY_I] = 'i';
  scancode[KEY_J] = 'j';
  scancode[KEY_K] = 'k';
  scancode[KEY_L] = 'l';
  scancode[KEY_M] = 'm';
  scancode[KEY_N] = 'n';
  scancode[KEY_O] = 'o';
  scancode[KEY_P] = 'p';
  scancode[KEY_Q] = 'q';
  scancode[KEY_R] = 'r';
  scancode[KEY_S] = 's';
  scancode[KEY_T] = 't';
  scancode[KEY_U] = 'u';
  scancode[KEY_V] = 'v';
  scancode[KEY_X] = 'x';
  scancode[KEY_W] = 'w';
  scancode[KEY_Y] = 'y';
  scancode[KEY_Z] = 'z';

  register_interrupt_handler(IRQ1, &keyboard_callback);


}
