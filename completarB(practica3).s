Dada una rutina que tiene el siguente código en alto nivel:
#define N 3
int OperaMat(int Matriz[N][N], int salto) {
    // La @ de Matriz esta en la @ 8[ebp] y el
    // valor de la variable salto en la @ 12[ebp]
    int j; // j esta en la @ -12[ebp]
    int i; // i esta en la @ -8[ebp]
    int res; // res esta en la @ -4[ebp]
    // Codigo que has de introducir
    res=0;
    for (i=0; i <3; i+=salto)
        for (j=0; j <3; j++)
            res-=Matriz[i][i]+j;
    // Fin del codigo a introducir
    return res;
}
Traduce el interior de la rutina a ensamblador y ponlo dentro del código Practica3CompletarB.s.
Ejecútalo con el programa Practica3MainB.c y, cuando funcione, calcula cuántos
ciclos tarda, cuántas instrucciones ejecuta y cuál es el CPI resultante. Entregad en el
Racó de la asignatura el fichero Practica3CompletarB.s.
-------------------------------------------------------------
.text
	.align 4
	.globl OperaMat
	.type	OperaMat, @function
OperaMat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
# Aqui has de introducir el codigo
	movl 8(%ebp), %ebx		# %ebx = @Matriz
	movl $0, -4(%ebp)		# res = 0
	movl $0, -8(%ebp)		# i = 0
fori: 	movl -8(%ebp), %eax		# %eax = i
	cmpl $3, %eax		
	jge fifori			# salta si i >= 3
	movl $0, -12(%ebp)		# j = 0
forj:	movl -12(%ebp), %ecx		# %ecx = j
	cmpl $3, %ecx
	jge fiforj			# salta si j >= 3
	imul $3, %eax, %edx 		# %edx = 3 * i
	addl %eax, %edx			# %edx = (3 * i) + i
	movl (%ebx, %edx, 4), %edx	# %edx = Matriz[i][i]
	addl %ecx, %edx			# %edx = Matriz[i][i] + j
	movl -4(%ebp), %esi		# %esi = res
	subl %edx, %esi			# res = res - Matriz[i][i] + j
	movl %esi, -4(%ebp)	
	incl -12(%ebp)			# ++j
	jmp forj
fiforj:
	addl 12(%ebp), %eax	
	movl %eax, -8(%ebp)		# i += salto
	jmp fori
fifori:
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx	
	movl %ebp,%esp
	popl %ebp
	ret
# alumne@linuxFIB:~/AC/Fibernalia> gcc Practica3MainB.c Practica3CompletarB.s -o operamat
# alumne@linuxFIB:~/AC/Fibernalia> ./operamat
# Ciclos = 48083025.000000
# OperaMat BIEN programado.