#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, char **argv) {
  
char numeros[100];
int k, n, valores[100], *cont = 0;

FILE* arquivo = fopen(argv[1], "r");
LerArquivo(&arquivo, &n, numeros);
  
printf("%d\n", k);
printf("%d\n", n);
printf("%s\n", numeros);

ConverterStrInt(numeros, valores, cont);

for(int i = 0; i < *cont; i++){
  printf("%d\n", valores[*cont]);
}

return 0;
  
}
