__inline__ unsigned char inb (unsigned short port) {
  // A handy C wrapper function that reads a byte from the specified port
  //"=a"(result) means : put AL register in variable RESULT when finished
  //"d"(port) means : load EDX with port
  unsigned char result ;
  __asm__ __volatile__ ("inb %%dx, %%al":"=a"(result) :"d"(port));
  return result ;
}
__inline__ void outb (int port, char data) {
  //"a"(data) means : load EAX with data
  //"d"(port) means : load EDX with port
  __asm__ __volatile__ ("outb %%al, %%dx" : : "a" (data), "d" (port));
}
__inline__ unsigned short inw (unsigned short port) {
  unsigned short result ;
  __asm__ __volatile__ ("in %%dx, %%ax":"=a"(result) :"d"(port));
  return result ;
}
__inline__ void outw (unsigned short port , unsigned short data) {
  __asm__ __volatile__ ("out %%ax, %%dx": :"a"(data) ,"d"(port));
}
