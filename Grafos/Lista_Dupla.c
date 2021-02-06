#include "Lista_Dupla.h"


NoListaDupla *cria_no_dupla(int ele)
{
  NoListaDupla *no = (NoListaDupla *)calloc(1, sizeof(NoListaDupla));
  no->ant = no;
  no->pro = no;
  no->ele = ele;

  return(no);
}


ListaDupla *cria_lista_dupla_vazia()
{
  ListaDupla *inicio = cria_no_dupla(0);
  inicio->tam = 0;

  return(inicio);
}


bool lista_dupla_vazia(ListaDupla *inicio)
{
  if(inicio->pro == inicio){
    return(true);
  }

  return(false);
}


void imprime_lista_dupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->pro;

  if(lista_dupla_vazia(inicio)){
    printf("<-- (%p) x (%p) -->", inicio->ant, inicio->pro);
  }

  while(p != inicio){
    if (p->ant == inicio){ // primeiro nó da lista
      printf("<--");
    }
    printf(" (%p) %d (%p) ", p->ant, p->ele, p->pro);
    if (p->pro == inicio){
      printf("-->");
    }
    else{
      printf("<-->");
    }
    p = p->pro;
  }
  printf("\n");
}


void imprime_breve_lista_dupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->pro;

  if(lista_dupla_vazia(inicio)){
    printf("<-(%p)x(%p)->", inicio->ant, inicio->pro);
  }

  while(p != inicio){
    if (p->ant == inicio){ // primeiro nó da lista
      //printf("<-");
    }
    //printf(" (%p) %d (%p) ", p->ant, p->ele, p->pro);
    printf("%d ", p->ele);
    if (p->pro == inicio){
      //printf("->");
    }
    else{
      //printf("<->");
    }
    p = p->pro;
  }
}


bool busca_elemento_lista_dupla(ListaDupla *inicio, int ele, NoListaDupla **no)
{
  inicio->ele = ele;

  (*no) = inicio->pro;
  while((*no)->ele != ele){
    (*no) = (*no)->pro;
  }

  if((*no) == inicio){
    return(false);
  }
  return(true);
}


void insere_inicio_lista_dupla(ListaDupla *inicio, int ele)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoListaDupla *p = cria_no_dupla(ele);
  NoListaDupla *q = inicio->pro;

  inicio->pro = p;
  p->ant = inicio;
  p->pro = q;
  q->ant = p;
  inicio->tam += 1;
}


void insere_fim_lista_dupla(ListaDupla *inicio, int ele)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoListaDupla *p = cria_no_dupla(ele);
  NoListaDupla *q = inicio->ant;

  inicio->ant = p;
  p->pro = inicio;
  p->ant = q;
  q->pro = p;
  inicio->tam += 1;
}


bool insere_elemento_antes_chave_lista_dupla(ListaDupla *inicio, int ele, int chave)
{
  NoListaDupla *pno=NULL;

  if(busca_elemento_lista_dupla(inicio, chave, &pno)){
    NoListaDupla *p = cria_no_dupla(ele);
    p->pro = pno;
    p->ant = pno->ant;
    p->ant->pro = p;
    pno->ant = p;
    inicio->tam += 1;
    return(true);
  }
  return(false);
}


bool remove_inicio_lista_dupla(ListaDupla *inicio, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    NoListaDupla *primeiro = inicio->pro, *segundo = primeiro->pro;
    *ele = primeiro->ele;
    inicio->pro = segundo;
    segundo->ant = inicio;
    free(primeiro);
    inicio->tam -= 1;
    return(true);
  }

  return(false);
}


bool remove_elemento_lista_dupla(ListaDupla *inicio, int ele)
{
  NoListaDupla *pno=NULL;

  if(busca_elemento_lista_dupla(inicio, ele, &pno)){
    NoListaDupla *anterior = pno->ant, *posterior = pno->pro;
    anterior->pro = posterior;
    posterior->ant = anterior;
    free(pno);
    inicio->tam -= 1;
    return(true);
  }
  return(false);
}


bool remove_fim_lista_dupla(ListaDupla *inicio, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    NoListaDupla *ultimo = inicio->ant, *penultimo = ultimo->ant;
    *ele = ultimo->ele;
    penultimo->pro = inicio;
    inicio->ant = penultimo;
    free(ultimo);
    inicio->tam -= 1;
    return(true);
  }

  return(false);
}


void esvazia_lista_dupla(ListaDupla *inicio)
{
  int ele;
  while (!lista_dupla_vazia(inicio)){
    remove_inicio_lista_dupla(inicio, &ele);
  }
}


void destroi_lista_dupla(ListaDupla **inicio)
{
  int ele;
  if( *inicio != NULL){
    while(!lista_dupla_vazia(*inicio)){
      remove_inicio_lista_dupla(*inicio, &ele);
    }
    free(*inicio);
    *inicio=NULL;
  }

}


bool retorna_elemento_inicio_lista_dupla(ListaDupla *inicio, int pos, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    if(inicio->tam > pos){
      NoListaDupla *no = inicio->pro;
      for(int i=0; i<pos; i++){
        no = no->pro;
      }
      *ele = no->ele;
      return(true);
    }
  }
  return(false);
}


void copia_lista_dupla(ListaDupla *origem, ListaDupla *destino)
{
  int ele;
  esvazia_lista_dupla(destino);
  for(int i=0; i<origem->tam; i++){
    retorna_elemento_inicio_lista_dupla(origem, i, &ele);
    insere_fim_lista_dupla(destino, ele);
  }
}
