#include "Grafo.h"

typedef struct _entrada {
  double x,y;
  char local[30];

} Entrada;

int main() {
  Entrada entrada[9999];
  int tam = 0;

  scanf("%lf %lf", &(entrada[tam].x), &(entrada[tam].y)); strcpy(entrada[tam].local, "origem");
  tam++;

  while(scanf("%lf %lf %s", &(entrada[tam].x), &(entrada[tam].y), entrada[tam].local) != EOF)
    tam++;

  Grafo *G  = (Grafo *)calloc(1, sizeof(Grafo));
  G->no     = (NoGrafo *)calloc(tam, sizeof(NoGrafo));
  G->n      = tam;

  for (int i=0; i<G->n; i++)
  {
    G->no[i].nome = i;
    G->no[i].x = entrada[i].x;
    G->no[i].y = entrada[i].y;

    strcpy(G->no[i].local, entrada[i].local);

    G->no[i].m = tam-1;
    G->no[i].adj = (int *)calloc(G->no[i].m, sizeof(int));

    int z = 0;
    for(int j=0; j<tam; j++)
    {
      if(j!=i)
      {
        G->no[i].adj[z] = j;
        z++;
      }
    }
  }

  double M_arc = ceil(MaiorArco(G));

  double min=0, max=M_arc, piv=M_arc;
  while(true)
  {
    if(PercursoLargura(G, 0, ceil(piv)))
    {
      max = piv;
      piv = (max + min)/2;
    }
    else
    {
      min = piv;
      piv = (max + min)/2;
    }

    if(max - min < 1)
      break;
  }

  printf("%1.0lf\n", ceil(max));

  DestroiGrafo(&G);

  return 0;
}
