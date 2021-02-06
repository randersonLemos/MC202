#include <stdio.h>
#include "professor_carlos.h"

void carrega_turmas(Turma turmas[], int num_turmas){
  for(int i=0; i<num_turmas; i++){
    int num_alunos = 0;
    scanf("%d", &num_alunos);
    turmas[i].qtd = num_alunos;
    for(int j=0; j<num_alunos; j++){
      scanf("%s %s", turmas[i].alunos[j].nome, turmas[i].alunos[j].sobrenome);
      scanf("%d %d %d", &turmas[i].alunos[j].nascimento.dia, &turmas[i].alunos[j].nascimento.mes, &turmas[i].alunos[j].nascimento.ano);
    }
  }
}

int main(){
  int num_turmas = 0; int num_operacoes = 0;
  scanf("%d %d", &num_turmas, &num_operacoes);

  Turma turmas[50];
  carrega_turmas(turmas, num_turmas);

  int operacao = -1;
  while(scanf("%d", &operacao) != EOF){
    int turma;
    char padrao[6];
    Aluno alunO;

    switch(operacao){
      case 1:
        //printf("-Operacao 1\n");
        scanf("%d", &turma);
        alunO = procura_novo_na_turma(turmas, num_turmas, turma);
        //ver_turma(pts, turma);
        //ver_aluno(alunO);
        printf("%s\n", alunO.nome);
        //printf("%s %s\n", alunO.nome, alunO.sobrenome);
      break;

      case 2:
        //printf("-Operacao 2\n");
        scanf("%d", &turma);
        alunO =  procura_velho_na_turma(turmas, num_turmas, turma);
        //ver_turma(turmas, turma);
        //ver_aluno(alunO);
        printf("%s\n", alunO.sobrenome);
        //printf("%s %s\n", alunO.nome, alunO.sobrenome);
      break;

      case 3:
        //printf("-Operacao 3\n");
        alunO = procura_velho_todas_turmas(turmas, num_turmas);
        printf("%s\n", alunO.nome);
      break;

      case 4:
        //printf("-Operacao 4\n");
        alunO = procura_novo_todas_turmas(turmas, num_turmas);
        printf("%s\n", alunO.sobrenome);
      break;

      case 5:
        scanf("%d", &turma);
        scanf("%s", padrao);
        int num_alunos = conta_substrings(turmas, num_turmas, padrao);
        printf("%d\n", num_alunos);
      break;

      case 6:
        //printf("-Operacao 6\n");
        scanf("%d", &turma);
        scanf("%s %s", alunO.nome, alunO.sobrenome);
        scanf("%d %d %d", &alunO.nascimento.dia, &alunO.nascimento.mes, &alunO.nascimento.ano);
        //ver_turma(pts, turma);
        //printf("qtd=%d\n", pts[turma].qtd);
        add_aluno(turmas, alunO, turma);
        //ver_turma(pts, turma);
        //printf("qtd=%d\n", pts[turma].qtd);
        printf("%d\n", turmas[turma].qtd);
      break;

      case 7:
        //printf("-Operacao 7\n");
        scanf("%d", &turma);
        remove_aluno(turmas, turma);
        printf("%d\n", turmas[turma].qtd);
      break;

      default:
        printf("valor invalido\n");
    }
  }
  return(0);
}
