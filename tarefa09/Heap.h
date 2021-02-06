#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#include <string.h>

#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef enum{false,true} Boolean;

typedef struct _cliente {
  char nome[20];
  int x_atual, y_atual, x_destino, y_destino;
  double avaliacao;
} Cliente;

typedef struct _heap {
  double *info;           /* informação e prioridade ao mesmo tempo */
  Cliente *cliente;
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
} Heap;

typedef struct _heap_heap {
  double *info;           /* informação e prioridade ao mesmo tempo */
  Heap **heap;
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
} HeapHeap;

Heap   *CriaHeap(int maxsize);
void    DestroiHeap(Heap **H);
void    InsereHeap(Heap *H, double info, char nome[], int x_cliente, int y_cliente, int x_destino, int y_destino);
Cliente RemoveHeap(Heap *H);
Cliente RemoveClienteHeap(Heap *H, char nome[20]);
Boolean HeapCheio(Heap *H);
Boolean HeapVazio(Heap *H);
void    ImprimeCliente(Cliente cliente);
void    ImprimeHeap(Heap *H, int indice, int nivel);
void    SobeHeap(Heap *H, int i);
void    DesceHeap(Heap *H, int i);
void    Troca(double *x, double *y);

#endif
