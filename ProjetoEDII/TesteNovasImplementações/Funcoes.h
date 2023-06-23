#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NoArvore{
	int valor;
	unsigned long long binario;
	char *BinarioString;
	struct NoArvore *E;
	struct NoArvore *D;
}NoArvore;

typedef struct Arvore{
	NoArvore *Raiz;
	int Tamanho;
}Arvore;


Arvore * ArvoreNovo(void){
    Arvore *a = (Arvore*)malloc(sizeof(Arvore));
    if(a != NULL){
        a->Raiz = NULL;
        a->Tamanho = 0;
    }
    return a;
}
unsigned long long ConverterBinario(unsigned long long Num) {
    unsigned long long ValorBinario = 0;
    unsigned long long Posicao = 1;

    while (Num > 0) {
        ValorBinario += (Num % 2) * Posicao;
        Num /= 2;
        Posicao *= 10;
    }

    return ValorBinario;
}

char* ConverterBinString(unsigned long long Num, int N) {
    char* BinarioString = (char*)malloc((N + 1) * sizeof(char));
    if (BinarioString == NULL) {
        return NULL;
    }

    sprintf(BinarioString, "%0*llu", N, Num); 

    return BinarioString;
}

int ArvoreInserir(Arvore *a, int valor, int n){
	if(a == NULL){
		return 0;
	}
	NoArvore *novo = (NoArvore*)malloc(sizeof(NoArvore));
	
	if(novo == NULL){
		return 0;
	}
	
	novo->valor = valor;
	novo->binario = ConverterBinario(novo->valor);
	novo->BinarioString = ConverterBinString(novo->binario,n);
	novo->E = NULL;
	novo->D = NULL;
	
	NoArvore *atual = a->Raiz;
	NoArvore *pai = NULL;
	
	while(atual != NULL){
		pai = atual;
		if(valor < atual->valor){
			atual = atual->E;
		}
		else{
			atual = atual->D;
		}
	}
	
	if(pai == NULL){
		a->Raiz = novo;
	}
	else if(valor < pai->valor){
		pai->E = novo;
	}
	else{
		pai->D = novo;
	}
	a->Tamanho = a->Tamanho + 1;
	return 1;
}

void LerArquivo(FILE *arquivo, int *k, int *n, char *numeros) {
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d %d %s", k, n, numeros);
}

void ConverterStrArvore(char *numeros, Arvore *a, int n) {
    char *token;
    token = strtok(numeros, ";");
    while (token != NULL) {
    	int valor = atoi(token);
        ArvoreInserir(a, valor, n);
        token = strtok(NULL, ";");
    }
}

void MostreNo(NoArvore *no){
	if(no != NULL){
		MostreNo(no->E);
		printf("%lld\n",no->valor);
		MostreNo(no->D);
	}
}

void MostreArvore(Arvore *a){
	if(a != NULL){
		MostreNo(a->Raiz);
	}
}

void MostreNoBin(NoArvore *no){
	if(no != NULL){
		MostreNoBin(no->E);
		printf("%s\n", no->BinarioString);
		MostreNoBin(no->D);
	}
}

void MostreArvoreBin(Arvore *a){
	if(a != NULL){
		MostreNoBin(a->Raiz);
	}
}


#endif
