#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Leitura do Arquivo txt
void LerArquivo(FILE *arquivo, int *k, int *n, char *Numeros) {
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d %d %s", k, n, Numeros);
}

//defini��es da arvore
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

//fun��o que converte os b�meros em bin�rio adicionando os zeros a esquerda se necess�rio
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

//Fun��o que insere um novo n� na �rvore
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

//Fun��o que remore o ; dos n�meros da terceira linha do arquivo 
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

//fun��o que concatena todos os n�s bin�rios para an�lise
char* ConcatenaStringNo(NoArvore* no) {
    if (no == NULL) {
        return NULL;
    }

    char* resultadoEsquerda = ConcatenaStringNo(no->E);
    char* resultadoDireita = ConcatenaStringNo(no->D);

    int tamanhoTotal = 1; // Tamanho inicial 1 para o caractere nulo '\0'
    if (resultadoEsquerda != NULL) {
        tamanhoTotal += strlen(resultadoEsquerda);
    }
    tamanhoTotal += strlen(no->BinarioString);
    if (resultadoDireita != NULL) {
        tamanhoTotal += strlen(resultadoDireita);
    }

    char* resultado = (char*)malloc(tamanhoTotal * sizeof(char));
    if (resultado == NULL) {
        printf("Erro na aloca��o de mem�ria.\n");
        return NULL;
    }

    resultado[0] = '\0'; // Inicializa com o caractere nulo

    if (resultadoEsquerda != NULL) {
        strcat(resultado, resultadoEsquerda);
        free(resultadoEsquerda);
    }

    strcat(resultado, no->BinarioString);

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
//fun��o que libera a mem�ria alocada para a arvore ap�s a execu��o do programa
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

//fun��o para mostrar o a arvore em decimal
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

//fun��o que mostra a �rvore em bin�rio
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
