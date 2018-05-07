;------------------------------------------------------------------------
;  File Name: test.asm
;  Author: Fang Yuan
;  Mail: yfang@nju.edu.cn
;  Created Time: Tue 04 Apr 2017 08:47:46 PM CST
;------------------------------------------------------------------------
   mov AX,  1234
   PUSH         ds
   add ax, Bx
   xlat
   dec di
   seg es
   mov [bx+si], dx
   NOP
   mov word[bp+di], 1234
   iNt 21
