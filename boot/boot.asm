   [org  0x7c00]

STACK_16 equ 0x9000
KERNEL_SEG_16 equ 0x4000        ; We need to use segments to reach KERNEL_OFFSET_32 in real mode
KERNEL_OFFSET_16 equ 0x0

STACK_32 equ 0x3ffff
KERNEL_OFFSET_32 equ 0x40000    ; We will load the kernel here
   
   mov   [BOOT_DRIVE], dl       ; BIOS stores our boot drive in dl, so let's save it for later use
   
   mov   bp, STACK_16             ; set stack
   mov   sp, bp

   mov   bx, MSG_REAL_MODE
   call  print_string

   call  load_kernel

   call  switch_to_pm

loop:
   jmp   loop

   ;; include files
   %include "boot/print_string_rm.asm"
   %include "boot/gdt.asm"
   %include "boot/disk_load.asm"
   %include "boot/switch_to_pm.asm"

   [bits 16]
load_kernel:
   mov bx, MSG_LOAD_KERNEL
   call print_string

   mov ax, 0x4000
   mov es, ax
   mov bx, KERNEL_OFFSET_16
   mov dh, 11
   mov dl, [BOOT_DRIVE]
   call disk_load
   ret
   
   [bits 32]
   %include "boot/print_string_pm.asm"

BEGIN_PM:

   mov   ebx, MSG_PROT_MODE
   call  print_string_pm

   call  CODE_SEG:KERNEL_OFFSET_32
   
   jmp   $

   ;; Data
   BOOT_DRIVE db 0
   MSG_REAL_MODE db "Starting 16 bit Real Mode", 0
   MSG_LOAD_KERNEL db "Loading Kernel into memory", 0
   MSG_PROT_MODE db "Sucesfully jumped into 32 bits Protected Mode", 0

   ;; padding and boot magic number
   times 510 -( $ - $$ ) db 0
   dw    0xaa55
