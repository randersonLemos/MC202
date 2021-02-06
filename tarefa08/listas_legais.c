#include "AVL.h"


int main(){
  bool verbose = false;

  AVL *avl=NULL;

  int n_num, n_ope;
  scanf("%d %d", &n_num, &n_ope);
  if(verbose) printf("%d %d\n", n_num, n_ope);

  for(int i=0; i<n_num; i++){
    int val;
    scanf("%d", &val);
    AVL *aux = Buscar(avl, val);
    if(aux == NULL)
    {
      if(verbose) printf("%d\n", val);
      char mais_alta;
      InsereValor(&avl, val, &mais_alta);
    }
    else
      aux->counter++;
  }

  //ImprimeAVL(avl, 0, Altura(avl));

  for(int i=0; i<n_ope; i++)
  {
    int ope;
    scanf("%d", &ope);
    if(verbose) printf("%d ", ope);
    if(ope == 1)
    {
      int val;
      char mais_alta;
      scanf("%d ", &val);
      if(verbose) printf("%d\n", val);
      AVL *aux = Buscar(avl, val);
      if(aux == NULL)
        InsereValor(&avl, val, &mais_alta);
      else
        aux->counter++;
    }
    else if(ope == 2)
    {
      int val;
      scanf("%d ", &val);
      if(verbose) printf("%d\n", val);
      AVL *aux = Buscar(avl, val);
      if(aux == NULL)
      {
        printf("0\n");
      }
      else
      {
        printf("%d\n", aux->counter);
      }
    }
    else if(ope == 3)
    {
      if(verbose) printf("%d\n",ope);
      printf("%d\n", FaltaParaListaLegal(avl));
    }
  //  else
  //  {
  //    printf("Alguma coisa estranha... Encerrando programa");
  //    return(0);
  //  }
  }
  DestroiAVL(&avl);
  return(0);
}
