	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
.globl	_Factorial              ## -- Begin function Factorial
	#.type	Factorial, @function
	.p2align	4, 0x90
_Factorial:                             ## @Factorial
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jne	LBB0_2
## BB#1:
	movl	$1, -4(%rbp)
	jmp	LBB0_3
LBB0_2:
	movl	-8(%rbp), %eax
	movl	-8(%rbp), %ecx
	subl	$1, %ecx
	movl	%ecx, %edi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	_Factorial
	movl	-12(%rbp), %ecx         ## 4-byte Reload
	imull	%eax, %ecx
	movl	%ecx, -4(%rbp)
LBB0_3:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.globl	_nCr                    ## -- Begin function nCr
	#.type	nCr, @function
	.p2align	4, 0x90
_nCr:                                   ## @nCr
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edi
	callq	_Factorial
	movl	-8(%rbp), %edi
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	callq	_Factorial
	movl	-4(%rbp), %esi
	subl	-8(%rbp), %esi
	movl	%esi, %edi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	callq	_Factorial
	movl	-20(%rbp), %esi         ## 4-byte Reload
	imull	%eax, %esi
	movl	-16(%rbp), %eax         ## 4-byte Reload
	cltd
	idivl	%esi
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
