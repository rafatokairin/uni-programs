.data
squares: .space 256 		# espaco para 64 inteiros (cada inteiro ocupa 4 bytes)

.text
main:
	li $v0, 5           	# instrucao ler valor
	syscall
	move $t0, $v0       	# copiar valor para $t0

	li $t1, 0           	# carregar 0 em $t1(índice)
	li $t2, 0           	# carregar 0 em $t2(soma dos quadrados)

loop:
	mul $t3, $t1, $t1   	# $t3(quadrado) = índice * índice
	mul $t4, $t1, 4	 	# $t4(endereco) = $t1 * 4
	sw $t3, squares($t4)	# armazena quadrado em squares no endereço calculado
	add $t2, $t2, $t3   	# $t2 = $t2 + $t3
	addi $t1, $t1, 1    	# índice = índice + 1
	bne $t1, $t0, loop  	# desviar para loop, se índice != número

print_result:
	move $a0, $t2        	# copiar soma em $a0
	li $v0, 1            	# instrucao imprimir inteiro
	syscall

exit_program:
	li $v0, 10           	# encerrar programa
	syscall