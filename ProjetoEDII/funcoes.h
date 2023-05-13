#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LerArquivo(char* nome_arquivo, int* k, int* n, char* numeros) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fscanf(arquivo, "%d %d %s", k, n, numeros);
    fclose(arquivo);
}

#endif