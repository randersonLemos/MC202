#include "ArvBinBusca.h"


int main()
{
  bool verbose = false;

  ABBusca *Tokens=NULL;

  int n_cartao, n_autoridade;

  while(scanf("%d %d", &n_cartao, &n_autoridade) != EOF)
  {
    int chave;
    char word[9999];
    for(int i=0; i<n_cartao; i++)
    {
      scanf("%d  \"%[^\"]\"", &chave, word);
      Tokens = inserir(Tokens, chave, word);
    }

    if(verbose) { printf("\n"); imprime_arvore(Tokens, 0, altura(Tokens)); printf("\n"); }

    for(int i=0; i<n_autoridade; i++)
    {
      scanf("%d", &chave);

      if(verbose) { printf("c: %d\n", chave); }

      ABBusca *menor=NULL, *x=NULL, *y=NULL, *z=NULL;
      y = x = menor = minimo(Tokens);

      while(true)
      {
        int z_chave = chave - x->chave - y->chave;

        z = buscar(Tokens, z_chave);
        if(z != NULL)
        {
          strcpy(word, x->word); strcat(word, y->word); strcat(word, z->word);

          if(verbose) { printf("x: %d (%s), y: %d (%s), z: %d (%s) -> s: %d (%s)\n", x->chave, x->word, y->chave
              , y->word, z->chave, z->word, x->chave + y->chave + z->chave, word); }

          if(verbose) { imprime_words(Tokens); printf("\n"); }

          int xaux, yaux, zaux;
          xaux = x->chave;
          yaux = y->chave;
          zaux = z->chave;
          Tokens = remover_rec(Tokens, xaux);
          Tokens = remover_rec(Tokens, yaux);
          Tokens = remover_rec(Tokens, zaux);
          Tokens = inserir(Tokens, chave, word);

          if(verbose) { printf("\n"); imprime_arvore(Tokens, 0, altura(Tokens)); printf("\n"); }
          if(verbose) { imprime_words(Tokens); printf("\n"); }

          break;
        }

        //if(verbose) { printf("x: %d, y: %d\n", x->chave, y->chave); }

        if(!sucessor(Tokens, y->chave, &y))
        {
          if(!sucessor(Tokens, x->chave, &x))
          {
            printf("Sem sucessor");
            return(0);
          }
          y = x;
        }
      }
    }
    imprime_words(Tokens); printf("\n");
    limpa_arvore(&Tokens);
  }
  return(0);
}
