// Sistema para gerenciamento de estoque de grãos

// Bibliotecas
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados (Silo)
typedef struct silo {
  char localizacao[255];
  char tipoGrao[255];
  int capacidade;
  int quantidade;
} Silo;

// Array de silos (dinâmico)
Silo *silos;

// Variáveis globais
int qtdSilos = 0;

// Função para cadastrar silo
int cadastrarSilo() {
  // Variaveis
  int capacidade, quantidade;
  char localizacao[255], tipoGrao[255];

  // Lendo dados do silo
  printf("Localização: ");
  scanf("%s", localizacao);
  printf("Tipo de grão: ");
  scanf("%s", tipoGrao);
  printf("Capacidade: ");
  scanf("%d", &capacidade);
  printf("Quantidade: ");
  scanf("%d", &quantidade);

  // Checa se a quantidade é maior que a capacidade
  if (quantidade > capacidade) {
    printf("Quantidade maior que a capacidade do silo! Tente novamente.");
    return 0;
  }

  // Checa se o silo já existe
  for (int i = 0; i < qtdSilos; i++) {
    if (strcmp(silos[i].localizacao, localizacao) == 0) {
      printf("Silo já cadastrado! Tente novamente.");
      return 0;
    }
  }

  // Alocando memória para o novo silo
  silos = (Silo *)realloc(silos, (qtdSilos + 1) * sizeof(Silo));

  // Atribuindo dados ao silo
  strcpy(silos[qtdSilos].localizacao, localizacao);
  strcpy(silos[qtdSilos].tipoGrao, tipoGrao);
  silos[qtdSilos].capacidade = capacidade;
  silos[qtdSilos].quantidade = quantidade;

  // Incrementando quantidade de silos
  qtdSilos++;

  // Retornando sucesso
  printf("Silo cadastrado com sucesso!");

  return 0;
}

// Remover silo
int removerSilo() {
  // Variáveis
  int i;
  char localizacao[255];

  // Lendo id do silo
  printf("Localizacao do silo: ");
  scanf("%s", localizacao);

  // Percorrendo silos
  for (i = 0; i < qtdSilos; i++) {
    // Verificando se o silo existe
    if (strcmp(silos[i].localizacao, localizacao) == 0) {
      
      // Remover o silo
      for (int j = i; j < qtdSilos; j++) {
        silos[j] = silos[j + 1]; // Copiando o próximo silo para o atual
        // exemplo : 
        // 4 silos, remover o silo 2
        // silos[2] = silos[3]
        // silos[3] = silos[4]
        // removido!
      }

      // Realocar memoria
      silos = (Silo *)realloc(silos, qtdSilos * sizeof(Silo));
      // Retornando sucesso
      printf("Silo removido com sucesso!");
      return 0;
    }
  }

  // Silo não encontrado
  printf("Silo não encontrado!");
  return 1;
}

// Editar silo
int editarSilo() {
  // Variáveis
  int i, capacidade, quantidade;
  char localizacao[255], tipoGrao[255];

  // Lendo id do silo
  printf("Localizacao do silo: ");
  scanf("%s", localizacao);

  // Percorrendo silos
  for (i = 0; i < qtdSilos; i++) {
    // Verificando se o silo existe
    if (strcmp(silos[i].localizacao, localizacao) == 0) {
      // Lendo dados do silo
      printf("Localização: ");
      scanf("%s", localizacao);
      printf("Tipo de grão: ");
      scanf("%s", tipoGrao);
      printf("Capacidade: ");
      scanf("%d", &capacidade);
      printf("Quantidade: ");
      scanf("%d", &quantidade);

      // Atribuindo dados ao silo
      strcpy(silos[i].localizacao, localizacao);
      strcpy(silos[i].tipoGrao, tipoGrao);
      silos[i].capacidade = capacidade;
      silos[i].quantidade = quantidade;

      // Retornando sucesso
      printf("Silo editado com sucesso!");
      return 0;
    }
  }

  // Silo não encontrado
  printf("Silo não encontrado!");
  return 1;
}

// Função para listar silos
int listarSilos() {
  // Variáveis
  int i;

  // Percorrendo silos
  for (i = 0; i < qtdSilos; i++) {
    // Imprimindo dados do silo
    printf("Silo: %d | Localização: %s | Tipo de grão: %s | Capacidade: %d | Quantidade: "
           "%d |",
           (i+1), silos[i].localizacao, silos[i].tipoGrao, silos[i].capacidade,
           silos[i].quantidade);
  }
  return 0;
}

// Função para adicionar grãos
int adicionarGrao() {

  // Variáveis
  int i, quantidade;
  char localizacao[255];

  // Lendo id do silo
  printf("Localizacao do silo: ");
  scanf("%s", localizacao);

  // Percorrendo silos
  for (i = 0; i < qtdSilos; i++) {
    // Verificando se o silo existe
    if (strcmp(silos[i].localizacao, localizacao) == 0) {
      // Lendo quantidade de grãos
      printf("Quantidade de grãos: ");
      scanf("%d", &quantidade);

      // Verificando se a quantidade é válida
      if (quantidade > 0) {
        // Verificando se a quantidade cabe no silo
        if (quantidade + silos[i].quantidade <= silos[i].capacidade) {
          // Adicionando grãos
          silos[i].quantidade += quantidade;
          // Retornando sucesso
          printf("Grãos adicionados com sucesso!");
          return 0;
        } else {
          // Retornando erro
          printf("Quantidade de grãos excede a capacidade do silo!");
          return 0;
        }
      } else {
        // Retornando erro
        printf("Quantidade de grãos inválida!");
        return 0;
      }
    }
  }
}

// Função para remover grãos
int removerGrao() {

  // Variáveis
  int i, quantidade;
  char localizacao[255];

  // Lendo id do silo
  printf("Localizacao do silo: ");
  scanf("%s", localizacao);

  // Percorrendo silos
  for (i = 0; i < qtdSilos; i++) {
    // Verificando se o silo existe
    if (strcmp(silos[i].localizacao, localizacao) == 0) {
      // Lendo quantidade de grãos
      printf("Quantidade de grãos: ");
      scanf("%d", &quantidade);

      // Verificando se após a remoção a quantidade é válida
      if (silos[i].quantidade - quantidade >= 0) {
        // Removendo grãos
        silos[i].quantidade -= quantidade;
        // Retornando sucesso
        printf("Grãos removidos com sucesso!");
        return 0;
      } else {
        // Retornando erro
        printf("Quantidade de grãos inválida!");
        return 0;
      }
    }
  }
}

// Função principal
int main() {
  // Variáveis
  int opcao;

  // Loop infinito
  while (1) {
    // Menu de opções
    printf("\n \nO que deseja fazer? \n");
    printf("1 - Criar novo silo \n");
    printf("2 - Remover silo \n");
    printf("3 - Editar silo \n");
    printf("4 - Listar silos \n");
    printf("5 - Adicionar grãos \n");
    printf("6 - Remover grãos \n");
    printf("7 - Sair \n");

    // Lendo opção
    scanf("%d", &opcao);

    // Verificando opção
    switch (opcao) {
    case 1:
      cadastrarSilo();
      break;
    case 2:
      removerSilo();
      break;
    case 3:
      editarSilo();
      break;
    case 4:
      listarSilos();
      break;
    case 5:
      adicionarGrao();
      break;
    case 6:
      removerGrao();
      break;
    case 7:
      printf("Saindo...");
      return 0;
    default:
      printf("Opção inválida!");
    }
  }
}