#ifndef ASM_H
#define ASM_H

unsigned char inb ( unsigned short port );
void outb ( unsigned short port , unsigned char data );
unsigned short inw ( unsigned short port );
unsigned short outw ( unsigned short port );


#endif /* ASM_H */
