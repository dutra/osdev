#include <screen.h>
#include <lib.h>
#include <asm.h>

void print_string(char *string) {
  int i=0;
  while(string[i] != 0) {
    
    print_char(string[i++], -1, -1, WHITE_ON_BLACK);
  }
    
}
void print_char(char character, int row, int col, char attribute_byte) {

  unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

  if (!attribute_byte) {
    attribute_byte = WHITE_ON_BLACK;
  }
  int offset;

  if (col >= 0 && row >= 0) 
    offset = get_screen_offset(row, col);
  else 
    offset = get_cursor();
  
  if (character == '\n') {
    int rows = offset / (2*MAX_COLS);
    offset = get_screen_offset(rows, MAX_COLS-1);
  } else {
    vidmem[offset] = character;
    vidmem[offset+1] = attribute_byte;
  }

  offset += 2;

  offset = handle_scrolling(offset, attribute_byte);

  set_cursor(offset);
}

int get_screen_offset(int row, int col) {
  return (row * 80 + col) * 2;
}

int get_cursor() {
  outb (REG_SCREEN_CTRL, 14);
  int offset = inb (REG_SCREEN_DATA) << 8;
  outb (REG_SCREEN_CTRL, 15);
  offset += inb (REG_SCREEN_DATA);
  return offset * 2;
}

void set_cursor (unsigned int offset) {
  offset /= 2;
 
  outb (0x3D4, 14);
  outb (0x3D5, (offset >> 8));
  outb (0x3D4, 15);
  outb (0x3D5, offset);
}

void clear_screen() {
  int row = 0;
  int col = 0;

  for (row = 0; row < MAX_ROWS; row++) {
    for (col = 0; col < MAX_COLS; col++) {
      print_char(' ', row, col, WHITE_ON_BLACK);
    }
  }

  set_cursor(get_screen_offset(0,0));
}

int handle_scrolling(int cursor_offset, char attribute_byte) {
  char *dst_row, *src_row;
  int i;
  
  if (cursor_offset < MAX_ROWS*MAX_COLS*2)
    return cursor_offset;

  for (i=1; i<MAX_ROWS; i++) { // move rows back by one
    src_row = (char *) get_screen_offset(i, 0) + VIDEO_ADDRESS;
    dst_row = (char *) get_screen_offset(i-1, 0) + VIDEO_ADDRESS;
    memcpy(dst_row, src_row, MAX_COLS*2);
  }

  // clean last row
  char* last_row = (char *) get_screen_offset(MAX_ROWS-1, 0) + VIDEO_ADDRESS;
  for (i=0; i<MAX_COLS; i++) {
    last_row[2*i] = ' ';
    last_row[2*i+1] = attribute_byte;
  }

  // move offset to beginning of the last row
  cursor_offset -= 2*MAX_COLS;

  return cursor_offset;
}
    
