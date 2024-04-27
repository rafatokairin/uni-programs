.macro prints(%string)            		# Define uma macro para imprimir uma string
.data
    	string: .asciiz %string       	# Define a string na seção de dados
.text
    	la $a0, string                	# Carrega o endereço da string em $a0
	li $v0, 4                     		# Carrega o código do syscall para imprimir string em $v0
    	syscall                       	# Chama o syscall para imprimir a string
.end_macro

.macro printd(%int)               		# Define uma macro para imprimir um inteiro
.text
    	move $a0, %int                	# Move o valor do inteiro para $a0
    	li $v0, 1                     	# Carrega o código do syscall para imprimir inteiro em $v0
    	syscall                       	# Chama o syscall para imprimir o inteiro
.end_macro

.macro malloc(%sizeof)        			# Define uma macro para alocação de memória
.text
    	move $a0, %sizeof         		# Move o tamanho desejado para alocar para $a0
    	li $v0, 9               		# Carrega o código do syscall para alocação de memória em $v0
    	syscall                			# Chama o syscall para alocação de memória
.end_macro

.macro return0()             			# Define uma macro para encerrar o programa
.text
    	li $v0, 10                		# Carrega o código do syscall para finalizar o programa em $v0
    	syscall                   		# Chama o syscall para encerrar o programa
.end_macro

.macro criarLista()         			# Define uma macro para alocar uma nova lista
.text 
    	li $t0, 8                	
    	malloc($t0)             
.end_macro

.macro novoNo(%chave)         			# Define uma macro para alocar no
.text
    	li $t0, 8                      
    	malloc($t0)                    
    	sw %chave, 4($v0)      			# Armazena a chave no novo no
.end_macro

.macro scand()                 			# Define uma macro para ler um inteiro do usuário
.text
    	li $v0, 5                 		# Carrega o código do syscall para ler um inteiro em $v0
    	syscall                    		# Chama o syscall para ler um inteiro
.end_macro

.macro inserir(%lista, %chave) 			# Define uma macro para inserir uma chave em uma lista
.data
    	ant_address: .word 0      		# Define uma variável para armazenar o endereço anterior
.text
    	lw $t1, (%lista)          		# Carrega o endereço inicial da lista em $t1
    	bnez $t1, loop             		# Se a lista não estiver vazia, vá para loop
    	novoNo(%chave)            		# Se a lista estiver vazia, cria um novo nó com a chave
    	sw $v0, (%lista)          		# Armazena o endereço do novo nó como início da lista
    	j exit                    		# Sai da macro
loop:
    	sw $t1, ant_address       		# Armazena o endereço atual como o endereço anterior
    	lw $t1, ($t1)              		# Carrega o próximo endereço na lista
    	bnez $t1, loop           		# Se não chegou ao final da lista, continue no loop
    	novoNo(%chave)           		# Se chegou ao final da lista, cria um novo nó com a chave
    	lw $t1, ant_address      		# Carrega o endereço anterior
    	sw $v0, ($t1)              		# Conecta o novo nó ao final da lista
exit:
    	lw $t1, 4(%lista)          		# Carrega o contador de elementos da lista
    	add $t1, $t1, 1            		# Incrementa o contador de elementos
    	sw $t1, 4(%lista)          		# Atualiza o contador na lista
.end_macro

.macro remover(%lista, %chave) 			# Define uma macro para remover uma chave de uma lista
.data
    	ant_address: .word 0     		# Define uma variável para armazenar o endereço anterior
    	rmv_address: .word 0       		# Define uma variável para armazenar o endereço do nó a ser removido
.text
    	lw $t1, (%lista)           		# Carrega o endereço inicial da lista em $t1
    	beqz $t1, exit           		# Se a lista estiver vazia, saia da macro
    	lw $t0, 4($t1)              	# Carrega a chave do primeiro nó da lista em $t0
    	bne $t0, %chave, loop     		# Se a chave não corresponder, vá para loop
	lw $t0, ($t1)              			# Se a chave corresponder, carrega o próximo endereço
    	sw $t0, (%lista)          		# Remove o primeiro nó da lista
    	lw $t0, 4(%lista)         		# Carrega o contador de elementos da lista
    	sub $t0, $t0, 1           		# Decrementa o contador de elementos
    	sw $t0, 4(%lista)           	# Atualiza o contador na lista
    	j exit                    		# Sai da macro
loop:
    	sw $t1, ant_address        		# Armazena o endereço atual como o endereço anterior
    	lw $t1, ($t1)              		# Carrega o próximo endereço na lista
    	beqz $t1, exit            		# Se chegou ao final da lista, saia do loop
    	lw $t0, 4($t1)            		# Carrega a chave do nó atual em $t0
    	bne $t0, %chave, loop      		# Se a chave não corresponder, continue no loop
    	sw $t1, rmv_address        		# Se a chave corresponder, armazena o endereço do nó a ser removido
    	lw $t0, ant_address        		# Carrega o endereço anterior
    	lw $t1, ($t1)              		# Carrega o próximo endereço
    	sw $t1, ($t0)              		# Remove o nó da lista
    	lw $t0, 4(%lista)         		# Carrega o contador de elementos da lista
    	sub $t0, $t0, 1           		# Decrementa o contador de elementos
    	sw $t0, 4(%lista)         		# Atualiza o contador na lista
exit:
.end_macro

.macro imprimir(%lista)       			# Define uma macro para imprimir os elementos de uma lista
.text
    	lw $t0, (%lista)           		# Carrega o endereço inicial da lista em $t0
    	beqz $t0, exit              	# Se a lista estiver vazia, saia da macro
loop:
    	lw $t1, 4($t0)             		# Carrega a chave do nó atual em $t1
    	printd($t1)                		# Imprime a chave
    	lw $t0, ($t0)              		# Carrega o próximo endereço na lista
    	beqz $t0, exit              	# Se chegou ao final da lista, saia do loop
    	prints(" ")                    
    	j loop                    		# Volta ao início do loop
exit:
    	prints("\n")                   
.end_macro

.macro buscar(%lista, %chave) 			# Define uma macro para buscar uma chave em uma lista
.text
    	lw $t0, (%lista)           		# Carrega o endereço inicial da lista em $t0
    	beqz $t0, notFound       		# Se a lista estiver vazia, vá para notFound
loop:
    	lw $t1, 4($t0)              	# Carrega a chave do nó atual em $t1
    	beq $t1, %chave, found     		# Se a chave corresponder, vá para found
    	lw $t0, ($t0)              		# Se a chave não corresponder, carrega o próximo endereço na lista
    	beqz $t0, notFound        		# Se chegou ao final da lista, vá para notFound
    	j loop                    		# Volta ao início do loop
found:
    	prints("Encontrado!\n")       
    	j exit                     		# Sai da macro
notFound:
    	prints("Nao encontrado.\n") 
exit:
.end_macro

.text
main:
    	criarLista()                   	# Chama a macro para criar uma lista
    	move $s0, $v0                 	# Move o endereço da lista para $s0
    	li $s1, 4                      	# Define um valor inicial para $s1
    	jal switch                     	# Chama a sub-rotina 'switch'
    	return0()                      	# Encerra o programa com código de saída 0

switch:
    	prints("\n1. Inserir\n2. Remover\n3. Imprimir\n4. Buscar\n5. Sair\n")
    	scand()                        
    	bge $v0, 5, case5              	# Se a opção for 5 ou mais, vá para case5
case1:
    	bgt $v0, 1, case2              	# Se a opção for maior que 1, vá para case2
    	prints("Digite um valor: ")    
    	scand()                        
    	move $s1, $v0                  	# Move o valor lido para $s1
    	inserir($s0, $s1)               # Chama a macro para inserir o valor na lista
    	j switch                       	# Volta ao início da sub-rotina 'switch'
case2:
    	bgt $v0, 2, case3              	# Se a opção for maior que 2, vá para case3
    	prints("Digite um valor: ")    
    	scand()                        
    	move $s1, $v0                  	# Move o valor lido para $s1
    	remover($s0, $s1)               # Chama a macro para remover o valor da lista
    	j switch                       	# Volta ao início da sub-rotina 'switch'
case3:
    	bgt $v0, 3, case4              	# Se a opção for maior que 3, vá para case4
    	imprimir($s0)                  	# Chama a macro para imprimir a lista
    	j switch                       	# Volta ao início da sub-rotina 'switch'
case4:
    	prints("Digite um valor: ")    
    	scand()                        
    	move $s1, $v0                  	# Move o valor lido para $s1
    	buscar($s0, $s1)                # Chama a macro para buscar o valor na lista
    	j switch                       	# Volta ao início da sub-rotina 'switch'
case5:
    	jr $ra                         	# Retorna para main