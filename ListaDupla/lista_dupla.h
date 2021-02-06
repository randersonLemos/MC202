#ifndef LISTA_DUPLA_H_
#define LISTA_DUPLA_H_

#include <stdio.h>
#include <stdlib.h>

#ifndef bool
typedef enum _bool {
  false, true
} bool;
#endif

/* Lista dupla circular e com no cabeca ficticio */

typedef struct no_lista_dupla {
    struct no_lista_dupla *ant;
    struct no_lista_dupla *pro;
    int ele;
    int tam;
} ListaDupla, NoListaDupla;

NoListaDupla *cria_no_dupla(int ele);

ListaDupla *cria_lista_dupla_vazia();

bool lista_dupla_vazia(ListaDupla *inicio);

void imprime_lista_dupla(ListaDupla *inicio);

void imprime_breve_lista_dupla(ListaDupla *inicio);

bool busca_elemento_lista_dupla(ListaDupla *inicio, int ele, NoListaDupla **no);

void insere_inicio_lista_dupla(ListaDupla *inicio, int ele);

void insere_fim_lista_dupla(ListaDupla *inicio, int ele);

bool insere_elemento_antes_chave_lista_dupla(ListaDupla *inicio, int ele, int chave);

bool remove_inicio_lista_dupla(ListaDupla *inicio, int *ele);

bool remove_elemento_lista_dupla(ListaDupla *inicio, int ele);

bool remove_fim_lista_dupla(ListaDupla *inicio, int *ele);

void esvazia_lista_dupla(ListaDupla *inicio);

void destroi_lista_dupla(ListaDupla **inicio);

#endif
