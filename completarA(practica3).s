Dada una rutina que tiene el siguente código en alto nivel:
int OperaVec(int Vector[], int elementos) {
    // La @ de Vector esta en la @ 8[ebp] y el
    // valor de la variable elementos en la @ 12[ebp]
    int i; // i esta en la @ -8[ebp]
    int res; // res esta en la @ -4[ebp]
    res=Vector[0];
    // Código que has de introducir
    for (i=1;i<elementos;i++)
        if (Vector[i]<res)
            res=Vector[i];
    // Fin del código a introducir
    return res;
}
Traduce el interior de la rutina a ensamblador y ponlo dentro del código Practica3CompletarA.s.
Ejecútalo con el programa Practica3MainA.c y, cuando funcione, calcula cuántos
ciclos tarda, cuántas instrucciones ejecuta y cuál es el CPI resultante. Entregad en el
Racó de la asignatura el fichero Practica3CompletarA.s.
-------------------------------------------------------------
.text
	.align 4
	.globl OperaVec
	.type	OperaVec, @function
OperaVec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	8(%ebp), %eax		
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)		# res = Vector[0]
# Aqui has de introducir el codigo
	movl 	$1, -8(%ebp)		# i = 1
	movl 	8(%ebp), %ecx		# @Vector
for:	movl 	-8(%ebp), %eax		# %eax = i
	cmpl 	12(%ebp), %eax
	jge 	fifor			# salta si i >= elementos
	movl	(%ecx, %eax, 4), %ebx
if:	cmpl 	-4(%ebp), %ebx
	jge 	fiif			# salta si Vector[i] >= res
	movl	%ebx, -4(%ebp)		# res = Vector[i]	
fiif:	incl 	-8(%ebp)
	jmp 	for
fifor:	
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
# alumne@linuxFIB:~/AC/Fibernalia> gcc Practica3MainA.c Practica3CompletarA.s -o operavec
# alumne@linuxFIB:~/AC/Fibernalia> ./operavec
# Ciclos = 52814265.000000
# OperaVec BIEN programado.