#include "professor_carlos.h"
#include <stdio.h>
#include <string.h>


void ver_turma(Turma *pt, long i){ // Função utilizada para debug
  printf("-Turma %ld\n", i);
  for(int j=0; j<(pt+i)->qtd; j++){
    printf("%s %s %d %d %d\n", (pt+i)->alunos[j].nome, (pt+i)->alunos[j].sobrenome,
        (pt+i)->alunos[j].nascimento.dia,
        (pt+i)->alunos[j].nascimento.mes,
        (pt+i)->alunos[j].nascimento.ano);
  }
}


void ver_aluno(Aluno a){ // Função utilizada para debug
    printf("-Aluno %s %s %d %d %d\n",
        a.nome,
        a.sobrenome,
        a.nascimento.dia,
        a.nascimento.mes,
        a.nascimento.ano);
}


void copia_string(char *origin, char *destiny){
  int i = 0;
  do{
    destiny[i] = origin[i]; i++;
  }while(origin[i] != '\0');
  destiny[i] = '\0';
}


int conta_string(char *str){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return(i);
}


int tem_substring(char *sub_str, char *str){
  int substr_size = conta_string(sub_str);
  int str_size = conta_string(str);
  if(substr_size > str_size){
    return(0);
  }

  int j=0;
  for(int i=0; i<str_size; i++){
    if(str[i] == sub_str[j]){
      j++;
      if(j == substr_size){
        return(1);
      }
    }
    else{
      j=0;
    }
  }
  return(0);
}


int compara_string(char *str1, char *str2){
  int menor = 0;

  if(conta_string(str1) <= (conta_string(str2))){
    menor = conta_string(str1);
  }
  else{
    menor = conta_string(str2);
  }

  for(int i=0; i<menor; i++){
    if(str1[i] < str2[i]){
      return(-1);
    }

    if (str1[i] > str2[i]){
      return(1);
    }
  }

  if(conta_string(str1) < conta_string(str2)){
    return(-1);
  }
  else if(conta_string(str1) > conta_string(str2)){
    return(1);
  }
  else{
    return(0);
  }
}


Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
  Aluno novo;

  copia_string(t[j].alunos[0].nome, novo.nome);
  copia_string(t[j].alunos[0].sobrenome, novo.sobrenome);
  novo.nascimento.dia = t[j].alunos[0].nascimento.dia;
  novo.nascimento.mes = t[j].alunos[0].nascimento.mes;
  novo.nascimento.ano = t[j].alunos[0].nascimento.ano;

  //ver_turma(t, j);

  for(int i=0; i<t[j].qtd; i++){
    int mais_novo = 0;

    if (t[j].alunos[i].nascimento.ano > novo.nascimento.ano){ mais_novo = 1; }

    if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes >  novo.nascimento.mes)){ mais_novo = 1; }

    if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia >  novo.nascimento.dia)){ mais_novo = 1; }

    if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia == novo.nascimento.dia) &&
        (compara_string(t[j].alunos[i].nome, novo.nome) < 0)){ mais_novo = 1; }

    if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia == novo.nascimento.dia) &&
        (compara_string(t[j].alunos[i].nome, novo.nome) == 0) &&
        (compara_string(t[j].alunos[i].sobrenome, novo.sobrenome) < 0)){ mais_novo = 1; }

    if(mais_novo){
      novo.nascimento.dia = t[j].alunos[i].nascimento.dia;
      novo.nascimento.mes = t[j].alunos[i].nascimento.mes;
      novo.nascimento.ano = t[j].alunos[i].nascimento.ano;
      copia_string(t[j].alunos[i].nome, novo.nome);
      copia_string(t[j].alunos[i].sobrenome, novo.sobrenome);
      mais_novo = 0;
    }
  }
  return(novo);
}


Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
  Aluno velho;

  copia_string(t[j].alunos[0].nome, velho.nome);
  copia_string(t[j].alunos[0].sobrenome, velho.sobrenome);
  velho.nascimento.dia = t[j].alunos[0].nascimento.dia;
  velho.nascimento.mes = t[j].alunos[0].nascimento.mes;
  velho.nascimento.ano = t[j].alunos[0].nascimento.ano;

  //ver_turma(t, j);

  for(int i=0; i<t[j].qtd; i++){
    int mais_velho = 0;

    if (t[j].alunos[i].nascimento.ano < velho.nascimento.ano){ mais_velho = 1; }

    if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes <  velho.nascimento.mes)){ mais_velho = 1; }

    if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia <  velho.nascimento.dia)){ mais_velho = 1; }

    if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia == velho.nascimento.dia) &&
        (compara_string(t[j].alunos[i].nome, velho.nome) < 0)){ mais_velho = 1; }

    if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
        (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
        (t[j].alunos[i].nascimento.dia == velho.nascimento.dia) &&
        (compara_string(t[j].alunos[i].nome, velho.nome) == 0) &&
        (compara_string(t[j].alunos[i].sobrenome, velho.sobrenome) < 0)){ mais_velho = 1; }

    if(mais_velho){
      velho.nascimento.dia = t[j].alunos[i].nascimento.dia;
      velho.nascimento.mes = t[j].alunos[i].nascimento.mes;
      velho.nascimento.ano = t[j].alunos[i].nascimento.ano;
      copia_string(t[j].alunos[i].nome, velho.nome);
      copia_string(t[j].alunos[i].sobrenome, velho.sobrenome);
      mais_velho = 0;
    }
  }
  return(velho);
}


Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
  Aluno novo;

  copia_string(t[0].alunos[0].nome, novo.nome);
  copia_string(t[0].alunos[0].sobrenome, novo.sobrenome);
  novo.nascimento.dia = t[0].alunos[0].nascimento.dia;
  novo.nascimento.mes = t[0].alunos[0].nascimento.mes;
  novo.nascimento.ano = t[0].alunos[0].nascimento.ano;

  //ver_turma(t, j);

  for(int j=0; j<qtd_turmas; j++){
    for(int i=0; i<t[j].qtd; i++){
      int mais_novo = 0;

        if (t[j].alunos[i].nascimento.ano > novo.nascimento.ano){ mais_novo = 1; }

        if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
            (t[j].alunos[i].nascimento.mes >  novo.nascimento.mes)){ mais_novo = 1; }

        if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
            (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
            (t[j].alunos[i].nascimento.dia >  novo.nascimento.dia)){ mais_novo = 1; }

        if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
            (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
            (t[j].alunos[i].nascimento.dia == novo.nascimento.dia) &&
            (compara_string(t[j].alunos[i].nome, novo.nome) < 0)){ mais_novo = 1; }

        if ((t[j].alunos[i].nascimento.ano == novo.nascimento.ano) &&
            (t[j].alunos[i].nascimento.mes == novo.nascimento.mes) &&
            (t[j].alunos[i].nascimento.dia == novo.nascimento.dia) &&
            (compara_string(t[j].alunos[i].nome, novo.nome) == 0) &&
            (compara_string(t[j].alunos[i].sobrenome, novo.sobrenome) < 0)){ mais_novo = 1; }

        if(mais_novo){
          novo.nascimento.dia = t[j].alunos[i].nascimento.dia;
          novo.nascimento.mes = t[j].alunos[i].nascimento.mes;
          novo.nascimento.ano = t[j].alunos[i].nascimento.ano;
          copia_string(t[j].alunos[i].nome, novo.nome);
          copia_string(t[j].alunos[i].sobrenome, novo.sobrenome);
          mais_novo = 0;
        }
      }
    }
  return(novo);
}


Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
  Aluno velho;

  copia_string(t[0].alunos[0].nome, velho.nome);
  copia_string(t[0].alunos[0].sobrenome, velho.sobrenome);
  velho.nascimento.dia = t[0].alunos[0].nascimento.dia;
  velho.nascimento.mes = t[0].alunos[0].nascimento.mes;
  velho.nascimento.ano = t[0].alunos[0].nascimento.ano;

  //ver_turma(t, j);

  for(int j=0; j<qtd_turmas; j++){
    for(int i=0; i<t[j].qtd; i++){
      int mais_velho = 0;

      if (t[j].alunos[i].nascimento.ano < velho.nascimento.ano){ mais_velho = 1; }

      if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
          (t[j].alunos[i].nascimento.mes <  velho.nascimento.mes)){ mais_velho = 1; }

      if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
          (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
          (t[j].alunos[i].nascimento.dia <  velho.nascimento.dia)){ mais_velho = 1; }

      if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
          (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
          (t[j].alunos[i].nascimento.dia == velho.nascimento.dia) &&
          (compara_string(t[j].alunos[i].nome, velho.nome) < 0)){ mais_velho = 1; }

      if ((t[j].alunos[i].nascimento.ano == velho.nascimento.ano) &&
          (t[j].alunos[i].nascimento.mes == velho.nascimento.mes) &&
          (t[j].alunos[i].nascimento.dia == velho.nascimento.dia) &&
          (compara_string(t[j].alunos[i].nome, velho.nome) == 0) &&
          (compara_string(t[j].alunos[i].sobrenome, velho.sobrenome) < 0)){ mais_velho = 1; }

      if(mais_velho){
        velho.nascimento.dia = t[j].alunos[i].nascimento.dia;
        velho.nascimento.mes = t[j].alunos[i].nascimento.mes;
        velho.nascimento.ano = t[j].alunos[i].nascimento.ano;
        copia_string(t[j].alunos[i].nome, velho.nome);
        copia_string(t[j].alunos[i].sobrenome, velho.sobrenome);
        mais_velho = 0;
      }
    }
  }
  return(velho);
}


int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
  int num_alunos = 0;
  for(int j=0; j<qtd_turmas; j++){
    for(int i=0; i<t[j].qtd; i++){
      num_alunos += tem_substring(padrao, t[j].alunos[i].nome);
    }
  }
  return(num_alunos);
}

int add_aluno(Turma t[], Aluno A, int j){
  t[j].alunos[t[j].qtd] = A;
  t[j].qtd++;
  return(t[j].qtd);
}

int remove_aluno(Turma t[], int j){
  t[j].qtd -= 1;
  return(t[j].qtd);
}
