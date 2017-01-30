Traducid a ensamblador del x86 la rutina BuscarElemento. Utilizad como base el
fichero BuscaElemento.s y comprobad el resultado con ayuda de los ficheros Main.c
y Buscar.c (podéis usar make test1 para compilar). Entregad en el Racó de la
asignatura el fichero BuscaElemento.s.
-------------------------------------------------------------
 .text
	.align 4
	.globl BuscarElemento
	.type BuscarElemento,@function
BuscarElemento:
        # Aqui viene vuestro codigo
	pushl %ebp
	movl %esp,%ebp
if:	movl 16(%ebp),%eax	# mid = @ a la que apunta mid
	movl (%eax),%eax	# *mid
	movl 32(%ebp),%ecx	# @v
	imul $12,%eax		# *mid x 12 (tamaño struct)
	addl %eax,%ecx		# @v + *mid x 12 = @v[*mid]
	movl 24(%ebp),%eax	# X.k
	cmpl 4(%ecx),%eax
	jne elseif		# elseif si X.k != v[*mid].k
	movl 16(%ebp),%eax	# # mid = @ a la que apunta mid
	movl (%eax),%eax	# return *mid
	jmp end
elseif:	movl 16(%ebp),%eax	# mid = @ a la que apunta mid
	movl 12(%ebp),%ecx	# high = @ a la que apunta high
	movl (%ecx),%ecx	# *high
	cmpl %ecx,(%eax)
	jge else		# else si *mid >= *high
	movl %ecx,(%eax)	# *mid = *high
	movl 8(%ebp),%eax	# low = @ a la que apunta low
	addl $1,(%eax)		# (*low)++
	jmp elsend
else:	movl 8(%ebp),%ecx	# low = @ a la que apunta low
	movl (%ecx),%ecx	# *low
	movl %ecx,(%eax)	# *mid = *low
	movl 12(%ebp),%eax	# high = @ a la que apunta high
	subl $1,(%eax)		# (*high)--
elsend: movl $-1,%eax		# return -1
end:	movl %ebp,%esp
	popl %ebp
	ret
-------------------------------------------------------------
alumne@linuxFIB:~/AC/Fibernalia> make test1
gcc -g -Wall -o Sesion04-1 Main.c Asignar.c Buscar.c BuscaElemento.s Insertar.c Intercambiar.c Ordenar.c Volcar.c elemento.h
alumne@linuxFIB:~/AC/Fibernalia> ./Sesion04-1
...
6 encontrado en 7
30 encontrado en 13