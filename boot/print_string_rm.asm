print_string:
   push ax
   push bx
   
print_string_loop:
   mov   al, [bx]
   cmp   al, byte 0
   je    print_string_exit
   call  print_char
   inc   bx
   jmp   print_string_loop
   
print_string_exit:
   mov   al, 0x0D
   call print_char
   
   mov   al, 0x0A               ; new line
   call  print_char

   pop   bx
   pop   ax
                                ;   popa
   ret   
   
print_char:   
   mov   ah, 0x0e
   int   0x10
   ret   