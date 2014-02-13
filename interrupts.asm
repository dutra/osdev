                                ; In isr.c
   [EXTERN isr_handler]
   
                                ; This is our common ISR stub. It saves the processor state, sets
                                ; up for kernel mode segments, calls the C-level fault handler,
                                ; and finally restores the stack frame.
isr_common_stub:
   pusha                        ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
   
   mov   ax, ds                 ; Lower 16-bits of eax = ds.
   push  eax                    ; save the data segment descriptor
   
   mov   ax, 0x10               ; load the kernel data segment descriptor
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax
   
   call  isr_handler
   
   pop   eax                    ; reload the original data segment descriptor
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax
   
   popa                         ; Pops edi,esi,ebp...
   add   esp, 8                 ; Cleans up the pushed error code and pushed ISR number
   sti   
   iret                         ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

   [GLOBAL isr0]
isr0:
   cli                          ; Disable interrupts
   push  byte 0                 ; Push a dummy error code (if ISR0 doesn't push it's own error code)
   push  byte 0                 ; Push the interrupt number (0)
   jmp   isr_common_stub        ; Go to our common handler.

   [GLOBAL isr1]
isr1:
   cli                    
   push  byte 0           
   push  byte 1           
   jmp   isr_common_stub  
   
   [GLOBAL isr2]
isr2:
   cli                    
   push  byte 0           
   push  byte 2           
   jmp   isr_common_stub  

   [GLOBAL isr3]
isr3:
   cli                    
   push  byte 0           
   push  byte 3           
   jmp   isr_common_stub  


   [EXTERN irq_handler]
   
irq_common_stub:
   pusha                        ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov   ax, ds                 ; Lower 16-bits of eax = ds.
   push  eax                    ; save the data segment descriptor

   mov   ax, 0x10               ; load the kernel data segment descriptor
      mov ds, ax
      mov es, ax
      mov fs, ax
      mov gs, ax

      call irq_handler

   pop   ebx                    ; reload the original data segment descriptor
      mov ds, bx
      mov es, bx
      mov fs, bx
      mov gs, bx

   popa                         ; Pops edi,esi,ebp...
   add   esp, 8                 ; Cleans up the pushed error code and pushed ISR number
      sti
   iret                         ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
   
   
[GLOBAL irq0]
irq0:
   cli
   push byte 0
   push byte 32
   jmp irq_common_stub
[GLOBAL irq1]
irq1:
   cli
   push byte 0
   push byte 33
   jmp irq_common_stub
[GLOBAL irq2]
irq2:
   cli
   push byte 0
   push byte 34
   jmp irq_common_stub
[GLOBAL irq3]
irq3:
   cli
   push byte 0
   push byte 35
   jmp irq_common_stub
[GLOBAL irq4]
irq4:
   cli
   push byte 0
   push byte 36
   jmp irq_common_stub
[GLOBAL irq5]
irq5:
   cli
   push byte 0
   push byte 37
   jmp irq_common_stub
[GLOBAL irq6]
irq6:
   cli
   push byte 0
   push byte 38
   jmp irq_common_stub
[GLOBAL irq7]
irq7:
   cli
   push byte 0
   push byte 39
   jmp irq_common_stub
[GLOBAL irq8]
irq8:
   cli
   push byte 0
   push byte 40
   jmp irq_common_stub
[GLOBAL irq9]
irq9:
   cli
   push byte 0
   push byte 41
   jmp irq_common_stub
[GLOBAL irq10]
irq10:
   cli
   push byte 0
   push byte 42
   jmp irq_common_stub
[GLOBAL irq11]
irq11:
   cli
   push byte 0
   push byte 43
   jmp irq_common_stub
[GLOBAL irq12]
irq12:
   cli
   push byte 0
   push byte 44
   jmp irq_common_stub
[GLOBAL irq13]
irq13:
   cli
   push byte 0
   push byte 45
   jmp irq_common_stub
[GLOBAL irq14]
irq14:
   cli
   push byte 0
   push byte 46
   jmp irq_common_stub
[GLOBAL irq15]
irq15:
   cli
   push byte 0
   push byte 47
   jmp irq_common_stub
   