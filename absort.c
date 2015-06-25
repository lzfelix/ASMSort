#include <stdio.h>

int main(){
   int v[5];
   int a;

   for(a=0; a<5; a++)
      scanf("%d", &v[a]);

   asm mov dx, 0x04	            //array's size
   asm mov al, 0x01	            //AL is the swap flag

   While:
      asm cmp al, 0x01
      asm jnz Fim
      asm xor ax, ax		    //turn off the swap flag
      asm xor cx, cx		    //CX is counter

      asm lea si, v		        //SI is the vector

  Loop:
	asm mov bx, [si]            //BX is SI's current element
	asm add si, 2               //Advances SI to the next position (int is size 2)

	asm cmp bx, [si]            //compare two adjacent array elements. One is on BX
                                //and the next is on [SI]

	asm jl	NoSwap              //if BX is lesser than [SI], don't swap

	asm push word ptr [si]		//begins swapping
	asm mov word ptr [si], bx	//v[a+1] = v[a]
	asm sub si, 2		       	//goes back one position on the array
	asm pop word ptr [si]
	asm add si, 2			    //gpes back to the original position (one ahead)
	asm mov al, 0x01

  NoSwap:
	asm inc cx
	asm cmp cx, dx
	asm jnz Loop

	asm jmp While
   Fim:

   for(a=0; a<5; a++)
      printf("%d ",v[a]);
   printf("\n");

   return 0;
}
