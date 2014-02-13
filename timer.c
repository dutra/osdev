#include <timer.h>
#include <isr.h>
#include <screen.h>
#include <asm.h>
#include <lib.h>

uint32_t tick = 0;

static void timer_callback(registers_t regs) {
  char tick_string[10];
  tick++;
  print_string("Tick: ");
  print_string(itoa(tick, tick_string, 10));
  print_string("\n");
}

void init_timer(uint32_t frequency) {
  uint32_t divisor = 0;
  
  // The divisor sent to PIT has to fit in 16-bits. Thus, the maximum divisor is 2^16, giving a minimum frequency of 18.2 Hz and a max frequency of 1193180
  if((frequency > 0 && frequency < 19) || frequency > 1193180) {
    puts("Error setting the frequency");
    return;
  }
  
  // Firstly, register our timer callback.
  register_interrupt_handler(IRQ0, &timer_callback);

  // The value we send to the PIT is the value to divide it's input clock
  // (1193180 Hz) by, to get our required frequency. Important to note is
  // that the divisor must be small enough to fit into 16-bits.
  // That is, min frequency is 18 Hz.

  if(frequency)
    divisor = 1193180 / frequency;


  // Send the command byte.
  outb(0x43, 0x36);

  // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
  uint8_t l = (uint8_t) (divisor & 0xFF);
  uint8_t h = (uint8_t) ((divisor>>8) & 0xFF);

  // Send the frequency divisor.
  outb(0x40, l);
  outb(0x40, h);
}
