.data
base_str: .asciiz "\nDigite base: "
exp_str: .asciiz "\nDigite expoente: "
res_str: .asciiz "\nResultado: "

.text
.globl main

main:
    li $v0, 4
    la $a0, base_str
    syscall
    li $v0, 5
    syscall
    move $s0, $v0 
    li $v0, 4
    la $a0, exp_str
    syscall
    li $v0, 5
    syscall
    move $s1, $v0 
    move $a0, $s0 
    move $a1, $s1 
    jal potencia
    move $s2, $v0 
    li $v0, 4
    la $a0, res_str
    syscall
    li $v0, 1
    move $a0, $s2
    syscall
    li $v0, 10
    syscall

potencia:
    addi $sp, $sp, -8 
    sw $ra, 4($sp)    
    sub $a1, $a1, 1   
    jal potencia       
    lw $ra, 4($sp)   
    addi $sp, $sp, 8  
    mul $v0, $a0, $v0 
    jr $ra           

caso_base:
    li $v0, 1          
    jr $ra          