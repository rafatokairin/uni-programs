#include "../headers/rb.h"
#include "../headers/rb_aux.h"

int main() 
{
    Raiz T;
    T.nil = (No *)malloc(sizeof(No));
    T.nil->cor = BLACK;
    T.raiz = T.nil;
    menu(&T);
    return 0;
}