#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "checkPassword.h"

// Função que tenta descobrir três caracteres da senha
void verificar_faixa(int start, char *resultado) {
    char tentativa[4] = {0}; // 3 caracteres + null
    for (int c1 = 33; c1 <= 126; c1++) {
        for (int c2 = 33; c2 <= 126; c2++) {
            for (int c3 = 33; c3 <= 126; c3++) {
                tentativa[0] = c1;
                tentativa[1] = c2;
                tentativa[2] = c3;
                if (checkPassword(tentativa, start) == 0) {
                    resultado[0] = c1;
                    resultado[1] = c2;
                    resultado[2] = c3;
                    resultado[3] = '\0';
                    printf("Processo %d encontrou %d-%d: %s\n", getpid(), start, start+2, resultado);
                    return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int usar_fork = (argc > 1 && strcmp(argv[1], "-f") == 0);
    char senha[13] = {0};

    printf("Processo %d quebrando a senha...\n", getpid());

    if (!usar_fork) {
        // Sem fork(), verificando em sequência
        verificar_faixa(0, &senha[0]);
        verificar_faixa(3, &senha[3]);
        verificar_faixa(6, &senha[6]);
        verificar_faixa(9, &senha[9]);
    } else {
        // Com fork(), criando 4 processos
        for (int i = 0; i < 4; i++) {
            int pid = fork();
            if (pid == 0) { // Código do filho
                verificar_faixa(i * 3, &senha[i * 3]);
                exit(0);
            } else if (pid < 0) {
                perror("Erro ao criar o processo filho");
                exit(1);
            }
        }
        // Processo pai aguarda os filhos
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
    }
    
    return 0;
}
