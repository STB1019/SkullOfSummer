	.file	"restrict.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	increase
	.type	increase, @function
increase:
.LFB0:
	.cfi_startproc
	movl	(%rdx), %eax
	addl	%eax, (%rdi)
	# here the CPU loads the value pointed by c. It needs to do that because maybe c=a: 
	# if this is the case the line *a = *a + *c has changed not only *a, but *c as well!
	# This is why the CPU needs to reload *c
	movl	(%rdx), %eax
	addl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	increase, .-increase
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
