#include "Funcoes.h"
int main(int argc, char *argv[]) {
	
	int QtdNumeros = 130000;
	int TamanhoVetor = QtdNumeros * 10 + 1;
    char *numeros = malloc(TamanhoVetor * sizeof(char));
    
    int k = 0, n = 0;

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
	printf("%d\n", a->Tamanho);
    return 0;
}
