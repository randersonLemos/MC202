#ifndef _ABBusca_H_
#define _ABBusca_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef bool
typedef enum { false, true } bool;
#endif

#define MAX(a,b) ((a > b)?a:b)

typedef struct NoABBusca {
  int chave;
  char word[9999];
  struct NoABBusca *esq, *dir, *pai;
} ABBusca;

ABBusca *criar_arvore();

void destruir_arvore(ABBusca *raiz);

ABBusca *inserir(ABBusca *raiz , int chave, char word[9999]);

ABBusca *remover(ABBusca *raiz , int chave);

ABBusca *remover_rec(ABBusca *raiz , int chave);

ABBusca *buscar(ABBusca *raiz , int chave);

ABBusca *minimo(ABBusca *raiz);

ABBusca *maximo(ABBusca *raiz);

//ABBusca *sucessor(ABBusca *x);

bool sucessor(ABBusca *raiz, int chave, ABBusca **holder);

ABBusca *antecessor(ABBusca *x);

int altura(ABBusca *ab);

void imprime_arvore(ABBusca *ab, int h, int altura);

void limpa_arvore(ABBusca **raiz);

void imprime_keys(ABBusca *raiz);

void imprime_words(ABBusca *raiz);

#endif









