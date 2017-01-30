.text
	.align 4
	.globl procesar
	.type	procesar, @function
cero:	.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp	# subl $8, %esp ?
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo

	# Como se accede al elemento 0, luego al 1,
	# luego al 2, etc. hasta el nxn - 1, se
	# puede hacer un for (i = 0; i < nxn; ++i)
	# con stride 1 (chars) y sin la j

	movl $0, %eax		# eax = i = 0
	movl 8(%ebp), %ebx	# ebx = @mata
	movl 12(%ebp), %ecx	# ecx = @matb
	movl 16(%ebp), %edi	# edi = @matc
	movl 20(%ebp), %esi	# esi = n
	imull %esi, %esi	# esi = nxn
	
for:	cmpl %esi, %eax
	jge fifor		# saltar a fifor si i >= nxn
	movdqu (%ebx), %xmm0	# xmm0 = mata[i*n+j]
	movdqu (%ecx), %xmm1	# xmm1 = matb[i*n+j]
	psubb %xmm1, %xmm0	# xmm0 = mata[i*n+j] - matb[i*n+j]
	movdqu %xmm0, (%edi)	# matc[i*n+j] = mata[i*n+j] - matb[i*n+j]
	
	movdqu cero, %xmm2	# xmm2 = 0
	pcmpgtb %xmm2, %xmm0	# si matc[i*n+j] > 0, matc[i*n+j] = 0xFF
				# si no, matc[i*n+j] = 0x00
	movdqu %xmm0, (%edi)	
	
	addl $16, %eax		# i = i + 16;
	addl $16, %ebx		# stride
	addl $16, %ecx		# stride
	addl $16, %edi		# stride
	jmp for
fifor:

# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret