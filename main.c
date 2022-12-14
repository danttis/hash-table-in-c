//Francisco Junior Peixoto Dantas
// Tabela de dispersão por encadeamento interior homogêneo
// Posições e valores nulos são tratados como -1
// Caso for usar no Windows descomentar a função pause() na linha 70

#include <stdio.h>
#include <time.h>
#include <locale.h>
//DEfinição de cores 
#define WHITE "\x1b[00m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m" 
#define BLUE "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[44m"
#define RESET "\x1B[0m"
//controles de tamanho e mod
#define TAM 10
#define m 6

typedef struct celula {
  int valor;
  int prox;
}
celula;
int mod(int);
void inserir(celula * x, int y);
void imprimir(celula * x);
int buscar(celula * x, int y);
void remover(celula * x, int y);
void pause();
int main(void) {
  setlocale (LC_ALL, "portuguese");
  celula x[TAM];
  int valor;
  for (int i = 0; i < TAM; i++) {
    x[i].valor = -1;
    x[i].prox = -1;
  }
  printf("Você deseja inserir os valores, ou usar padrão?\n 1 - Digitar | 2 - Usar padrão : ");
  scanf("%d", & valor);
  if (valor == 1) {
    for (int i = 0; i < TAM; i++) {
      printf("Digite o %dº valor: ", i + 1);
      scanf("%d", & valor);
      inserir(x, valor);
    }
    imprimir(x);
    printf("Digite um valor para busca-lo: ");
    scanf("%d", & valor);
    printf("\nBuscando a chave %d\nA chave está na posição: %d\n\n", valor, buscar(x, valor));
    printf("Digite um valor para remove-lo: ");
    scanf("%d", & valor);
    remover(x, valor);
    imprimir(x);
  } else {
    printf("\nInserindo valores de 5 a %d com função mod %d\n",TAM+5, m);
    for (int i = 5; i < TAM + 5; i++) {
      inserir(x, i);
    }
    imprimir(x);
    printf("\nBuscando a chave 12\nA chave está na posição: %d", buscar(x, 12));
    printf("\n\nRemovendo valor 12");
    remover(x, 12);
    imprimir(x);
    printf("\n\nBuscando a chave 12\nA chave está na posição: %d\n\n", buscar(x, 12));
  }

  //pause();
  return 0;
}
int mod(x) {
  return (x % m);
}
void inserir(celula * x, int y) {
  int n = mod(y);
  if (x[n].valor == -1) {
    x[n].valor = y; // se não der colisão
  } else if(x[n].valor != y){
    int q = TAM;
    while (x[q].valor != -1 ) {
      q--;
    }
    if (x[n].prox == -1) { //colisão simples 
      x[n].prox = q;
      x[q].valor = y;
      x[q].prox = -1;
    } else if (x[n].prox != -1) {
      int tmp = x[n].prox;
      while (x[tmp].prox != -1) {
        tmp = x[tmp].prox;
      }
      if(x[tmp].valor != y){
      x[tmp].prox = q;
      x[q].valor = y;
      x[q].prox = -1;
      }
    }
  }
}
void imprimir(celula * x) {
  #ifdef __linux__ // compilação condicional para mostrar cores 
  printf(CYAN "\n\nTabela de dispersão mod %d\n"
      RESET, m);
  for (int i = 0; i < TAM; i++) {
    printf(CYAN "%d : "
      RESET, i);
    switch (mod(x[i].valor == -1 ? i : x[i].valor)) {
    case 0:
      printf(RED " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    case 1:
      printf(YELLOW " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    case 2:
      printf(PURPLE " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    case 3:
      printf(BLUE " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    case 4:
      printf(WHITE " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    case 5:
      printf(GREEN " %d prox---> %d\n" RESET, x[i].valor, x[i].prox);
      break;
    }
  }
  printf(RESET "\nAs cores mostram a colisão e apontam a chave onde o valor se encontra.\n");
  #elif _WIN32
  printf("\n\nTabela de dispersão mod 6\n\n"
      );
   for (int i = 0; i < TAM; i++) {
     printf("%d : %d prox---> %d\n", i, x[i].valor, x[i].prox);
   }
  #endif
}
int buscar(celula * x, int y) {
  int n = mod(y);
  int loc = -1;
  if (x[n].valor == y) {
    loc = n;
  } else {
    int tmp = x[n].prox;
    while (tmp != -1) {
      if (x[tmp].valor == y) {
        loc = tmp;
      }
      tmp = x[tmp].prox;
    }
  }
  return (loc);
}
void remover(celula * x, int y) {
  int n = mod(y);
  if (x[n].valor == y) {
    x[n].valor = -1;
  } else {
    n = buscar(x, y);
    if (n != -1) {x[n].valor = -1;}
    else {printf("valor já não estava na tabela.");}
  }
}
void pause(){ 
#ifdef __linux__ 
system("read -p \"Pressione qualquer tecla para continuar…\" saindo");
#elif _WIN32
system("pause");
#endif
}