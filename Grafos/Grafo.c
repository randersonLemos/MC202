#include "Grafo.h"

void DestroiGrafo(Grafo **G)
{
  Grafo *aux=*G;
  int    u;

  for (u=0; u < aux->n; u++) {
    if (aux->no[u].m > 0)
      free(aux->no[u].adj);
  }
  free(aux->no);
  free(aux);
  *G = NULL;
}

void ImprimeGrafo(Grafo *G)
{
  int u, v, i;

  for (u=0; u < G->n; u++) {
    printf("%3d: x=%+10.5lf, y=%+10.5lf, local=%8s, adjacentes={",G->no[u].nome,G->no[u].x,G->no[u].y,G->no[u].local);
    for (i=0; i < G->no[u].m; i++) {
      v=G->no[u].adj[i];
      printf("%3d,",G->no[v].nome);
    }
    printf("}\n");
  }
}


//void IniciaJornada(Grafo *G)
//{
//  ListaDupla *visitar = cria_lista_dupla_vazia(G->n);
//  ListaDupla *visitados = cria_lista_dupla_vazia(G->n);
//
//  char *cor=(char *)calloc(G->n,sizeof(char));
//
//  /* Inicializacao */
//  for (int u=0; u < G->n; u++)
//  {
//    cor[u]           = BRANCO;
//    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
//    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
//    G->no[u].custo   = -1; /* comprimento do caminho para a raiz */
//  }
//
//  for (int u=0; u < G->n; u++)
//    insere_fim_lista_dupla(visitar, u);
//
//  // printf("visitados"); imprime_breve_lista_dupla(visitados); printf("\n");
//  // printf("visitar"); imprime_breve_lista_dupla(visitar); printf("\n");
//
//  int u = 0, v = 0;
//  insere_fim_lista_dupla(visitados, u); cor[u]=PRETO; G->no[u].custo = G->no[v].d - G->no[u].d;
//  remove_elemento_lista_dupla(visitar, u);
//
//  double Custo = 0;
//  while(true)
//  {
//    if(strcmp(G->no[u].local, "Lugia") == 0)
//      break;
//
//    double distancia = DBL_MAX;
//    for(int i=0; i < G->no[u].m; i++)
//    {
//      int aux = G->no[u].adj[i];
//      if(fabs(G->no[aux].d - G->no[u].d) < distancia && cor[aux] == BRANCO)
//      {
//        distancia = fabs(G->no[aux].d - G->no[u].d);
//        v = aux;
//      }
//    }
//    insere_fim_lista_dupla(visitados, v); cor[v]=PRETO; G->no[v].custo = G->no[v].d - G->no[u].d;
//    remove_elemento_lista_dupla(visitar, v);
//    u = v;
//    Custo += distancia;
//  }
//  printf("visitados "); imprime_breve_lista_dupla(visitados); printf("\n");
//  printf("visitar   "); imprime_breve_lista_dupla(visitar); printf("\n");
//
//  printf("\n");
//  for(int i=0; i<G->n; i++)
//    printf("no %3d e custo %+10.5lf\n", i, G->no[i].custo);
//
//  printf("Custo %lf\n", Custo);
//}

double MaiorArco(Grafo *G)
{
  double Distancia = -1;
  for(int u=0; u<G->n; u++)
  {
    for(int v=0; v<G->n; v++)
    {
      double distancia = sqrt(pow(G->no[u].x - G->no[v].x, 2) + pow(G->no[u].y - G->no[v].y, 2));
      if(distancia > Distancia)
        Distancia = distancia;
    }
  }
  return Distancia;
}

bool PercursoLargura(Grafo *G, int inicio, double max_distancia)
{
  Fila *Q=CriaFila(G->n);
  int   u, v, i;
  char *cor=(char *)calloc(G->n,sizeof(char));

  /* Inicializacao */

  for (u=0; u < G->n; u++) {
    cor[u]           = BRANCO;
    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].custo   = -1; /* comprimento do caminho para a raiz */
  }

  InsereFila(Q,inicio); cor[inicio]=CINZA; G->no[inicio].custo = 0;

  /* Propagacao */
  u = v = inicio;
  while (!FilaVazia(Q)){
    u = RemoveFila(Q); cor[u]=PRETO;

    //printf("   %3d: x=%+10.5lf, y=%+10.5lf, local=%8s (custo=%lf)\n",G->no[u].nome,G->no[u].x,G->no[u].y,G->no[u].local, G->no[u].custo);
    //printf("\n");

    if(strcmp(G->no[u].local, "Lugia") == 0)
      return 1;

    for (i=0; i < G->no[u].m; i++)
    {
      v = G->no[u].adj[i];

      double distancia = sqrt(pow(G->no[u].x - G->no[v].x, 2) + pow(G->no[u].y - G->no[v].y, 2));

      if (cor[v]==BRANCO)
      {
        if (distancia < max_distancia)
        {
          //printf("u: %3d: x=%+10.5lf, y=%+10.5lf, local=%8s\n",G->no[u].nome,G->no[u].x,G->no[u].y,G->no[u].local);
          //printf("v: %3d: x=%+10.5lf, y=%+10.5lf, local=%8s\n",G->no[v].nome,G->no[v].x,G->no[v].y,G->no[v].local);


          G->no[v].pred   = u;
          G->no[v].custo  = distancia;
          G->no[v].rotulo = G->no[u].rotulo;
          InsereFila(Q,v); cor[v]=CINZA;
        }
      }
    }

      //printf("\n");
  }

  free(cor);
  DestroiFila(&Q);

  return 0;
}
//
//void   PercursoProfundidade(Grafo *G, int inicio)
//{
//  Pilha *Q=CriaPilha(G->n);
//  int   u, v, i;
//  char *cor=(char *)calloc(G->n,sizeof(char));
//
//  /* Inicializacao */
//
//  for (u=0; u < G->n; u++) {
//    cor[u]           = BRANCO;
//    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
//    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
//    G->no[u].custo   = INT_MAX; /* comprimento do caminho para a raiz */
//  }
//  Empilha(Q,inicio); cor[inicio]=CINZA; G->no[inicio].custo = 0;
//
//  /* Propagacao */
//
//  while (!PilhaVazia(Q)){
//    u      = Desempilha(Q); cor[u]=PRETO;
//    printf("%c (%c,%d,%c),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[G->no[u].rotulo].nome);
//    for (i=0; i < G->no[u].m; i++) {
//      v = G->no[u].adj[i];
//      if (cor[v]!=PRETO){
//	G->no[v].pred   = u;
//	G->no[v].custo  = G->no[u].custo + 1;
//	G->no[v].rotulo = G->no[u].rotulo;
//	if (cor[v]==BRANCO){
//	  Empilha(Q,v); cor[v]=CINZA;
//	}
//      }
//    }
//  }
//  printf("\n");
//  free(cor);
//  DestroiPilha(&Q);
//}
//
//void  ArvoreCaminhosMinimos(Grafo *G, int inicio)
//{
//  int   u, v, i, tmp;
//  char *cor=(char *)calloc(G->n,sizeof(char));
//  int  *custo = (int *)calloc(G->n, sizeof(int));
//  Heap *Q=CriaHeap(G->n,custo);
//
//  /* Inicializacao */
//
//  for (u=0; u < G->n; u++) {
//    cor[u]           = BRANCO;
//    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
//    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
//    custo[u] = G->no[u].custo = INT_MAX; /* custo do caminho para a raiz */
//  }
//  custo[inicio] = G->no[inicio].custo = 0; /* custo do caminho para a raiz */
//  InsereHeap(Q,inicio); cor[inicio]=CINZA;
//
//  /* Relaxacao e propagacao */
//
//  while (!HeapVazio(Q)){
//    u      = RemoveHeap(Q); cor[u]=PRETO;
//    printf("%c (%c,%d,%c),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[G->no[u].rotulo].nome);
//    for (i=0; i < G->no[u].m; i++) {
//      v = G->no[u].adj[i];
//      if ((cor[v]!=PRETO)&&(G->no[u].custo < G->no[v].custo)){
//	tmp = G->no[u].custo + abs(G->no[v].valor-G->no[u].valor);
//	if (tmp < G->no[v].custo){
//	  custo[v] = G->no[v].custo = tmp;
//	  G->no[v].pred   = u;
//	  G->no[v].rotulo = G->no[u].rotulo;
//	  if (cor[v]==BRANCO){
//	    InsereHeap(Q,v); cor[v]=CINZA;
//	  } else {
//	    SobeHeap(Q,v);
//	  }
//	}
//      }
//    }
//  }
//  printf("\n");
//  free(cor);
//  free(custo);
//  DestroiHeap(&Q);
//}
//
//Grafo *FlorestaPesoMinimo(Grafo *G)
//{
//  Grafo *F;
//  int    u, v, i, tmp, r=1;
//  char  *cor=(char *)calloc(G->n,sizeof(char));
//  int   *custo = (int *)calloc(G->n, sizeof(int));
//  Heap  *Q=CriaHeap(G->n,custo);
//  int   *indice;
//
//  /* Inicializacao */
//
//  for (u=0; u < G->n; u++) {
//    custo[u] = G->no[u].custo = INT_MAX; /* custo do caminho para a raiz */
//    InsereHeap(Q,u); cor[u]=CINZA;
//  }
//
//  /* Relaxacao e propagacao */
//
//  while (!HeapVazio(Q)){
//    u  = RemoveHeap(Q); cor[u]=PRETO;
//    if (G->no[u].custo == INT_MAX){ /* no inicial no componente */
//      G->no[u].pred    = u;      /* define uma raiz em u */
//      G->no[u].rotulo  = r; r++; /* inicia rotulacao do componente conexo */
//      custo[u] = G->no[u].custo = 0;
//    }
//    for (i=0; i < G->no[u].m; i++) {
//      v = G->no[u].adj[i];
//      if (cor[v]!=PRETO){
//	tmp = abs(G->no[v].valor-G->no[u].valor);
//	if (tmp < G->no[v].custo){
//	  custo[v] = G->no[v].custo  = tmp;
//	  G->no[v].pred   = u;
//	  G->no[v].rotulo = G->no[u].rotulo;
//	  SobeHeap(Q,v);
//	}
//      }
//    }
//  }
//
//  free(cor);
//  free(custo);
//  DestroiHeap(&Q);
//
//  /* A Floresta eh um grafo aciclico e nao direcionado. Entao copie as
//     arvores de peso minimo no grafo correspondente. */
//
//  F      = (Grafo *)calloc(1,sizeof(Grafo));
//  F->no  = (NoGrafo *)calloc(G->n,sizeof(NoGrafo));
//  F->n   = G->n;
//  indice = (int *)calloc(G->n,sizeof(int));
//
//  for (u=0; u < G->n; u++) {
//    F->no[u].nome   = G->no[u].nome;
//    F->no[u].valor  = G->no[u].valor;
//    F->no[u].pred   = G->no[u].pred;
//    F->no[u].rotulo = G->no[u].rotulo;
//    F->no[u].custo  = G->no[u].custo;
//    v               = G->no[u].pred;
//    if (v != u){ /* conte os adjacentes */
//      F->no[u].m++; F->no[v].m++;
//    }
//  }
//
//  /* aloque memoria para os adjacentes */
//
//  for (u=0; u < G->n; u++) {
//    F->no[u].adj = (int *)calloc(F->no[u].m,sizeof(int));
//  }
//
//  /* insira os adjacentes */
//
//  for (u=0; u < G->n; u++) {
//    v = G->no[u].pred;
//    if (v != u){
//      F->no[u].adj[indice[u]] = v; indice[u]++;
//      F->no[v].adj[indice[v]] = u; indice[v]++;
//    }
//  }
//
//  free(indice);
//
//  return(F);
//}
