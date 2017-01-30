Traducid a ensamblador del x86 la rutina Buscar. Utilizad como base el fichero
Busca.s. Probadla con el fichero Main.c y con la rutina en ensamblador del apartado
anterior (make test2). Entregad en el Racó de la asignatura el fichero Busca.s
-------------------------------------------------------------
 .text
	.align 4
	.globl Buscar
	.type Buscar,@function
Buscar:
        # Aqui viene vuestro codigo
	pushl %ebp
	movl %esp, %ebp
	subl $16, %esp		# variables locales (4 ints)
	movl $-1, -4(%ebp)	# trobat = -1
	movl $0, -16(%ebp)	# low = 0
	movl $0, -8(%ebp)	# mid = 0
	movl 24(%ebp), %eax	# N
	subl $1, %eax		# N-1
	movl %eax, -12(%ebp)	# high = N-1
while:	movl -16(%ebp), %edx	# low
	movl -12(%ebp), %eax	# high
	cmpl %eax, %edx
	jg fiwhile		# fiwhile si low > high
	pushl 8(%ebp)		# pushl @v
	pushl 20(%ebp)		# X.m
	pushl 16(%ebp)		# X.k
	pushl 12(%ebp)		# X.c
	leal -8(%ebp), %eax
	pushl %eax		# &mid
	leal -12(%ebp), %eax
	pushl %eax		# &high
	leal -16(%ebp), %eax
	pushl %eax		# &low
	call BuscarElemento
	addl $28, %esp		# eliminar parametros: 7 pushl's, 28 (4 + 12 + 4 + 4 + 4)
	movl %eax, -4(%ebp)	# trobat = BuscarElemento(...)
if:	cmpl $0, %eax
	jl while		# si < while; si >=, fiwhile
fiwhile: movl -4(%ebp), %eax
	 movl %ebp,%esp
	 popl %ebp
	 ret
-------------------------------------------------------------
alumne@linuxFIB:~/AC/Fibernalia> make test2
gcc -g -Wall -o Sesion04-2 Main.c Asignar.c Busca.s BuscaElemento.s Insertar.c Intercambiar.c Ordenar.c Volcar.c elemento.h
alumne@linuxFIB:~/AC/Fibernalia> ./Sesion04-2
...
6 encontrado en 7
30 encontrado en 13