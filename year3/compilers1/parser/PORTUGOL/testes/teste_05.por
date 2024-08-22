algoritmo tc05;
variaveis
    inteiro: i,j,j;
inicio
    i<-1;j<-i;k<-1;
    SE(i<11) ENTAO
       i<-i+5;
    FIM SE;
    se nao(j<=k) entao
        se(i+j)>5 entao i<-0;fim se;
    senao
      se j>0 entao j<-0; senao j<-10000; fim se;
    fim se;
fim.

