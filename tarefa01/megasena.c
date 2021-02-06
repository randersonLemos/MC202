#include <stdio.h>
#include <stdlib.h>

int *CreateArrayInt(int nlin){
  int *arr = (int *)calloc(nlin, sizeof(int));
  return(arr);
}

void DestroyArrayInt(int **arr){
  if((*arr) != NULL){
    free(*arr);
    *arr = NULL;
  }
}

void PrintArrayInt(int *arr, int nlin){
  for(int i=0; i<nlin; i++)
      printf("%d ", arr[i]);
  printf("\n");
}

float *CreateArrayFloat(int nlin){
  float *arr = (float *)calloc(nlin, sizeof(float));
  return(arr);
}

void DestroyArrayFloat(float **arr){
  if((*arr) != NULL){
    free(*arr);
    *arr = NULL;
  }
}

void PrintArrayFloat(float *arr, int nlin){
  for(int i=0; i<nlin; i++)
      printf("%f ", arr[i]);
  printf("\n");
}

long double *CreateArrayLongDouble(int nlin){
  long double *arr = (long double *)calloc(nlin, sizeof(long double));
  return(arr);
}

void DestroyArrayLongDouble(long double **arr){
  if((*arr) != NULL){
    free(*arr);
    *arr = NULL;
  }
}

void PrintArrayLongDouble(long double *arr, int nlin){
  for(int i=0; i<nlin; i++)
      printf("%Lf ", arr[i]);
  printf("\n");
}


int **Create2dArrayInt(int nlin, int ncol){
  int **arr = (int **)calloc(nlin, sizeof(int *));
  for(int l=0; l<nlin; l++){
    arr[l] = (int *)calloc(ncol, sizeof(int));
  }
  return(arr);
}

void Destroy2dArrayInt(int ***arr, int nlin){
  if ((*arr) != NULL){
    for(int l=0; l<nlin; l++){
      free((*arr)[l]);
    }
    free(*arr);
    *arr = NULL;
  }
}

void Print2dArrayInt(int **arr, int nlin, int ncol){
  for(int i=0; i<nlin; i++){
    for(int j=0; j<ncol; j++){
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

int ***Create3dArrayInt(int nlin, int ncol, int nwid){
  int ***arr = (int ***)calloc(nlin, sizeof(int **));
  for(int l=0; l<nlin; l++){
    arr[l] = (int **)calloc(ncol, sizeof(int *));
    for(int c=0; c<ncol; c++){
      arr[l][c] = (int *)calloc(nwid, sizeof(int));
    }
  }
  return(arr);
}

void Destroy3dArrayInt(int ****arr, int nlin, int ncol){
  if((*arr)!=NULL){
    for(int l=0; l<nlin; l++){
      for(int c=0; c<ncol; c++){
        free((*arr)[l][c]);
      }
      free((*arr)[l]);
    }
    free(*arr);
  }
}

void Print3dArrayInt(int ***arr, int nlin, int ncol, int nwid){
  for(int i=0; i<nlin; i++){
    for(int j=0; j<ncol; j++){
      for(int k=0; k<nwid; k++){
        printf("%d ", arr[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

int matches(int **bet, int *values_drawn){
  int count = 0;
  int lin, col = 0;
  for(int i=0; i<6; i++){
    col = (values_drawn[i]-1) % 10;
    lin = ((values_drawn[i]-1) - col) / 10;
    count += bet[lin][col];
  //  printf("(%d, %d, %d) ", lin, col, bet[lin][col]);
  //printf("\n");
  }
  return(count);
}

int main() {
  int num_players;
  long double prize;
  scanf("%d", &num_players);
  scanf("%Lf", &prize);

  int ***bets;
  bets = Create3dArrayInt(num_players, 6, 10);
  for(int i=0; i<num_players; i++){
    for(int j=0; j<6; j++){
      for(int k=0; k<10; k++){
          scanf("%d", &bets[i][j][k]);
      }
    }
  }

  int *values_drawn;
  values_drawn = CreateArrayInt(6);
  for(int i=0; i<6; i++){
    scanf("%d", &values_drawn[i]);
  }

  int *matches_players;
  int *prize_categories;
  matches_players = CreateArrayInt(num_players);
  prize_categories = CreateArrayInt(7);
  for(int i=0; i<num_players; i++){
    matches_players[i] = matches(bets[i], values_drawn);
    prize_categories[matches_players[i]] += 1;
    //Print2dArrayInt(bets[i], 6, 10);
    }
  //PrintArrayInt(num_matches_players, m);

  long double *prize_players;
  prize_players = CreateArrayLongDouble(num_players);
  for(int i=0; i<num_players; i++){
    if(matches_players[i] == 6){
      prize_players[i] = (0.62*prize) / prize_categories[matches_players[i]];
    }

    if(matches_players[i] == 5){
      prize_players[i] = (0.19*prize) / prize_categories[matches_players[i]];
    }

    if(matches_players[i] == 4){
      prize_players[i] = (0.19*prize) / prize_categories[matches_players[i]];
    }
  }

  //PrintArrayInt(matches_players, num_players);
  //PrintArrayInt(prize_categories, num_players);
  //PrintArrayFloat(prize_players, num_players);

  for(int i=0; i<num_players; i++){
    printf("%.2Lf\n", prize_players[i]);
  }

  Destroy3dArrayInt(&bets, num_players, 6);
  DestroyArrayInt(&values_drawn);
  DestroyArrayInt(&matches_players);
  DestroyArrayInt(&prize_categories);
  DestroyArrayLongDouble(&prize_players);
  return(0);
}
