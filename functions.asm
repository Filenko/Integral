section .rodata
   half dq 0.5
   three dq 3.0
   two_half dq 2.5
   nine_half dq 9.5
   five dq 5.0
section .text
global f1 ;f(x) = 3*(0.5/(x+1)+1);
f1:
push ebp
mov ebp, esp
finit
fld qword[ebp+8]
fld1
faddp
fld qword[half]
fdivrp
fld1
faddp
fld qword[three]
fmulp
leave
ret
    
global f2 ;2.5 * x - 9.5
f2:
push ebp
mov ebp, esp
finit
fld qword[ebp+8]
fld qword[two_half]
fmulp
fld qword[nine_half]
fsubp
leave
ret
    
global f3
f3: ;5 / x
push ebp
mov ebp, esp
finit
fld qword[five]
fld qword[ebp+8]
fdivp
leave
ret