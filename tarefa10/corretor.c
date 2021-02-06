#include "Hash.h"

unsigned long long numeric_form(char *str)
{
    unsigned long long hash = 5381;

    int c;
    int length = strlen(str);

    for(int i = 0; i < length; i++)
    {
        c = str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void remove_uma_letra(char *dest, char *orig, int length, int pivot)
{
  for(int i = 0; i < pivot; i++)
  {
    dest[i] = orig[i];
  }

  for(int i = pivot; i < length; i++)
  {
    dest[i] = orig[i+1];
  }
  dest[length - 1] = '\0';
}

void troca_uma_letra(char *dest, char *orig, int length, char letter, int pivot)
{
  for(int i = 0; i < pivot; i++)
  {
    dest[i] = orig[i];
  }

  dest[pivot] = letter;

  for(int i = pivot + 1; i < length; i++)
  {
    dest[i] = orig[i];
  }
  dest[length] = '\0';
}

void adiciona_uma_letra(char *dest, char *orig, int length, char letter, int pivot)
{
  for(int i = 0; i < pivot; i++)
  {
    dest[i] = orig[i];
  }

  dest[pivot] = letter;

  for(int i = pivot; i < length; i++)
  {
    dest[i+1] = orig[i];
  }
  dest[length+1] = '\0';
}

int main(){

int n_word_dict = 0;
int n_word_text = 0;
scanf("%d %d", &n_word_dict, &n_word_text);

Hash *palavrasCorretas = CriaTabelaHash(100);
Hash *palavrasTrocadas = CriaTabelaHash(100000);
Hash *palavrasMenores  = CriaTabelaHash(100000);
Hash *palavrasMaiores  = CriaTabelaHash(100000);

for(int i = 0; i < n_word_dict; i++) // CARREGANDO DICIONÁRIO
{
  char word[MAX_WORD_SIZE];
  scanf("%s", word);

  // PALAVRAS CORRETAS
  unsigned long long chave = numeric_form(word);
  InsereChave(palavrasCorretas, chave);


  // PALAVRAS TROCADAS
  char _word[MAX_WORD_SIZE];
  int length = strlen(word);

  for(int i = 0; i < length; i++)
  {
    for(int letter = 97; letter < 123; ++letter)
    {
      troca_uma_letra(_word, word, length, letter, i);
      chave = numeric_form(_word);
      InsereChave(palavrasTrocadas, chave);
    }
  }


  // PALAVRAS MENORES
  for(int i = 0; i < length; i++)
  {
    remove_uma_letra(_word, word, length, i);
    chave = numeric_form(_word);
    InsereChave(palavrasMenores, chave);
  }


  // PALAVRAS MAIORES
  for(int i = 0; i < length; i++)
  {
    for(int letter = 97; letter < 123; letter++)
    {
      adiciona_uma_letra(_word, word, length, letter, i);
      chave = numeric_form(_word);
      InsereChave(palavrasMaiores, chave);
    }
  }
}


for(int i = 0; i < n_word_text; i++) // CORRIGINDO PALAVRAS
{
  char word[MAX_WORD_SIZE];
  scanf("%s ", word);

  unsigned long long chave = numeric_form(word);

  if(ConsultaChave(palavrasCorretas, chave))
  {
    printf("verde\n");
  }
  else if(ConsultaChave(palavrasTrocadas, chave))
  {
    printf("amarelo\n");
  }
  else if(ConsultaChave(palavrasMenores, chave))
  {
    printf("amarelo\n");
  }
  else if(ConsultaChave(palavrasMaiores, chave))
  {
    printf("amarelo\n");
  }
  else
  {
    printf("vermelho\n");
  }
}

DestroiTabelaHash(&palavrasCorretas);
DestroiTabelaHash(&palavrasTrocadas);
DestroiTabelaHash(&palavrasMenores);
DestroiTabelaHash(&palavrasMaiores);

return(0);
}
