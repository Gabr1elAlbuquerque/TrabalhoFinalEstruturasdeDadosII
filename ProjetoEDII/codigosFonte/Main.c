#include "Funcoes.h"

int main(int argc, char *argv[]) {
	
	int QtdNumeros = 130000;
	int TamanhoVetor = QtdNumeros * 10 + 1;
    char *Numeros = malloc(TamanhoVetor * sizeof(char));
    
    int k = 0, n = 0;

    FILE *entrada = fopen(argv[1], "r");
    
    LerEntrada(entrada, &k, &n, Numeros);
    fclose(entrada);
    
    Arvore *a = ArvoreNovo();

    ConverterStrArvore(Numeros,a, n);
    
    char *ArvoreConcatenada = ConcatenaStringArvore(a);
    
	ContarCombinacoesRepetidas(ArvoreConcatenada,k);
	
	LiberaArvore(a);
	
    return 0;
}
