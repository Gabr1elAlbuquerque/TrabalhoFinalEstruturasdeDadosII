#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>


void LerArquivo(void){
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("entrada.txt","r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
    }
    while (fgets(linha,100,arquivo) != NULL)
    {
       printf("%s", linha);
    }
    
    fclose(arquivo);
}

#endif