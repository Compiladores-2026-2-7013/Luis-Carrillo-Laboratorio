	.file	"programa.c"
	.text
	.section	.rodata
.LC0:
	.string	"Hola mundo! "
.LC2:
	.string	"Resultado: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC0, %edi
	call	puts
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-4(%rbp), %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC1:
	.long	1105342969
	.ident	"GCC: (GNU) 14.3.1 20251022 (Red Hat 14.3.1-4)"
	.section	.note.GNU-stack,"",@progbits
