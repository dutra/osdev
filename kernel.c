#include <types.h>
#include <screen.h>
#include <lib.h>

void main() {

  char string[20] = "";
  char *p = string;
  p = itoa(125, string, 10);
  print_string(p, 0, 0);
  
  while(1) ; // infinite loop
}
