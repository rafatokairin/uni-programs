.data
    str_perfect: .asciiz "Eh perfeito!"
    str_not_perfect: .asciiz "Nao perfeito."

.text
main:
	li $v0, 5       		# instrucao ler valor
	syscall         
	move $t0, $v0   		# copiar valor para $t0

	li $t1, 1       		# carregar 1(primeiro divisor) em $t1
	li $t2, 0       		# carregar 0 em $t2(soma de divisores)

loop:
	beq $t1, $t0, check_perfect  	# desviar para check_perfect, se $t1 == $t0
	divu $t3, $t0, $t1          	# $t3 = $t0 / $t1
	mfhi $t4                    	# $t4 = hi(resto da divisao)
	beqz $t4, add_divisor       	# desviar para add_divisor, se resto == 0
	j next_divisor               	# senao desviar para next_divisor

add_divisor:
	add $t2, $t2, $t1          	# $t2 = $t2 + $t1
	j next_divisor               	# desviar para next_divisor

next_divisor:
	addi $t1, $t1, 1           	# $t1(divisor) = $t1 + 1
	j loop                     	# desviar para loop

check_perfect:
	beq $t0, $t2, perfect    	# desviar para perfect, se valor == $t2(soma de divisores)
	j not_perfect               	# senao desviar para not_perfect

perfect:
	li $v0, 4       		# instrucao imprimir String
	la $a0, str_perfect		# carregar endereco str_perfect para $a0
	syscall
	j exit_program              	# desviar para exit_program

not_perfect:
	li $v0, 4       		# instrucao imprimir String
	la $a0, str_not_perfect		# carregar endereco str_not_perfect para $a0
	syscall

exit_program:
        li $v0, 10      		# encerrar programa
        syscall