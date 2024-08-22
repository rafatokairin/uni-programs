Algoritmo tc08;
Variaveis
    inteiro: i,j,k;
Procedimento p1(p1_par1,p1_par2,p1_par3);
    inteiro: p1_par1;
    logico: p1_par2;
    real: p1_par3;
inicio
    i<-i*1;
    j<-j*p1_par1;
    k<-k*1;
    i<-i*666;
    teste1_1(i);
    k<-k+1;
fim;

Procedimento p2(k);
    logico: k;
inicio
    i<-i-1;
    se k entao j<-j-1; fim se;
    k<-k ou verdadeiro;
fim;

Inicio
    i<-666;j<-666;k<-666;
    se i<666 entao
        p1(1,2,falso);
    fim se;
    se nao(j<=k) entao
        se (i+j)>666 entao p2(i>j); //FALTA: fim se;
    senao
        se j>0 entao p1(i+1,i+2,j<3); senao p2(0=0); fim se;
    fim se;
Fim.

