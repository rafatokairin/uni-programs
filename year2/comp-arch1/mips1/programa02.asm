.data
	str_A: .asciiz "Digite o valor de A: "
	str_B: .asciiz "Digite o valor de B: "
	result: .asciiz "Multiplos de A no intervalo [A, AxB]: "
	space: .asciiz " "

.text
main:
	li $v0, 4			# instrucao imprimir String
	la $a0, str_A			# carregar endereco str_A para $a0
	syscall
	li $v0, 5			# instrucao ler A
	syscall
	move $t0, $v0			# copiar A para $t0
	blez $t0, exit_program		# desviar para exit_program se $t0(A) <= 0

	li $v0, 4			# instrucao imprimir String
	la $a0, str_B			# carregar endereco str_B para $a0
	syscall
	li $v0, 5			# instrucao ler B
	syscall
	move $t1, $v0			# copiar B para $t1
	blez $t1, exit_program		# desviar para exit_program se $t1(B) <= 0

	li $v0, 4			# instrucao imprimir String
	la $a0, result			# carregar endereco result para $a0
	syscall
    
	li $t2, 1 			# carregar imediato inteiro 1 para $t2(contador)
	mul $t3, $t0, $t1		# $t3 = A * B
    
print_multiples:
	mul $t4, $t0, $t2 		# $t4(multiplo de A) = A * contador
	bgt $t4, $t3, exit_program 	# desviar para exit_program se multiplo de A >= AxB

	li $v0, 1			# instrucao imprimir inteiro
	move $a0, $t4			# copiar multiplo de A para $a0
	syscall

	li $v0, 4			# instrucao imprimir String
	la $a0, space			# carregar endereco space para $a0
	syscall

	addi $t2, $t2, 1		# contador = contador + 1
	j print_multiples

exit_program:
	li $v0, 10			# encerrar programa
	syscall