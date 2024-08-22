Algoritmo tc09;

//Declaracao de Variaveis
Variaveis
     inteiro: a,x,y;
     REAL: valor;
     tipo vetor_inteiro = vetor[1:10] inteiro;
     tipo matriz_real = matriz[1:10,1:10] real;
     vetor_inteiro: vet;
     matriz_real: mat;
     logico: sera_verdade;
     caractere: frase;

//Declaracao de Procedimento
procedimento proc;
inicio
    i <- 1;
    i <- i / 3;
fim;    

//Declaracao de Procedimento com variaveis locais
Procedimento procVar;
variaveis
    inteiro: i;
inicio
    i <- 1;
fim;

//Declaracao de Procedimento com parametros e variaveis locais
Procedimento procParVar(a,b,c,d);
    inteiro: a;
    inteiro: b;
    real: c;
    tipo vet=vetor[1:10] inteiro;
    vet: d;
variaveis
    inteiro: i;
inicio
    i <- 1;
fim;

//Declaracao de Funcao
Funcao Fatorial(n):inteiro;
    inteiro: n;
variaveis
    inteiro: aux;
Inicio
    aux <- 0;
    
    se(n=0) entao
        Fatorial <- 0;
    senao
        se n = 1 entao
            Fatorial <- 1;
        senao
            Fatorial <- n*Fatorial(n-1);
        fim se;
    fim se;
fim;


procedimento proc;
variaveis
    tipo m = matriz[1:3,1:2] inteiro;
    m: M1;
    inteiro: I,J;
inicio
    M1[1,1] <- 1;
    M1[1,2] <- 2;
    M1[2,1] <- 3;
    M1[2,2] <- 4;
    M1[3,1] <- 5;
    M1[3,2] <- 6;
    
    M1[1,1] <- M1[1,3];

    frase <- "Eu sou o Portugol";
    imprima(frase);
    imprima(frase,": Versao - ",1.0);

    imprima(M1);
    para I de 1 ate 2 faca
        para J de 1 ate 3 faca
            imprima(M1[J,I]);
        fim para;
    fim para;
fim;

procedimento TestaParametros(a,b,c);
    inteiro: a,b,c;
variaveis
    real: r;
inicio
    imprima(M1);
    para I de 1 ate 2 faca
        para J de 1 ate 3 faca
            imprima(M1[J,I]);
        fim para;
    fim para;
    se a>b entao
        a <- +b;
    fim se;
fim;

Inicio
    sera_verdade <- verdadeiro;
    sera_verdade <- falso;
    i <- 666;
    v[34] <- 666 div 3;
    i <- +5+(+5);
    
    proc;
    TestaParametros(a,b,c);
    Fatorial(6);
    
    se i entao
        se i entao
            se i entao
                i <- 0;        
            senao
                i <- 1;
            fim se;
        fim se;
    fim se;

    se i entao
        i <- -1;
    fim se;

    se i entao
        i <- 0;
    senao
        i <- 1;
    fim se;
    
    enquanto i faca
        i <- i+1;
    fim enquanto;
        
    para i de 1 ate 10 faca
       v[i] <- 0;
       mat[5,5] <- 0.5;
    fim para;

    para i de 1 ate 100 passo 2 faca
       a <- i+1-4*5<d>=8;
    fim para;
    
    
    repita
        a <- i;
        a <- 666;
    ate i;
    
    
    leia(i);
    imprima(i);

    se a > 15 entao
        x <- x*4;
        y <- y+3;
    senao
        se a > 10 entao
            x <- x*3;
            y <- y+2;
        senao
            se a > 5 entao
                x <- x*2;
                y <- y+1;
            senao
                x <- 0;
                y <- 0;
            fim se;
        fim se;
    fim se;
    se((a>x)e((x<y)ou(i=j))) entao
        vet[3] <- a>=9;
    fim se;
    enquanto (a>4) faca
       i <- 4;
    fim enquanto;

    para i de 0 ate 10 passo 1 faca
         vet[i] <- 0;
    fim para;

    repita 
        vet[i] <- vet[i] div 1;
    ate x>1;
    
    imprima("Oi mundo");
    leia(a);
    
    frase <- "Eu sou o Portugol";
    imprima(frase);
    imprima(frase,": Versao - ",1.0);
Fim.
