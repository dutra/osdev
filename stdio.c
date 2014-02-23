#include <stdarg.h>
#include <screen.h>
#include <lib.h>
#include <stdio.h>

static int parser(char *output, const char *input, const char *args[]);

void puts(char *string) {
    print_string(string);
    print_string("\n");
}

void printf(const char *string, const void * args, ...) {

  char string_out[255];

  va_list ap;
  const char *array[MAXARGS +1];
  int argno = 0;

  va_start(ap, args);
  while (args != 0 && argno < MAXARGS) {
    array[argno++] = args;
    args = va_arg(ap, const char *);
  }

  array[argno] = (char *) 0;
  va_end(ap);

  parser(string_out, string, array);
  puts(string_out);

}

static int parser(char *output, const char *input, const char *args[]) {
  int ipos = 0, apos = 0, opos = 0, i;
  char tmp[16];
  while(1) {
    if(input[ipos] == '\0') {
      output[opos] = '\0';
      break;
    }

    if(input[ipos] == '%') {
      switch(input[ipos+1]) {
      case 'd':
	itoa((int) args[apos++], tmp, 10);
	for(i=0; tmp[i]; i++)
	  output[opos+i] = (char) tmp[i];
	opos+=i-1;
        break;
      case 'c':
        output[opos] = (char) *args[apos++];
        break;
      case 's':
	puts("Case s");
	for(i=0; args[apos][i]; i++)
	  output[opos+i] = (char) args[apos][i];
	apos++; opos+=i-1;
	break;
      default:
        output[opos] = input[ipos];
        output[opos+1] = input[ipos+1];
      }
      ipos++;
    } else {
      output[opos] = input[ipos];
    }
    opos++; ipos++;
  }
  return 0;
}

