Algoritmo tc06;
Variaveis
    inteiro: i,j,k;

Procedimento teste1(x,y);
   inteiro: x;
   inteiro: y;
inicio
    i<-+i+1 div x;
    j<--j+1 * y;
    K<-+k-1 / x * y;
fim;

Procedimento teste2;
inicio
   i<-i-1;
   J<-J-1;
   k<-k-1;
fim;

Inicio
    i<-1;j<-1;k<-1;
    se(i<11) entao
       teste1(1+1*3,i);
    fim se;
    se nao(j<=k) entao
       se (i+j)>5 entao teste2; fim se;
    senao
        se j>0 entao teste1(1+1*3,i) { falta ; } senao teste2 { falta ; } fim se;
    fim se;
Fim.

