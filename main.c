#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Usuario{
  char nome[50];
  char senha[50];
  int id;
  int nAmigos;
  struct Usuario *prox;
  struct Usuario *ant;
}usuario;
//------------------ASSINATURAS--------------------//
void login(usuario *ver, usuario *inicio);
void verLogin(usuario *ver, usuario *inicio);
void menu(usuario *perfil, usuario *inicio);
//-------------------------------------------------//

int main(void) {
  usuario *inicio = malloc(sizeof(usuario));
  usuario *ver = malloc(sizeof(usuario));
  login(ver, inicio);
  return 0;
}
void login(usuario *ver, usuario *inicio){
  printf("bem vindo! digite seu username: ");
  scanf("%s", ver->nome);
  printf("\ndigite sua senha: ");
  scanf("%s", ver->senha);
  verLogin(ver, inicio);
}
void verLogin(usuario *ver, usuario *inicio){
  usuario *atual = inicio;
  if(strcmp(ver->nome, atual->nome) == 0 && strcmp(ver->senha, atual->senha) == 0){
    menu(atual, inicio);
  }
  else if(atual == NULL){
    printf("dados incorretos\n");
    login(NULL, inicio);
  }
  else{
    atual = atual->prox;
  }
}
void menu(){

}