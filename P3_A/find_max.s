	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function
Find_Max:
// prologue - write code for the prologue here

// printf("The length of the array is %d\n", n);
// update this code if necessary to print the length of the array
// this block prints the value of register %edi
// initially the parameter n
	movl	%edi, %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

// reserve space for local variables
/* make a table here the variables from 
 * your c code and the addresses used in assembly 
 * n - address of n    
 * a - address of a
 * i - address of i
 * ....
*/ 

// this code calls Print_One_Number to 
// print the number found in register %eax - use this code to debug 
// replace $999 with a register or memory address you wish to print
    movl    $999, %eax
	movl	%eax, %edi
	call	Print_One_Number@PLT

// write your code to find the index of the maximum value here


// prepare the return value
// the template returns -1, you will need to update this
	movl	$-1, %eax

// epilogue - complete the epilogue below
	ret
.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
