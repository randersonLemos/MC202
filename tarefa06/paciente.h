#ifndef PACIENTE_H_
#define PACIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla.h"

/* Lista dupla circular e com no cabeca ficticio */

typedef struct _paciente {
  long id;
  char nome[50];
  char prioridade[15];
  ListaDupla *atendimento_lista;
} Paciente;

Paciente *cria_paciente();

void destroi_paciente(Paciente **paciente);

void imprime_paciente(Paciente *paciente);

void copia_paciente(Paciente *origem, Paciente **destino);


typedef struct no_fila_paciente {
  struct no_fila_paciente *ant;
  struct no_fila_paciente *pro;
  Paciente *paciente;
  int tam;
} NoFilaPaciente, FilaPaciente;

NoFilaPaciente *cria_no_fila_paciente(Paciente *paciente);

FilaPaciente *cria_fila_paciente_vazia();

bool fila_paciente_vazia(FilaPaciente *inicio);

void insere_inicio_fila_paciente(FilaPaciente *inicio, Paciente *paciente);

void insere_fim_fila_paciente(FilaPaciente *inicio, Paciente *paciente);

bool remove_inicio_fila_paciente(FilaPaciente *inicio, Paciente **paciente);

void esvazia_fila_paciente(FilaPaciente *inicio);

void destroi_fila_paciente(FilaPaciente **inicio);

void imprime_fila_paciente(FilaPaciente *inicio);

void ordena_fila_paciente(FilaPaciente *inicio);

#endif
