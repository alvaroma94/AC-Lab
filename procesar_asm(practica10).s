.text
	.align 4
	.globl procesar
	.type	procesar, @function
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
	movb (%ebx), %dl	# dl = mata[i*n+j]
	subb (%ecx), %dl	# dl = mata[i*n+j] - matb[i*n+j]
	movb %dl, (%edi)	# matc[i*n+j] = mata[i*n+j] - matb[i*n+j]
if:	cmpb $0, (%edi)
	jle else		# saltar al else si matc[i*n+j] <= 0
	movb $255, (%edi)	# matc[i*n+j] = 255
	jmp fif
else:	movb $0, (%edi)		# matc[i*n+j] = 0
fif:	incl %eax		# ++i
	incl %ebx		# stride
	incl %ecx		# stride
	incl %edi		# stride
	jmp for
fifor:

# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret