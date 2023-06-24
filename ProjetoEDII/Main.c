#include "Funcoes.h"
int main(int argc, char *argv[]) {
	
	int QtdNumeros = 130000;
	int TamanhoVetor = QtdNumeros * 10 + 1;
    char *Numeros = malloc(TamanhoVetor * sizeof(char));
    
    int k = 0, n = 0;

    FILE *arquivo = fopen(argv[1], "r");
    LerArquivo(arquivo, &k, &n, Numeros);
    fclose(arquivo);

    printf("Valor de K: %d\n", k);
    printf("Valor de N: %d\n", n);
    printf("Arvore Inicio:\n");
    
    Arvore *a = ArvoreNovo();

    ConverterStrArvore(Numeros,a, n);
    char *Concatenado = ConcatenaStringArvore(a);
	MostreArvoreBin(a);
	printf("String Concatenada: %s", Concatenado);
	LiberaArvore(a);
    return 0;
}
