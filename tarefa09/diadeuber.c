#include "Heap.h"

typedef struct _motorista{
  int x_atual;
  int y_atual;
  int dtc; // Distância total corrida
  int dtp; // Distância total percorrida
  Boolean livre;
  Cliente *cliente;
} Motorista;

Motorista CriaMotorista(){
  Motorista motorista;

  motorista.x_atual = 0;
  motorista.y_atual = 0;
  motorista.dtc = 0;
  motorista.dtp = 0;

  motorista.livre = true;
  motorista.cliente = (Cliente *)calloc(1, sizeof(Cliente));

  return motorista;
}

void ImprimeMotorista(Motorista motorista)
{
  printf("%6d %6d %6d %6d", motorista.x_atual, motorista.y_atual, motorista.dtc, motorista.dtp);
}

void ContabilizaCorrida(Motorista *motorista, Cliente cliente)
{
  int dtc = 0; // Distância total corrida
  int dtp = 0; // Distância total percorrida

  dtp = abs((*motorista).x_atual - cliente.x_atual) + abs((*motorista).y_atual - cliente.y_atual);

  (*motorista).x_atual = cliente.x_atual;
  (*motorista).y_atual = cliente.y_atual;

  dtc = abs((*motorista).x_atual - cliente.x_destino) + abs((*motorista).y_atual - cliente.y_destino);
  dtp += dtc;

  (*motorista).dtc += dtc;
  (*motorista).dtp += dtp;

  (*motorista).x_atual = cliente.x_destino;
  (*motorista).y_atual = cliente.y_destino;
}

int main()
{

Heap *heap = CriaHeap(9999);
Motorista motorista = CriaMotorista();
double taxa_cancelamento = 0.0;

char letter;

while(scanf("%c ", &letter) != EOF)
{
  if(letter == 'A')
  {
    char nome[20]; double avaliacao; int x_cliente, y_cliente, x_destino, y_destino;
    scanf("%s %lf %d %d %d %d ", nome, &avaliacao, &x_cliente, &y_cliente, &x_destino, &y_destino);
    InsereHeap(heap, avaliacao, nome, x_cliente, y_cliente, x_destino, y_destino);
    printf("Cliente %s foi adicionado(a)\n", nome);

    if(motorista.livre)
    {
      motorista.livre = false;
      *(motorista.cliente) = RemoveHeap(heap);
    }
  }
  else if(letter == 'F')
  {
    motorista.livre = true;
    ContabilizaCorrida(&motorista, *(motorista.cliente));
    printf("A corrida de %s foi finalizada\n", motorista.cliente->nome);

    if(!HeapVazio(heap))
    {
      motorista.livre = false;
      *(motorista.cliente) = RemoveHeap(heap);
    }
  }
  else if(letter == 'C')
  {
    char nome[20];
    scanf("%s ", nome);
    Cliente cliente = RemoveClienteHeap(heap, nome);
    printf("%s cancelou a corrida\n", cliente.nome);

    taxa_cancelamento += 7.0;
  }
  else if(letter == 'T')
  {
    double rendimento_bruto = taxa_cancelamento + motorista.dtc*1.40;
    double despesas = 57.00 + motorista.dtp/10.0*4.104;
    double rendimento_liquido = rendimento_bruto*0.75 - despesas;

    printf("\n");
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", motorista.dtp);
    printf("Rendimento bruto: %.2lf\n", rendimento_bruto);
    printf("Despesas: %.2lf\n", despesas);
    printf("Rendimento liquido: %.2lf\n", rendimento_liquido);
  }
}

DestroiHeap(&heap);
free(motorista.cliente);
return(0);
}
