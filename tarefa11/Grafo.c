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
    {
      free(cor);
      DestroiFila(&Q);
      return 1;
    }

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
