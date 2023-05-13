#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main(void) {
  
char *NomeArquivo = "entrada.txt", numeros[100];
int k, n, valores[100];
  
LerArquivo(NomeArquivo, &k, &n, numeros);
  
printf("%d\n", k);
printf("%d\n", n);
printf("%s\n", numeros);

ConverterStrInt(numeros, valores);



return 0;
  
}