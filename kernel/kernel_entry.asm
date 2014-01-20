;;; This file should be linked together with the kernel, but just before it
;;; It makes sure that we call main
   
   [bits 32]
   
   [extern main]

   call main

   jmp $