#include "paciente.h"


Paciente *cria_paciente()
{
  Paciente *paciente = (Paciente *)calloc(1, sizeof(Paciente));
  paciente->id=-1;
  for(int i=0; i<50; i++) paciente->nome[i] = '\0';
  for(int i=0; i<15; i++) paciente->prioridade[i] = '\0';
  paciente->atendimento_lista = cria_lista_dupla_vazia();
  return(paciente);
}


void destroi_paciente(Paciente **paciente)
{
  destroi_lista_dupla(&((*paciente)->atendimento_lista));
  free(*paciente);
}


void imprime_paciente(Paciente *paciente)
{
  ListaDupla *inicio = paciente->atendimento_lista;

  printf("%li %s %s", paciente->id, paciente->nome, paciente->prioridade);
  for(int i=0; i<inicio->tam; i++){
    int j;
    retorna_elemento_inicio_lista_dupla(inicio, i, &j);
    printf(" %c", j);
  }
  printf("\n");
}


void copia_paciente(Paciente *origem, Paciente **destino)
{
 (*destino)->id = origem->id;
  for(int i=0; i<50; i++) (*destino)->nome[i] = origem->nome[i];
  for(int i=0; i<15; i++) (*destino)->prioridade[i] = origem->prioridade[i];
  copia_lista_dupla(origem->atendimento_lista, (*destino)->atendimento_lista);
}


NoFilaPaciente *cria_no_fila_paciente(Paciente *paciente)
{
  NoFilaPaciente *no = (NoFilaPaciente *)calloc(1, sizeof(NoFilaPaciente));
  no->ant = no;
  no->pro = no;
  no->paciente = paciente;
  return(no);
}


FilaPaciente *cria_fila_paciente_vazia()
{
  Paciente *paciente = cria_paciente();
  FilaPaciente *inicio = cria_no_fila_paciente(paciente);
  inicio->tam = 0;

  return(inicio);
}


bool fila_paciente_vazia(FilaPaciente *inicio)
{
  if(inicio->pro == inicio){
    return(true);
  }
  return(false);
}


void insere_inicio_fila_paciente(FilaPaciente *inicio, Paciente *paciente)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoFilaPaciente *p = cria_no_fila_paciente(paciente);
  NoFilaPaciente *q = inicio->pro;

  inicio->pro = p;
  p->ant = inicio;
  p->pro = q;
  q->ant = p;
  inicio->tam += 1;
}


void insere_fim_fila_paciente(FilaPaciente *inicio, Paciente *paciente)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoFilaPaciente *p = cria_no_fila_paciente(paciente);
  NoFilaPaciente *q = inicio->ant;

  inicio->ant = p;
  p->pro = inicio;
  p->ant = q;
  q->pro = p;
  inicio->tam += 1;
}


bool remove_inicio_fila_paciente(FilaPaciente *inicio, Paciente **paciente)
{
  if(!fila_paciente_vazia(inicio)){
    NoFilaPaciente *primeiro = inicio->pro, *segundo = primeiro->pro;
    copia_paciente(primeiro->paciente, paciente);
    inicio->pro = segundo;
    segundo->ant = inicio;
    destroi_paciente(&(primeiro->paciente));
    free(primeiro);
    primeiro=NULL;
    inicio->tam -= 1;
    return(true);
  }
  //destroi_paciente(paciente);
  //*paciente = cria_paciente();
  return(false);
}


void esvazia_fila_paciente(FilaPaciente *inicio)
{
  Paciente *paciente = cria_paciente();
  while (!fila_paciente_vazia(inicio)){
    //imprime_fila_paciente(inicio); printf("\n"); imprime_paciente(paciente); printf("\n");
    remove_inicio_fila_paciente(inicio, &paciente);
  }
  //imprime_fila_paciente(inicio); printf("\n"); imprime_paciente(paciente); printf("\n");
  destroi_paciente(&paciente);
}


void destroi_fila_paciente(FilaPaciente **inicio)
{
  if( *inicio != NULL ){
    esvazia_fila_paciente(*inicio);
    destroi_paciente(&((*inicio)->paciente));
    free(*inicio);
    *inicio=NULL;
  }
}

void imprime_fila_paciente(FilaPaciente *inicio)
{
  NoFilaPaciente *p = inicio->pro;

  if(fila_paciente_vazia(inicio)){
    printf("<-(%p)x(%p)->", inicio->ant, inicio->pro);
    printf("\n");
  }

  while(p != inicio){
    imprime_paciente(p->paciente);
    p = p->pro;
  }
}

void ordena_fila_paciente(FilaPaciente *inicio)
{

NoFilaPaciente *p = inicio->pro;

while (p != inicio){
  NoFilaPaciente *q = p->pro;
    while (q != inicio){
        if (p->paciente->id > q->paciente->id){ //se maior troca o conteudo das duas pessoas
          Paciente *paciente = cria_paciente();
          Paciente *Paciente = cria_paciente();
          copia_paciente(p->paciente, &paciente);
          copia_paciente(q->paciente, &Paciente);

          copia_paciente(paciente, &(q->paciente));
          copia_paciente(Paciente, &(p->paciente));

          destroi_paciente(&paciente);
          destroi_paciente(&Paciente);
        }
        q = q->pro;
    }
    p = p->pro;
}

}
