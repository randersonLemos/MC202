#include <stdio.h>
#include <stdlib.h>

typedef enum _bool
{
  false, true
} bool;

/* IMPLEMENTAÇÂO DE UMA LISTA DUPLAMENTE LIGADA */

typedef struct no_lista_dupla
{
  struct no_lista_dupla *ant;
  struct no_lista_dupla *pro;
  int ele;
  int tam;
} ListaDupla, NoListaDupla;


NoListaDupla *cria_no_dupla(int ele)
{
  NoListaDupla *no = (NoListaDupla *)calloc(1, sizeof(NoListaDupla));
  no->ant = no;
  no->pro = no;
  no->ele = ele;

  return(no);
}


NoListaDupla *cria_lista_dupla_vazia()
{
  ListaDupla *inicio = cria_no_dupla(0);
  inicio->tam = 0;

  return(inicio);
}


bool lista_dupla_vazia(ListaDupla *inicio)
{
  if(inicio->pro == inicio){
    return(true);
  }

  return(false);
}


void imprime_lista_dupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->pro;

  if(lista_dupla_vazia(inicio)){
    printf("<-- (%p) x (%p) -->", inicio->ant, inicio->pro);
  }

  while(p != inicio){
    if (p->ant == inicio){ // primeiro nó da lista
      printf("<--");
    }
    printf(" (%p) %d (%p) ", p->ant, p->ele, p->pro);
    if (p->pro == inicio){
      printf("-->");
    }
    else{
      printf("<-->");
    }
    p = p->pro;
  }
}


void imprime_breve_lista_dupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->pro;

  if(lista_dupla_vazia(inicio)){
    printf("<-(%p)x(%p)->", inicio->ant, inicio->pro);
  }

  while(p != inicio){
    if (p->ant == inicio){ // primeiro nó da lista
      //printf("<-");
    }
    //printf(" (%p) %d (%p) ", p->ant, p->ele, p->pro);
    printf("%d", p->ele);
    if (p->pro == inicio){
      //printf("->");
    }
    else{
      //printf("<->");
    }
    p = p->pro;
  }
}


bool busca_elemento_lista_dupla(ListaDupla *inicio, int ele, NoListaDupla **no)
{
  inicio->ele = ele;

  (*no) = inicio->pro;
  while((*no)->ele != ele){
    (*no) = (*no)->pro;
  }

  if((*no) == inicio){
    return(false);
  }
  return(true);
}


void insere_inicio_lista_dupla(ListaDupla *inicio, int ele)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoListaDupla *p = cria_no_dupla(ele);
  NoListaDupla *q = inicio->pro;

  inicio->pro = p;
  p->ant = inicio;
  p->pro = q;
  q->ant = p;
  inicio->tam += 1;
}


void insere_fim_lista_dupla(ListaDupla *inicio, int ele)
{
  if(inicio == NULL)
    printf("[Erro] inicio = NULL...");

  NoListaDupla *p = cria_no_dupla(ele);
  NoListaDupla *q = inicio->ant;

  inicio->ant = p;
  p->pro = inicio;
  p->ant = q;
  q->pro = p;
  inicio->tam += 1;
}


bool insere_elemento_antes_chave_lista_dupla(ListaDupla *inicio, int ele, int chave)
{
  NoListaDupla *pno=NULL;

  if(busca_elemento_lista_dupla(inicio, chave, &pno)){
    NoListaDupla *p = cria_no_dupla(ele);
    p->pro = pno;
    p->ant = pno->ant;
    p->ant->pro = p;
    pno->ant = p;
    inicio->tam += 1;
    return(true);
  }
  return(false);
}


bool remove_inicio_lista_dupla(ListaDupla *inicio, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    NoListaDupla *primeiro = inicio->pro, *segundo = primeiro->pro;
    *ele = primeiro->ele;
    inicio->pro = segundo;
    segundo->ant = inicio;
    free(primeiro);
    inicio->tam -= 1;
    return(true);
  }

  return(false);
}


bool remove_elemento_lista_dupla(ListaDupla *inicio, int ele)
{
  NoListaDupla *pno=NULL;

  if(busca_elemento_lista_dupla(inicio, ele, &pno)){
    NoListaDupla *anterior = pno->ant, *posterior = pno->pro;
    anterior->pro = posterior;
    posterior->ant = anterior;
    free(pno);
    inicio->tam -= 1;
    return(true);
  }
  return(false);
}


bool remove_fim_lista_dupla(ListaDupla *inicio, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    NoListaDupla *ultimo = inicio->ant, *penultimo = ultimo->ant;
    *ele = ultimo->ele;
    penultimo->pro = inicio;
    inicio->ant = penultimo;
    free(ultimo);
    inicio->tam -= 1;
    return(true);
  }

  return(false);
}


void esvazia_lista_dupla(ListaDupla *inicio)
{
  int ele;
  while (!lista_dupla_vazia(inicio)){
    remove_inicio_lista_dupla(inicio, &ele);
  }
}


void destroi_lista_dupla(ListaDupla **inicio)
{
  int ele;
  if( *inicio != NULL){
    while(!lista_dupla_vazia(*inicio)){
      remove_inicio_lista_dupla(*inicio, &ele);
    }
    free(*inicio);
    *inicio=NULL;
  }

}


bool retorna_elemento_inicio_lista_dupla(ListaDupla *inicio, int pos, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    if(inicio->tam > pos){
      NoListaDupla *no = inicio->pro;
      for(int i=0; i<pos; i++){
        no = no->pro;
      }
      *ele = no->ele;
      return(true);
    }
  }
  return(false);
}


bool retorna_elemento_fim_lista_dupla(ListaDupla *inicio, int pos, int *ele)
{
  if(!lista_dupla_vazia(inicio)){
    if(inicio->tam > pos){
      NoListaDupla *no = inicio->ant;
      for(int i=0; i<pos; i++){
        no = no->ant;
      }
      *ele = no->ele;
      return(true);
    }
  }
  return(false);
}


void copia_lista_dupla(ListaDupla *origem, ListaDupla *destino)
{
  int ele;
  esvazia_lista_dupla(destino);
  for(int i=0; i<origem->tam; i++){
    retorna_elemento_inicio_lista_dupla(origem, i, &ele);
    insere_fim_lista_dupla(destino, ele);
  }
}


int verifica_numero_maior(ListaDupla *inicio, ListaDupla *Inicio, ListaDupla **maior, ListaDupla **menor){
  int tam = inicio->tam;
  for(int i=0; i<tam; i++){
    int algarismo, Algarismo;
    retorna_elemento_inicio_lista_dupla( inicio, i, &algarismo );
    retorna_elemento_inicio_lista_dupla( Inicio, i, &Algarismo );
    if(algarismo > Algarismo){
      *maior = inicio;
      *menor = Inicio;
      return(-1);
    }
    else if(Algarismo > algarismo){
      *maior = Inicio;
      *menor = inicio;
      return(1);
    }
  }
  *maior = inicio;
  *menor = Inicio;
  return(0);
}


void remove_zeros_esquerda(ListaDupla *INICIO)
/* Remove zeros a esqueda da lista dupla*/
{
  int ele;
  while(!lista_dupla_vazia(INICIO)){
    retorna_elemento_inicio_lista_dupla(INICIO, 0, &ele);
    if(ele == 0){
      remove_inicio_lista_dupla(INICIO, &ele);
    }
    else{
      break;
    }
  }
  if(lista_dupla_vazia(INICIO)){
    insere_inicio_lista_dupla(INICIO, 0);
  }
}


void soma(ListaDupla *inicio, ListaDupla *Inicio, ListaDupla *INICIO)
{
  int diferenca = inicio->tam - Inicio->tam;
  if(diferenca <= 0){ // adicionando zeros na menor lista
    for(int i=0; i<(-1)*diferenca; i++)
      insere_inicio_lista_dupla( inicio, 0);
  }
  else{
    for(int i=0; i<diferenca; i++)
      insere_inicio_lista_dupla( Inicio, 0);
  }

  esvazia_lista_dupla(INICIO);
  int tamanho = inicio->tam;
  int zero_ou_um = 0;
  for(int i=0; i<tamanho; i++){
    int algarismo, Algarismo, ALGARISMO;
    retorna_elemento_fim_lista_dupla( inicio, i, &algarismo );
    retorna_elemento_fim_lista_dupla( Inicio, i, &Algarismo );

    ALGARISMO = algarismo + Algarismo + zero_ou_um;
    zero_ou_um = 0;
    if(ALGARISMO < 10){
      insere_inicio_lista_dupla( INICIO, ALGARISMO );
    }
    else{
      ALGARISMO = ALGARISMO - 10;
      insere_inicio_lista_dupla( INICIO, ALGARISMO );
      zero_ou_um = 1;
    }
  }
  if(zero_ou_um){
    insere_inicio_lista_dupla( INICIO, 1 );
  }

  remove_zeros_esquerda(inicio);
  remove_zeros_esquerda(Inicio);
  remove_zeros_esquerda(INICIO);
}


void subtrai(ListaDupla *inicio, ListaDupla *Inicio, ListaDupla *INICIO)
{
  int diferenca = inicio->tam - Inicio->tam;
  if(diferenca <= 0){ // adicionando zeros na menor lista
    for(int i=0; i<(-1)*diferenca; i++)
      insere_inicio_lista_dupla( inicio, 0);
  }
  else{
    for(int i=0; i<diferenca; i++)
      insere_inicio_lista_dupla( Inicio, 0);
  }

  esvazia_lista_dupla(INICIO);
  int tamanho = inicio->tam;
  int zero_ou_um = 0;
  ListaDupla *maior=NULL;
  ListaDupla *menor=NULL;
  verifica_numero_maior(inicio, Inicio, &maior, &menor);
  for(int i=0; i<tamanho; i++){
    int algarismo, Algarismo, ALGARISMO;
    retorna_elemento_fim_lista_dupla( maior, i, &algarismo );
    retorna_elemento_fim_lista_dupla( menor, i, &Algarismo );

    ALGARISMO = algarismo - Algarismo - zero_ou_um;
    zero_ou_um = 0;
    if(ALGARISMO >= 0){
      insere_inicio_lista_dupla( INICIO, ALGARISMO );
    }
    else{
      ALGARISMO = ALGARISMO + 10;
      insere_inicio_lista_dupla( INICIO, ALGARISMO );
      zero_ou_um = 1;
    }
  }

  remove_zeros_esquerda(inicio);
  remove_zeros_esquerda(Inicio);
  remove_zeros_esquerda(INICIO);
}

void multiplica(ListaDupla *inicio, ListaDupla *Inicio, ListaDupla *INICIO)
{
  ListaDupla *TMP = cria_lista_dupla_vazia();
  ListaDupla *COPY = cria_lista_dupla_vazia();

  int entre_zero_nove = 0;
  ListaDupla *maior=NULL;
  ListaDupla *menor=NULL;
  verifica_numero_maior(inicio, Inicio, &maior, &menor);
  for(int i=0; i<menor->tam; i++){
    int algarismo, Algarismo, ALGARISMO;

    for(int w=0; w<i; w++){
      insere_inicio_lista_dupla( TMP, 0 );
    }

    retorna_elemento_fim_lista_dupla( menor, i, &algarismo );

    for(int j=0; j<maior->tam; j++){
      retorna_elemento_fim_lista_dupla( maior, j, &Algarismo );
      ALGARISMO = algarismo*Algarismo + entre_zero_nove;
      entre_zero_nove = 0;
      if(ALGARISMO < 10){
        insere_inicio_lista_dupla( TMP, ALGARISMO );
      }
      else{
        int resto = ALGARISMO%10;
        insere_inicio_lista_dupla( TMP, resto );
        entre_zero_nove = (int)ALGARISMO/10;
      }
    }
    if(entre_zero_nove){
      insere_inicio_lista_dupla( TMP, entre_zero_nove );
      entre_zero_nove = 0;
    }
  copia_lista_dupla(INICIO, COPY);
  soma(TMP, COPY, INICIO);
  esvazia_lista_dupla(TMP);
  }

  destroi_lista_dupla(&TMP);
  destroi_lista_dupla(&COPY);
}

int main(){

int qty; // numero de operações
char tmp;
scanf("%d%c", &qty, &tmp);

for(int i = 0; i < qty; i++ ){
  char ch;
  char operacao;
  char primeira = true;
  ListaDupla *numero = cria_lista_dupla_vazia();
  ListaDupla *Numero = cria_lista_dupla_vazia();
  ListaDupla *NUMERO = cria_lista_dupla_vazia();
  scanf("%c%c", &operacao, &tmp);
  while(true){ // lendo números

    scanf("%c", &ch);

    if( ch == ' ' ){
      primeira = false;
    }

    else if( ch == '\n'){
      break;
    }

    else{
      if(primeira){ // primeiro número
        insere_fim_lista_dupla( numero, (int)ch-48 );
      }
      else{ // segundo número
        insere_fim_lista_dupla( Numero, (int)ch-48 );
      }
    }
  }

  // SOMA
  if(operacao == '+'){
    soma(numero, Numero, NUMERO);
  }
  // SUBTRAÇÃO
  else if(operacao == '-'){
    subtrai(numero, Numero, NUMERO);
  }
  // MULTIPLICAÇÂO
  else if(operacao == '*'){
    multiplica(numero, Numero, NUMERO);
  }
  else if(operacao == '/'){

  }
  else{
    printf("[ERRO] Operação não disponível...");
  }

  //imprime_breve_lista_dupla(numero);
  //printf("\n");
  //imprime_breve_lista_dupla(Numero);
  //printf("\n%c\n", operacao);
  imprime_breve_lista_dupla(NUMERO);
  printf("\n");
  //printf("\n");

  destroi_lista_dupla(&numero);
  destroi_lista_dupla(&Numero);
  destroi_lista_dupla(&NUMERO);
}
return(0);
}
