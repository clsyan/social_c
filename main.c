#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "Client.h"
#include "Server.h"


typedef struct User{
  char nome[50];
  char senha[50];
  long ip;
  //int id;
  //int nAmigos;
  //struct User* prox;
  //struct User* ant;
}User;
//------------------ASSINATURAS--------------------//
char login(User* ver/*, User* inicio*/);
//void verLogin(User* ver, User* inicio);
char menu(/*User* perfil, User* inicio*/);
//-------------------------------------------------//

int main(void) {
  //User*inicio = malloc(sizeof(User));
  /*Userver = malloc(sizeof(User));
  login(ver, inicio);*/
  menu();
  return 0;
}
char login(User* ver/*, User* inicio*/){
  printf("bem vindo! digite seu username: ");
  scanf("%s", ver->nome);
  printf("digite sua senha: ");
  scanf("%s", ver->senha);
  printf("insert server ip as long:");
  scanf("%ld", &ver->ip);
  //verLogin(ver, inicio);
  return 0;
}
/*void verLogin(User *ver, User *inicio){
  User* atual = inicio;
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
}*/
char menu() {
  for (;;) {
    printf("Start app as a:\n 1 - Server\n 2 - Client\n 3 - Close\ninsert a valid number:");
    char* temp = _getline();
	char* input = str_sub(temp, 0, strlen(temp) - 1);
	free(temp);
	if (strcmp(input, "1")==0) {
		User* _login = malloc(sizeof(User));
		login(_login);
		runAsClient(_login->ip, _login->nome, _login->senha);
	}
	else if (strcmp(input, "2")==0) {
		runAsServer();
	}
	else if (strcmp(input, "3")==0) {
		break;
	}
	else printf("Invalid input (%s)...\n", input);
  }
  return 0;
}