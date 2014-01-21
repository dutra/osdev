#include "../drivers/screen.h"

void main() {

  //  char *video_memory = (char *) 0xb8000;

  //  *video_memory = 'X';
  print_char('I', 0, 0, 0);

  while(1); // infinite loop
}
