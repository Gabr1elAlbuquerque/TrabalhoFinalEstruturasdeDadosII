#include "Funcoes.h"
int main(int argc, char *argv[]) {
    char numeros[1000000];
    int k, n;

    FILE *arquivo = fopen(argv[1], "r");
    LerArquivo(arquivo, &k, &n, numeros);
    fclose(arquivo);

    printf("%d\n", k);
    printf("%d\n", n);
    printf("Arvore Inicio:\n");
    
    
    Arvore *a = ArvoreNovo();

    ConverterStrArvore(numeros,a, n);
    MostreArvore(a);
    //printf("Arvore em binário:\n");
	MostreArvoreBin(a);
    return 0;
}
