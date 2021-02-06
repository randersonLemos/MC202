#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "Lista_Dupla.h"
#include "Fila.h"

/* Codigo de cores usado para indicar a situacao de um no do grafo em
   relacao a estrutura de dados Q, que pode ser um heap, fila, ou
   pilha, dependendo do algoritmo */

#define BRANCO 0 /* O no nunca foi visitado (nunca entrou em Q) */
#define CINZA  1 /* O no ja foi visitado mas ainda nao foi processado */
#define PRETO  2 /* O no ja foi processado (ja saiu de Q) */

/* Implementaçao estatica: nos e arcos sao fixos para todos os algoritmos */

typedef struct _no_grafo {
  int  nome; /* nome do no */
  int  valor; /* valor associado ao no para fins de computo de peso de aresta */
  int *adj, m; /* lista de adjacentes que armazena os indices deles e
		  o numero m de adjacentes */
  int pred, rotulo; /* informacao extra usada por algoritmos
			      que geram subgrafos deste grafo (e.g.,
			      os percursos geram sempre uma arvore no
			      mapa de predecessores) */

  double custo;

  char local[30];
  double x, y;

} NoGrafo;

typedef struct _grafo {
  NoGrafo *no; /* lista de nos do grafo */
  int       n; /* numero de nos */
} Grafo;

void DestroiGrafo(Grafo **G);
void ImprimeGrafo(Grafo *G);
bool PercursoLargura(Grafo *G, int inicio, double max_distancia);
double MaiorArco(Grafo *G);

#endif
