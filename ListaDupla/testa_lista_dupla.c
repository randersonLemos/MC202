#include "lista_dupla.h"

int main(){

  ListaDupla *lista = cria_lista_dupla_vazia();

  insere_fim_lista_dupla(lista, 5);
  insere_fim_lista_dupla(lista, 5);
  insere_fim_lista_dupla(lista, 5);

  imprime_lista_dupla(lista);

  destroi_lista_dupla(&lista);
return(0);
}
