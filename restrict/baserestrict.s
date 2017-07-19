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
