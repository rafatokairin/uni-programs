#include "../headers/esparsa.h"
#include "../headers/operacoes.h"
#include <stdlib.h>

int main()
{
    Matriz A, B, C;
    criar(&A); criar(&B); criar(&C);
    lerMatrizes(&A, &B);
    operacoes(&A, &B, &C);
    // libera primeiro arranjo
    free(A.arranjo); free(B.arranjo); free(C.arranjo);
    return 0;
}