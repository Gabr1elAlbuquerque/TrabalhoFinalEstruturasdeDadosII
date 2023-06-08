#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LerArquivo(FILE *arquivo, int *k, int *n, char *numeros) {
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d %d %s", k, n, numeros);
}

void ConverterStrInt(char *numeros, int *valores, int *cont) {
    char *token;
    int contador = 0;
    *cont = 0;

    token = strtok(numeros, ";");
    while (token != NULL) {
        valores[contador] = atoi(token);
        contador++;
        *cont = contador;
        token = strtok(NULL, ";");
    }
}

#endif
