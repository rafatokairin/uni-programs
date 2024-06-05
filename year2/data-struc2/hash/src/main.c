#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/cadastro.h"
#include "../headers/aberto.h"
#include "../headers/separado.h"

int main() {
    Lista tabelaSeparada[TAM];
    Produto tabelaAberta[TAM];
    iniSeparado(tabelaSeparada);
    iniAberto(tabelaAberta);
    menu(tabelaSeparada, tabelaAberta);
    destruirSeparado(tabelaSeparada);
    return 0;
}