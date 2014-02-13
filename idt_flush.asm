   [GLOBAL idt_flush]          
   
idt_flush:
   mov   eax, [esp+4]           ; Loads into eax the first argument passed to idt_flush
   lidt  [eax]                  ; sets the idt
   sti                          ; enables interrupts
   ret