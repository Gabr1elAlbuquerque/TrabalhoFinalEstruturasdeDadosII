#ifndef __funcoes__
#define __funcoes__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Leitura do Arquivo txt
void LerArquivo(FILE *arquivo, int *k, int *n, char *Numeros) {
    if (arquivo != NULL) {
        fscanf(arquivo, "%d %d %s", k, n, Numeros);
    }
}

//definições da arvore
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

//função que converte os búmeros em binário adicionando os zeros a esquerda se necessário
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

//Função que insere um novo nó na árvore
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

//Função que remore o ; dos números da terceira linha do arquivo 
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

//função que concatena todos os nós binários para análise
char* ConcatenaStringNo(NoArvore* no) {
    if (no == NULL) {
        return NULL;
    }

    char* resultadoEsquerda = ConcatenaStringNo(no->E);
    char* resultadoDireita = ConcatenaStringNo(no->D);

    int tamanhoTotal = 1;
    if (resultadoEsquerda != NULL) {
        tamanhoTotal += strlen(resultadoEsquerda);
    }
    tamanhoTotal += strlen(no->BinarioString);
    if (resultadoDireita != NULL) {
        tamanhoTotal += strlen(resultadoDireita);
    }

    char* resultado = (char*)malloc(tamanhoTotal * sizeof(char));
    if (resultado == NULL) {
        printf("Erro na alocação de memória.\n");
        return NULL;
    }

    resultado[0] = '\0';

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

void ContarCombinacoesRepetidas(char* concatenado, int k) {
    int numCombinacoes = 1 << k;  // Número total de combinações
    int* contadores = (int*)calloc(numCombinacoes, sizeof(int));
    if (contadores == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    int stringLength = strlen(concatenado);
    for (int i = 0; i <= stringLength - k; i++) {
        int combinacao = 0;
        for (int j = 0; j < k; j++) {
            combinacao = (combinacao << 1) | (concatenado[i + j] - '0');
        }
        contadores[combinacao]++;
    }

    // Criar um array de índices para ordenação
    int* indices = (int*)malloc(numCombinacoes * sizeof(int));
    if (indices == NULL) {
        printf("Erro na alocação de memória.\n");
        free(contadores);
        return;
    }
    for (int i = 0; i < numCombinacoes; i++) {
        indices[i] = i;
    }


    for (int i = 0; i < numCombinacoes - 1; i++) {
        for (int j = i + 1; j < numCombinacoes; j++) {
            if (contadores[indices[j]] > contadores[indices[i]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    for (int i = 0; i < numCombinacoes; i++) {
        for (int j = k - 1; j >= 0; j--) {
            printf("%d", (indices[i] >> j) & 1);
        }
        printf(" - %d\n", contadores[indices[i]]);
    }

    free(contadores);
    free(indices);
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

//função para mostrar o a arvore em decimal
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

//função que mostra a árvore em binário
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
