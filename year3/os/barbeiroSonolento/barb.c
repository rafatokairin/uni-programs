/*
Condicoes:
    1. Um barbeiro, uma cadeira de barbeiro em uma sala de corte
    e uma sala de espera contendo um numero especifico de cadeiras 
    para clientes aguardarem

    2. Cada cliente, ao chegar, verifica o que o barbeiro esta fazendo.
    Se o barbeiro estiver dormindo, o cliente acorda o barbeiro e se
    senta na cadeira de sala do corte

    3. Se o barbeiro estiver ocupado cortando o cabelo de um cliente,
    o cliente que chegou permanece na sala de espera e aguarda sua vez

    4. Quando o barbeiro termina o cabelo de um cliente, ele dispensa o
    cliente finalizando o corte e vai a sala de espera para verificar se
    ha outros clientes aguardando o corte. Se houver alguem esperando,
    ele traz um deles para a sala de corte

    5. Se um cliente entra na barbearia e todas as cadeiras estao
    ocupadas, o cliente vai embora
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#define N_CADEIRAS 3
// TOTAL CADEIRAS = N_CADEIRAS + CADEIRA_BARBEIRO
int begin = 0, end = 0, size = 0, fila[N_CADEIRAS + 1];

/*
Mutual Exclusion para garantir a sincronizacao entre threads, 
impedindo que outras threads acessem a fila ao mesmo tempo
*/
pthread_mutex_t travaFila;

// Verifica se a fila esta vazia
int vazio() {
    return !size;
}

// Adiciona cliente na fila
void enqueue(int cliente) {
    if (size < N_CADEIRAS + 1) {
        if (vazio())
            printf("Cliente %d acorda barbeiro e senta na cadeira de corte\n", cliente);
        else
            printf("Cliente %d senta em uma das cadeiras vagas da sala de espera\n", cliente);
        fila[end] = cliente;
        end = (end + 1) % (N_CADEIRAS + 1);
        size++;
    }
    else
        printf("Todas as cadeiras ocupadas, cliente %d foi embora\n", cliente);
}

// Corte de cabelo pelo barbeiro
int denqueue() {
    if (!vazio()) {
        srand(time(NULL));
        sleep(rand() % 4 + 1); // Intervalo de tempo corte cabelo
        printf("Barbeiro termina corte do cliente %d, que vai embora\n", fila[begin]);

        int cliente = fila[begin];
        begin = (begin + 1) % (N_CADEIRAS + 1);
        size--;

        if (vazio())
            printf("Nao ha clientes para atender. Barbeiro dorme\n");
        else
            printf("Barbeiro chama cliente %d, que senta na cadeira de corte\n", fila[begin]);
        return cliente;
    }
    else
        return -1; // Barbeiro dormindo, portanto nada ocorre e a funcao retorna -1 como ERRO
}

// Acao cliente chegando
void *cliente(void *arg) {
    unsigned long id_cliente = *((unsigned long*) arg);
    pthread_mutex_trylock(&travaFila);
    enqueue(id_cliente);
    pthread_mutex_unlock(&travaFila);
    return NULL;
}

// Acao barbeiro cortando cabelo
void *barbeiro(void *arg) {
    while (1) {
        pthread_mutex_trylock(&travaFila);
        denqueue();
        pthread_mutex_unlock(&travaFila);
    }
}

int main() {
    pthread_mutex_init(&travaFila, NULL);
    int i = 0;
    pthread_t threadBarbeiro, threadCliente;
    pthread_create(&threadBarbeiro, NULL, barbeiro, NULL);
    srand(time(NULL));
    while (1) {
        sleep(rand() % 4 + 1); // Intervalo de tempo chegada de clientes
        pthread_create(&threadCliente, NULL, cliente, &i);
        i++;
    }
    return 0;
}