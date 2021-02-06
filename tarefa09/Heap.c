#include "Heap.h"

Heap *CriaHeap(int maxsize)
{
  Heap *H = (Heap *)calloc(1,sizeof(Heap));

  H->maxsize = maxsize;
  H->nelems  = 0;
  H->info    = (double *)calloc(H->maxsize,sizeof(double));
  H->cliente  = (Cliente  *)calloc(H->maxsize,sizeof(Cliente));
  return(H);
}

void DestroiHeap(Heap **H)
{
  if (*H != NULL){
    free((*H)->info);
    free((*H)->cliente);
    free(*H);
    *H = NULL;
  }
}

void TrocaInfo(double *x, double *y)
{
  double aux;

  aux = *x;  *x  = *y;  *y = aux;
}

void TrocaCliente(Cliente *x, Cliente *y)
{
  Cliente aux;

  aux = *x;  *x  = *y;  *y = aux;
}

void DesceHeap (Heap *H, int i)
{
 int     maior,esq,dir;
 Boolean continua=true;

 while (continua) {

   esq = FilhoEsquerdo(i);
   dir = FilhoDireito(i);

   if ((esq < H->nelems)&&(H->info[esq] > H->info[i]))
     maior = esq;
   else
     maior = i;

   if ((dir < H->nelems)&&(H->info[dir] > H->info[maior]))
     maior = dir;

   if (maior != i){
     TrocaInfo(&H->info[i],&H->info[maior]);
     TrocaCliente(&H->cliente[i], &H->cliente[maior]);
     i = maior;
   }else
     continua = false;
 }

}

void SobeHeap(Heap *H, int i)
{
  int pai;

  pai = Pai(i);

  while ((pai >= 0) && (H->info[pai] < H->info[i])){
    TrocaInfo(&H->info[i], &H->info[pai]);
    TrocaCliente(&H->cliente[i], &H->cliente[pai]);
    i   = pai;
    pai = Pai(i);
  }

}

Boolean HeapCheio(Heap *H)
{
  if (H->nelems >= H->maxsize)
    return true;
  else
    return false;
}

Boolean HeapVazio(Heap *H)
{
  if (H->nelems <= 0)
    return true;
  else
    return false;
}

void ImprimeCliente(Cliente cliente)
{
  printf("%lf (%s)", cliente.avaliacao, cliente.nome);
}

void ImprimeHeap(Heap *H, int indice, int nivel)
{
  int i;

  if (indice < H->nelems){
    ImprimeHeap(H,FilhoDireito(indice),nivel+1);
    for (i=0; i < nivel; i++)
      printf("   ");

    ImprimeCliente(H->cliente[indice]);

    for (i=0; i <= (int)log2(H->nelems)-nivel; i++)
      printf("---");

    printf("\n");
    ImprimeHeap(H,FilhoEsquerdo(indice),nivel+1);
  }
}

void InsereHeap(Heap *H, double info, char nome[], int x_cliente, int y_cliente, int x_destino, int y_destino)
{
  if (!HeapCheio(H)) {
    H->nelems += 1;
    H->info[H->nelems-1] = info;
    H->cliente[H->nelems-1].avaliacao = info;
    strcpy(H->cliente[H->nelems-1].nome, nome);
    H->cliente[H->nelems-1].x_atual = x_cliente;
    H->cliente[H->nelems-1].y_atual = y_cliente;
    H->cliente[H->nelems-1].x_destino = x_destino;
    H->cliente[H->nelems-1].y_destino = y_destino;
    SobeHeap(H,H->nelems-1);
  }
}

Cliente RemoveHeap(Heap *H)
{
  Cliente cliente;

  if (!HeapVazio(H)) {
    cliente     = H->cliente[0];
    TrocaInfo(&(H->info[0]), &(H->info[H->nelems-1]));
    TrocaCliente(&(H->cliente[0]), &(H->cliente[H->nelems-1]));
    H->nelems--;
    DesceHeap(H,0);
  }

  return(cliente);
}

Cliente RemoveClienteHeap(Heap *H, char nome[20])
{
  Cliente cliente;

  for(int i = 0; i < H->nelems; i++)
  {
    if(strcmp((H->cliente[i]).nome, nome) == 0)
    {
      cliente = H->cliente[i];
      TrocaInfo(&(H->info[i]), &(H->info[H->nelems-1]));
      TrocaCliente(&(H->cliente[i]), &(H->cliente[H->nelems-1]));
      H->nelems--;
      DesceHeap(H,0);
    }
  }
  return cliente;
}
