.data
	vetor: .word -2, 4, 7, -3, 0, -3, 5, 6
	size: .word 8
	soma_positivos: .word 0
	soma_negativos: .word 0
	str_positivos: .asciiz "A soma dos valores positivos = "
	str_negativos: .asciiz "\nA soma dos valores negativos = "

.text
main:
	# inicializar registradores
	la $t0, vetor       		# carregar endereco vetor
	lw $t1, size			# carregar dados de size
	lw $t2, soma_positivos		# carregar dados de soma_positivos
	lw $t3, soma_negativos		# carregar dados de soma_negativos

loop:
	lw $t4, 0($t0)			# carregar valor atual do vetor em $t4
	bgez $t4, valor_positivo	# desviar para valor_positivo se $t4 >= 0
	add $t3, $t3, $t4		# se $t4 é negativo, some a soma_negativos
	j next_iteration		# desviar para next_iteration

valor_positivo:
	add $t2, $t2, $t4 		# se $t4 é positivo, some a soma_positivos

next_iteration:
	addi $t0, $t0, 4  		# avancar para próximo elemento do vetor
	addi $t1, $t1, -1   		# decrementar size
	bnez $t1, loop      		# se size != 0, continue o loop

print_result:
	li $v0, 4			# instrucao imprimir String
	la $a0, str_positivos		# String soma positivos
	syscall
	li $v0, 1			# instrucao imprimir inteiro
	move $a0, $t2			# copiar valor de $t2(soma positivos) para $a0
	syscall

	li $v0, 4			# instrucao imprimir String
	la $a0, str_negativos		# String soma negativos
	syscall
	li $v0, 1			# instrucao imprimir inteiro
	move $a0, $t3			# copiar valor de $t3(soma negativos) para $a0
	syscall

exit_program:
	li $v0, 10 			# encerrar programa
	syscall