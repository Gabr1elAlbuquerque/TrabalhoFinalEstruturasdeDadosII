#include "Funcoes.h"
int main(int argc, char *argv[]) {
    char numeros[1000000];
    int k, n;

    FILE *arquivo = fopen(argv[1], "r");
    LerArquivo(arquivo, &k, &n, numeros);
    fclose(arquivo);

    printf("Valor de K: %d\n", k);
    printf("Valor de N: %d\n", n);
    printf("Arvore Inicio:\n");
    
    Arvore *a = ArvoreNovo();

    ConverterStrArvore(numeros,a, n);
	MostreArvoreBin(a);
	LiberaArvore(a);
	
    return 0;
}
