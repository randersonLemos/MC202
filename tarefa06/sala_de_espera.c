#include <stdio.h>
#include <string.h>
#include "paciente.h"

int main()
{

FilaPaciente *filas[9];

for(int i=0; i<9; i++){
  filas[i] = cria_fila_paciente_vazia();
}


long count = 0;
char nome[50];

while(scanf("\"%[^\"]\"", nome) != EOF){
  /* CARREGA PACIENTES */
  Paciente *paciente = cria_paciente();
  paciente->id = count; count++;
  strcpy(paciente->nome, nome);

  scanf("%s", paciente->prioridade);

  char atendimento;
  while(scanf("%c", &atendimento)){
    if(atendimento == '\n')
      break;

    if(atendimento >= 49 && atendimento <= 57){ // de 1 (49) à 9 (57)
      insere_fim_lista_dupla(paciente->atendimento_lista, atendimento);
    }
  }

  /* ADICIONA PACIENTE NA FILA DE ATENDIMENTO  */
  int idx;
  retorna_elemento_inicio_lista_dupla(paciente->atendimento_lista, 0, &idx);
  if(strcmp(paciente->prioridade, "normal") == 0)
    insere_fim_fila_paciente(filas[idx-49], paciente);
  else
    insere_inicio_fila_paciente(filas[idx-49], paciente);
}

/* COMEÇA ATENDIMENTOS */
int minutos = 0;
int atendimento;
FilaPaciente *pacientes_atendidos = cria_fila_paciente_vazia();
while(true){
  minutos += 10;
  int fila_com_paciente = 0;
  for(int i=0; i<9; i++)
    fila_com_paciente += !fila_paciente_vazia(filas[i]);

  if(fila_com_paciente == 0)
    break;

  /* ATENDIMENTOS */
  for(int i=0; i<9; i++){
    FilaPaciente *fila = filas[i];
    if(i+1 == 1){
      for(int j=0; j<10; j++){ // 10 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 2){
      for(int j=0; j<2; j++){ // 2 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 3){
      for(int j=0; j<5; j++){ // 5 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 4){
      for(int j=0; j<3; j++){ // 3 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 5){
      for(int j=0; j<4; j++){ // 4 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 6){
      for(int j=0; j<7; j++){ // 7 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 7){
      for(int j=0; j<2; j++){ // 2 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 8){
      for(int j=0; j<1; j++){ // 1 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
    else if(i+1 == 9){
      for(int j=0; j<4; j++){ // 4 profissionais
        if(!fila_paciente_vazia(fila)){
          Paciente *paciente = cria_paciente();
          remove_inicio_fila_paciente(fila, &paciente);
          remove_inicio_lista_dupla(paciente->atendimento_lista, &atendimento);
          insere_fim_fila_paciente(pacientes_atendidos, paciente);
        }
      }
    }
  }
  //
  // PRECISA SORTEAR pacientes_atendidos
  //

  /* VER (POSSÍVEIS) PRÓXIMOS ATENDIMENTOS */
  ordena_fila_paciente(pacientes_atendidos);

  //printf("PACIENTES ATENDIDOS (%d)\n", minutos);
  //imprime_fila_paciente(pacientes_atendidos);
  //printf("\n");
  while(!fila_paciente_vazia(pacientes_atendidos)){
     Paciente *paciente = cria_paciente();
     remove_inicio_fila_paciente(pacientes_atendidos, &paciente);
     if(lista_dupla_vazia(paciente->atendimento_lista)){ // PACIENTE SEM MAIS ATENDIMENTOS
       printf("%02d:%02d %s\n", 8+(int)minutos/60, minutos%60, paciente->nome);
       destroi_paciente(&paciente);
     }
     else{ // PACIENTE COM MAIS ATENDIMENTOS
       int idx;
       retorna_elemento_inicio_lista_dupla(paciente->atendimento_lista, 0, &idx);
       if(strcmp(paciente->prioridade, "normal") == 0)
        insere_fim_fila_paciente(filas[idx-49], paciente);
       else
        insere_inicio_fila_paciente(filas[idx-49], paciente);
    }
  }
}
//imprime_fila_paciente(pacientes_atendidos);
destroi_fila_paciente(&pacientes_atendidos);


//for(int i=0; i<9; i++){
//  imprime_fila_paciente(filas[i]);
//  }


for(int i=0; i<9; i++)
  destroi_fila_paciente(&filas[i]);

return(0);
}
