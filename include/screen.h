#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x02
// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void puts(char *string);
void print_string(char *string);
void print_char(char character, int row, int col, char attribute_byte);
int get_screen_offset(int row, int col);
int get_cursor();
void set_cursor(unsigned int offsetx);
void clear_screen();
int handle_scrolling(int cursor_offset, char attribute_byte);

#endif /* SCREEN_H */
