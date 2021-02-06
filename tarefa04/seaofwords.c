#include <stdio.h>
#include <stdlib.h>

void ver_texto(char texto[][101], int m , int n){
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      printf("%c", texto[i][j]);
    }
    printf("\n");
  }
}

void ver_palavras(char palavras[][21], int q){
  for(int i=0; i<q; i++){
    printf("%s\n", palavras[i]);
  }
}

int tamanho_palavra(char palavra[21]){
  int count = 0;
  while(palavra[count] != '\0')
    count++;
  return count;
}

int no_caminho(int caminho[][2], int tam_caminho, int lin, int col)
{
  for(int i=0; i<tam_caminho; i++)
  {
    if(caminho[i][0] == lin && caminho[i][1] == col)
      return 1;
  }
  return 0;
}

void ver_caminho(int caminho[][2], int tam_caminho)
{
  for(int i=0; i<tam_caminho; i++)
  {
    printf("(%d, %d)", caminho[i][0], caminho[i][1]);
  }
  printf("\n");
}

void copia_caminho(int velho[][2], int novo[][2], int tam_caminho){
  for(int i=0; i<tam_caminho; i++)
  {
    novo[i][0] = velho[i][0];
    novo[i][1] = velho[i][1];
  }
}

int dentro_texto(int frt_lin, int frt_col, int lin, int col){
  if((lin >= 0) && (lin < frt_lin) && (col >= 0) && (col < frt_col))
      return 1;
  return 0;
}

int procura_palavra(char texto[][101], int frt_lin_tex, int frt_col_tex, int atl_lin_tex, int atl_col_tex, char palavra[21], int atl_pos_pal, int caminho[][2], int tam_caminho, int modo, int verbose)
{
  int aleluia = 0;
  int prx_lin_tex = 0;
  int prx_col_tex = 0;

  if(verbose) printf("---\n");

  if(dentro_texto(frt_lin_tex, frt_col_tex, atl_lin_tex, atl_col_tex))
  {
    if(palavra[atl_pos_pal] == texto[atl_lin_tex][atl_col_tex])
    {
      modo = 1;
      caminho[tam_caminho][0] = atl_lin_tex;
      caminho[tam_caminho][1] = atl_col_tex;
      tam_caminho++;
      atl_pos_pal++;

      if(verbose) ver_caminho(caminho, tam_caminho);

      if(atl_pos_pal == tamanho_palavra(palavra))
      {
        if(verbose) printf("return 1      : lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        return 1;
      }

      prx_lin_tex = atl_lin_tex;
      prx_col_tex = atl_col_tex + 1;
      if(no_caminho(caminho, tam_caminho, prx_lin_tex, prx_col_tex) == 0 && aleluia == 0)
      {
        if(verbose) printf("call procura >: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        aleluia += procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }

      prx_lin_tex = atl_lin_tex;
      prx_col_tex = atl_col_tex - 1;
      if(no_caminho(caminho, tam_caminho, prx_lin_tex, prx_col_tex) == 0 && aleluia == 0)
      {
        if(verbose) printf("call procura <: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        aleluia += procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }

      prx_lin_tex = atl_lin_tex + 1;
      prx_col_tex = atl_col_tex;
      if(no_caminho(caminho, tam_caminho, prx_lin_tex, prx_col_tex) == 0 && aleluia == 0)
      {
        if(verbose) printf("call procura v: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        aleluia += procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }

      prx_lin_tex = atl_lin_tex - 1;
      prx_col_tex = atl_col_tex;
      if(no_caminho(caminho, tam_caminho, prx_lin_tex, prx_col_tex) == 0 && aleluia == 0)
      {
        if(verbose) printf("call procura ^: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        aleluia += procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }

      if(aleluia == 0)
      {
        modo = 0;
        atl_pos_pal = 0;
        tam_caminho = 0;
        prx_lin_tex = caminho[0][0];
        prx_col_tex = caminho[0][1] + 1;
        if(prx_col_tex == frt_col_tex)
        {
          prx_col_tex = 0;
          prx_lin_tex++;
        }
        if(verbose) printf("return procura 1: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        return procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }
    }
    else
    {
      if(modo)
      {
        if(verbose) printf("return 0      : lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        return 0;
      }
      else
      {
        atl_pos_pal = 0;
        tam_caminho = 0;
        prx_lin_tex = atl_lin_tex;
        prx_col_tex = atl_col_tex + 1;
        if(prx_col_tex == frt_col_tex)
        {
          prx_col_tex = 0;
          prx_lin_tex++;
        }
        if(verbose) printf("return procura 2: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
        return procura_palavra(texto, frt_lin_tex, frt_col_tex, prx_lin_tex, prx_col_tex, palavra, atl_pos_pal, caminho, tam_caminho, modo, verbose);
      }
    }
  }
  if(verbose) printf("return aleluia: lin:%d, col:%d (lin:%d, col:%d)\n", atl_lin_tex, atl_col_tex, prx_lin_tex, prx_col_tex);
  return aleluia;
}

int main(){
  int m, n, q; // # linhas, # colunas e # palavras
  scanf("%d %d %d", &m, &n, &q);

  char texto[100][101];
  char palavras[10][21];

  for(int i=0; i<m; i++){
      scanf("%s", texto[i]);
  }

  for(int i=0; i<q; i++){
    scanf("%s", palavras[i]);
  }

  int caminho[1000][2];
  int tam_caminho = 0;

  int verbose = 0;
  for(int i=0; i<q; i++)
  {
    if(verbose) printf("------\npalavra: %s\n", palavras[i]);
    if(procura_palavra(texto, m, n, 0, 0, palavras[i], 0, caminho, tam_caminho, 0, verbose))
      printf("sim\n");
    else
      printf("nao\n");
  }
  return(0);
}
