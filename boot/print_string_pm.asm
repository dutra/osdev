   ;; Define some constants
VIDEO_MEMORY equ 0xb8000
REG_SCREEN_CTRL equ 0x3D4
REG_SCREEN_DATA equ 0x3D5   
WHITE_ON_BLACK equ 0x0e

   ;; prints a null-terminated string pointed to by EDX
print_string_pm:
   pusha


get_cursor:
   mov   dx, REG_SCREEN_CTRL
   mov   al, 14
   out   dx, al

   xor   eax, eax
   mov   dx, REG_SCREEN_DATA
   in    al, dx
   shl   eax, 8
   mov   ecx, eax
   
   mov   dx, REG_SCREEN_CTRL
   mov   al, 15
   out   dx, al

   xor   eax, eax
   mov   dx, REG_SCREEN_DATA
   in    al, dx

   add   ax, cx

   mov   ecx, eax               ; keep offset

   shl   eax, 1                 ; multiples offset by 2 (two bytes per character)
                                ; first byte is attribute, second is character
   
   mov   edx, VIDEO_MEMORY

   add   edx, eax               ; points to video_memory[offset]
                                ; offset is position of the cursor
     
print_string_pm_loop:
   mov   al, [ebx]              ; Store the char at EBX in AL
    
   mov   ah, WHITE_ON_BLACK     ; Store the attributes in AH

   cmp   al, 0                  ; if (al == 0), at end of string, so
   je    print_string_pm_done                   ; jump to done
   
   mov   [edx], ax              ; Store char and attributes at current

   add   ebx, 1                 ; Increment EBX to the next char in string.
   add   edx, 2                 ; Move to next character cell in vid mem.
   add   ecx, 1                 ; Increment ecx to keep track of offset
   
   jmp   print_string_pm_loop   ; loop around to print the next char.
                             
print_string_pm_done:
   
update_cursor: 
   mov dx, REG_SCREEN_CTRL
   mov al, 14
   out dx, al

   mov dx, REG_SCREEN_DATA
   mov al, ch
   out dx, al

   mov dx, REG_SCREEN_CTRL
   mov al, 15
   out dx, al

   mov dx, REG_SCREEN_DATA
   mov al, cl
   out dx, al
   
   popa                         ; Return from the function
   ret
         