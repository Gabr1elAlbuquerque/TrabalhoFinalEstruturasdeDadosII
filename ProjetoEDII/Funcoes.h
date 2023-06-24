#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LerArquivo(FILE *arquivo, int *k, int *n, char *Numeros) {
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d %d %s", k, n, Numeros);
}

typedef struct NoArvore{
	int valor;
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

char* ConverterBinString(int Num, int N) {
    char* BinarioString = (char*)malloc((N + 1) * sizeof(char));
    if (BinarioString == NULL) {
        return NULL;
    }

    BinarioString[N] = '\0';
    for (int i = N - 1; i >= 0; i--) {
        if (Num >= (1 << i)) {
            BinarioString[N - 1 - i] = '1';
            Num -= (1 << i);
        } else {
            BinarioString[N - 1 - i] = '0';
        }
    }

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
	novo->BinarioString = ConverterBinString(novo->valor,n);
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

void ConverterStrArvore(char *numeros, Arvore *a, int n) {
    char *token;
    token = strtok(numeros, ";");
    while (token != NULL) {
    	int valor = atoi(token);
        ArvoreInserir(a, valor, n);
        token = strtok(NULL, ";");
    }
    free(token);
}

char* ConcatenaStringNo(NoArvore* no) {
    if (no == NULL) {
        return NULL;
    }

    char* resultadoEsquerda = ConcatenaStringNo(no->E);
    char* resultadoDireita = ConcatenaStringNo(no->D);

    int tamanhoTotal = strlen(no->BinarioString) + 1;
    if (resultadoEsquerda != NULL) {
        tamanhoTotal += strlen(resultadoEsquerda);
    }
    if (resultadoDireita != NULL) {
        tamanhoTotal += strlen(resultadoDireita);
    }

    char* resultado = (char*)malloc(tamanhoTotal * sizeof(char));
    if (resultado == NULL) {
        printf("Erro na alocação de memória.\n");
        return NULL;
    }

    strcpy(resultado, no->BinarioString);

    if (resultadoEsquerda != NULL) {
        strcat(resultado, resultadoEsquerda);
        free(resultadoEsquerda);
    }

    if (resultadoDireita != NULL) {
        strcat(resultado, resultadoDireita);
        free(resultadoDireita);
    }

    return resultado;
}

char* ConcatenaStringArvore(Arvore* a) {
    if (a != NULL) {
        return ConcatenaStringNo(a->Raiz);
    }
}

void LiberaNo(NoArvore *no){
	if(no != NULL){
		LiberaNo(no->E);
		LiberaNo(no->D);
		free(no->BinarioString);
		free(no);
	}
}

void LiberaArvore(Arvore *a){
	if(a != NULL){
		LiberaNo(a->Raiz);
	}
}

void MostreNo(NoArvore *no){
	if(no != NULL){
		MostreNo(no->E);
		printf("%d\n",no->valor);
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
