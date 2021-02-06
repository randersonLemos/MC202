#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _data{
  char *termo;
  double *historico;
  double max;
  double min;
  double mea;
  double std;
  int cat;
} Data;

double maximum(double arr[], int size){
  double max = arr[0];
  for(int i=0; i<size; i++){
    if(arr[i] > max)
      max = arr[i];
  }
  return max;
}

double minimum(double arr[], int size){
  double min = arr[0];
  for(int i=0; i<size; i++){
    if(arr[i] < min)
      min = arr[i];
  }
  return min;
}

double mean(double arr[], int size){
  double mea = 0;
  for(int i=0; i<size; i++)
    mea += arr[i];
  mea = mea/size;
  return mea;
}

double standard_deviation(double arr[], int size){
  double mea = mean(arr, size);
  double std = 0;
  for(int i=0; i<size; i++){
    std += pow(arr[i]-mea,2);
  }
  std = sqrt(std/size);
  return std;
}


char *criaArrayChar(int size){
  char *arr = (char *)calloc(size, sizeof(char));
  return arr;
}

void destroiArrayChar(char **arr){
  if(*arr != NULL){
    free(*arr);
    *arr = NULL;
  }
}

double *criaArrayDouble(int size){
  double *arr = (double *)calloc(size, sizeof(double));
  return arr;
}

void destroiArrayDouble(double **arr){
  if(*arr != NULL){
    free(*arr);
    *arr = NULL;
  }
}

Data *criaArrayData(int size){
  Data *arr = (Data *)calloc(size, sizeof(Data));
  return arr;
}

void destroiArrayData(Data **arr, int size){
  if(*arr != NULL){
    for(int i=0; i<size; i++){
     destroiArrayChar(&(*arr)[i].termo);
     destroiArrayDouble(&(*arr)[i].historico);
    }
    free(*arr);
    *arr = NULL;
  }
}

int main(){
  int N; // número de termos
  int M; // quantidade de dias
  scanf("%d %d", &N, &M);

  Data *data = criaArrayData(N);

  long int num_bot = 0;
  long int num_surpreendente = 0;
  long int num_normal = 0;
  long int num_local = 0;
  long int num_irrelevante = 0;

  for(int i=0; i<N; i++){
    char *termo = criaArrayChar(26);
    double *historico = criaArrayDouble(M);

    scanf("%s", termo);
    for(int j=0; j<M; j++){ scanf("%lf", &historico[j]); }

    data[i].termo = termo;
    data[i].historico = historico;
    data[i].max = maximum(historico, M);
    data[i].min = minimum(historico, M);
    data[i].mea = mean(historico, M);
    data[i].std = standard_deviation(historico, M);

    if(data[i].mea >= 60 && data[i].std > 15){
      data[i].cat = 0;
      num_bot += 1;
    }
    if(data[i].mea >= 60 && data[i].std <= 15){
      data[i].cat = 1;
      num_surpreendente += 1;
    }
    if(data[i].mea < 60 && data[i].max >= 80 && data[i].min > 20){
      data[i].cat = 2;
      num_normal += 1;
    }
    if(data[i].mea < 60 && data[i].max >= 80 && data[i].min <= 20){
      data[i].cat = 3;
      num_local += 1;
    }
    if(data[i].mea < 60 && data[i].max < 80){
      data[i].cat = 4;
      num_irrelevante += 1;
    }
  }

  for(int i=0; i<N; i++){
    printf("%s %.2lf %.2lf %.2lf %.2lf\n", data[i].termo, data[i].max, data[i].min, data[i].mea, data[i].std);
  }

  printf("\n\n");
  printf("RESULTADO:\n");
  printf("Bot (%ld):", num_bot);
  for(int i=0; i<N; i++){
    if(data[i].cat == 0)
      printf(" %s", data[i].termo);
  }
  printf("\n");

  printf("Surpreendente (%ld):", num_surpreendente);
  for(int i=0; i<N; i++){
    if(data[i].cat == 1)
      printf(" %s", data[i].termo);
  }
  printf("\n");

  printf("Normal (%ld):", num_normal);
  for(int i=0; i<N; i++){
    if(data[i].cat == 2)
      printf(" %s", data[i].termo);
  }
  printf("\n");

  printf("Local (%ld):", num_local);
  for(int i=0; i<N; i++){
    if(data[i].cat == 3)
      printf(" %s", data[i].termo);
  }
  printf("\n");

  printf("Irrelevante (%ld):", num_irrelevante);
  for(int i=0; i<N; i++){
    if(data[i].cat == 4)
      printf(" %s", data[i].termo);
  }
  //printf("\n");

  destroiArrayData(&data, N);
return(0);
}
