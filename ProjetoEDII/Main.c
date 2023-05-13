#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main() {
char *NomeArquivo = "entrada.txt", numeros[100];
int k, n;
LerArquivo(NomeArquivo, &k, &n, numeros);
printf("%d\n", k);
printf("%d\n", n);
printf("%s\n", numeros);
return 0;
}