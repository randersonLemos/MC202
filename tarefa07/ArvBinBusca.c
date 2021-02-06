#include "ArvBinBusca.h"

ABBusca *buscar(ABBusca *raiz , int chave){
  if (raiz == NULL || chave == raiz->chave)
    return raiz;
  if (chave < raiz->chave)
    return buscar(raiz->esq, chave);
  else
    return buscar(raiz->dir, chave);
}

ABBusca *inserir(ABBusca *raiz , int chave, char word[9999]) {
  ABBusca *novo;
  if (raiz == NULL) {
    novo = calloc(1, sizeof(ABBusca));
    novo->esq = novo->dir = NULL;
    novo->chave = chave;
    strcpy(novo->word, word);
    return novo;
  }
  if (chave < raiz->chave)
    raiz->esq = inserir(raiz->esq , chave, word);
  else
    raiz->dir = inserir(raiz->dir , chave, word);
  return raiz;
}

ABBusca *minimo(ABBusca *raiz){
  if (raiz == NULL || raiz->esq == NULL)
    return raiz;
  return minimo(raiz->esq);
}

void _sucessor(ABBusca *raiz, int chave, ABBusca **holder, bool *update) {
   if (raiz != NULL) {
    _sucessor(raiz->esq, chave, holder, update);
    if(*update)
    {
      if(chave < raiz->chave)
      {
        *holder = raiz;
        *update = false;
      }
    }
    _sucessor(raiz->dir, chave, holder, update);
  }
}

bool sucessor(ABBusca *raiz, int chave, ABBusca **holder) {
  bool update=true;
  _sucessor(raiz, chave, holder, &update);
  return !update;

}

void remover_sucessor(ABBusca *raiz) {
  ABBusca *min = raiz->dir; /* será o mínimo da subárvore direita */
  ABBusca *pai = raiz;
  /* será o pai de min*/
  while (min->esq != NULL) {
    pai = min;
    min = min->esq;
  }
  if (pai->esq == min)
    pai->esq = min->dir;
  else
    pai->dir = min->dir;
  raiz->chave = min->chave;
  strcpy(raiz->word, min->word);
  free(min);
}

ABBusca *remover_rec(ABBusca *raiz , int chave){
  if (raiz == NULL)
    return NULL;
  if (chave < raiz->chave)
    raiz->esq = remover_rec(raiz->esq , chave);
  else if (chave > raiz->chave)
    raiz->dir = remover_rec(raiz->dir , chave);
  else if (raiz->esq == NULL){
    ABBusca *aux = raiz->dir;
    free(raiz);
    return aux;
  }
  else if (raiz->dir == NULL){
    ABBusca *aux = raiz->esq;
    free(raiz);
    return aux;
  }
  else
    remover_sucessor(raiz);
  return raiz;
}

int altura(ABBusca *ab)
{
  if (ab != NULL)
    return(1 + MAX(altura(ab->esq),altura(ab->dir)));
  else
    return(0);
}

void imprime_arvore(ABBusca *ab, int h, int altura)
{
  int i;
  if (ab != NULL) {
    imprime_arvore(ab->dir, h+1, altura);
    for (i=0; i < h; i++)
      printf("    ");
    printf("%d (%s)",ab->chave, ab->word);
    for (i=0; i < altura-h; i++)
      printf("----");
    printf("\n");
    imprime_arvore(ab->esq, h+1,altura);
  }
}

void limpa_arvore(ABBusca **raiz)
{
  if (*raiz != NULL) {
    limpa_arvore(&((*raiz)->esq));
    limpa_arvore(&((*raiz)->dir));
    free(*raiz);
    *raiz=NULL;
  }
}


void imprime_keys(ABBusca *raiz)
{
  if (raiz != NULL) {
    imprime_keys(raiz->esq);
    printf("%d ", raiz->chave);
    imprime_keys(raiz->dir);
  }
}

void imprime_words(ABBusca *raiz)
{
  if (raiz != NULL) {
    imprime_words(raiz->esq);
    printf("%s", raiz->word);
    imprime_words(raiz->dir);
  }
}
