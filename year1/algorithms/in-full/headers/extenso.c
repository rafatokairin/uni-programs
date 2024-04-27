#include "extenso.h"
#include <stdio.h>
#include <string.h>

void extenso(double numero)
{
    if (numero > 0 && numero < 10000)
    {
        char *unidades[10] = {"", "um ", "dois ", "tres ", "quatro ", "cinco ", "seis ", "sete ", "oito ", "nove "};
        char *dez_vinte[10] = {"", "onze ", "doze ", "treze ", "quatorze ", "quinze ", "dezesseis ", "dezessete ", "dezoito ", "dezenove "};
        char *dezenas[10] = {"", "dez ", "vinte ", "trinta ", "quarenta ", "cinquenta ", "sessenta ", "setenta ", "oitenta ", "noventa "};
        char *centenas[10] = {"", "cento ", "duzentos ", "trezentos ", "quatrocentos ", "quinhentos ", "seiscentos ", "setecentos ", "oitocentos ", "novecentos "};
        char extenso[100] = "";

        // calculo dos numerais em suas respectivas casas
        int pos_milhar = (int)numero / 1000;
        int pos_centenas = ((int)numero % 1000) / 100;
        int pos_dezenas = ((int)numero % 100) / 10;
        int pos_unidades = (int)numero % 10;
        int cmp_decimos = ((numero - (int)numero) * 100 + 0.5);
        int pos_decimos = cmp_decimos / 10;
        int pos_centesimos = cmp_decimos % 10;

        // concatenando milhar
        if (pos_milhar > 0)
        {
            strcat(extenso, unidades[pos_milhar]);
            strcat(extenso, "mil ");
        }
        if (pos_milhar > 0 && pos_centenas > 0 && pos_dezenas == 0 && pos_unidades == 0) strcat(extenso, "e ");
        // concatenando centenas
        if (pos_centenas == 1 && pos_dezenas == 0 && pos_unidades == 0) strcat(extenso, "cem ");
        else if (pos_centenas > 0) strcat(extenso, centenas[pos_centenas]);
        // concatenando dezenas
        if ((pos_milhar != 0 || pos_centenas != 0) && pos_dezenas != 0) strcat(extenso, "e ");
        if (pos_dezenas == 1 && pos_unidades != 0) strcat(extenso, dez_vinte[pos_unidades]);
        else strcat(extenso, dezenas[pos_dezenas]);
        // concatenando unidades
        if ((pos_milhar != 0 || pos_centenas != 0 || pos_dezenas != 0) && pos_unidades != 0 && pos_dezenas != 1) strcat(extenso, "e ");
        if (pos_unidades > 0 && pos_dezenas != 1) strcat(extenso, unidades[pos_unidades]);
        // concatenando reais (um real)
        if (pos_milhar != 0 || pos_centenas != 0 || pos_dezenas != 0 || pos_unidades > 1) strcat(extenso, "reais ");
        else if (pos_unidades == 1) strcat(extenso, "real ");
        // concatenando decimos
        if ((pos_milhar > 0 || pos_centenas > 0 || pos_dezenas > 0 || pos_unidades > 0) && (pos_decimos != 0 || pos_centesimos != 0)) strcat(extenso, "e ");
        if (pos_decimos == 1 && pos_centesimos != 0) strcat(extenso, dez_vinte[pos_centesimos]);
        else strcat(extenso, dezenas[pos_decimos]);
        // concatenando centesimos
        if (pos_decimos != 0 && pos_decimos != 1 && pos_centesimos != 0) strcat(extenso, "e ");
        if (pos_centesimos > 0 && pos_decimos != 1) strcat(extenso, unidades[pos_centesimos]);
        // concatenando centavos (um centavo)
        if (pos_decimos != 0 || pos_centesimos > 1) strcat(extenso, "centavos ");
        else if (pos_centesimos == 1) strcat(extenso, "centavo ");
        printf("%s\n", extenso);
    }
}