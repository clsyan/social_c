#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include "WebInterface.h"
#include "utils.h"
#define CLIENTMAX 64

char processMsg(WIData* x);

typedef struct SClient {
  char* name;
  char* pass;
  long ip;
  long uidsocket;
} SClient;
SClient* SClient_new(char* name, char* pass, long ip, long uidsocket) {
  SClient* n = malloc(sizeof(SClient));
  n->name = name;
  n->pass = pass;
  n->ip = ip;
  n->uidsocket = uidsocket;
  return n;
}
char SClient_delete(SClient* self) {
  free(self);
  return 0;
}

WIServer* serv = 0;
SClient** clients = 0;
char runAsServer() {
  WIData** msgs;
  int nMsgs = 0;
  printf("Running as Server...\n");
  long ip = WI_getMyLocalIP();
  serv = WIServer_new(&ip, 1, 1050);
  clients = (SClient**)malloc(sizeof(void*) * CLIENTMAX);
  //i believe that is enough :D
  memset(clients, 0, sizeof(void*) * CLIENTMAX);
  //zeromem
  for (;;) {
    WIServer_getPendingMsgs(serv, &msgs, &nMsgs);
    if (nMsgs) {
      for (int i = 0; i < nMsgs; i++) {
        printf("[received]%s\n", (const char*)msgs[i]->ptr);
        processMsg(msgs[i]);
        WISocket_delete(msgs[i]);
      }
      free(msgs);
    }
  }
  return 0;
}
int getSClientID(long ip,long uid) {
  for (int i = 0; i < CLIENTMAX; i++) {
    if (clients[i]&&clients[i]->ip==ip&&clients[i]->uidsocket==uid)
      return i;
  }
  return -1;
}
int addSClient(SClient* client) {
  for (int i = 0; i < CLIENTMAX; i++) {
    if (clients[i]==0) {
      clients[i]= client;
	  return i;
    }
  }
  return 0;//bug of milenium
}
char sendAllClients(char* text, int clientidException) {
  for (int i = 0; i < CLIENTMAX; i++) {
    if (i!= clientidException &&clients[i]) {
		WIServer_sendMsg(serv, WIData_new(text, strlen(text) + 1, clients[i]->ip, clients[i]->uidsocket));
    }
  }
  return 0;
}
char processMsg(WIData* x) {
  int id = getSClientID(x->ip,x->socketUID);
  if (id<0) {
    if (x->ptr==0){
      WIServer_closeConnection(serv,x->socketUID);
      return 0;
    }
    char* text = (char*)x->ptr;
    if (strlen(text) > 5&&strcmp(str_sub(text,0,4),"log&")==0) {
      int sp = str_indexof(text, '&', 4);
      if (sp > 6) {
        char* name = str_sub(text, 4,sp);
        char* pass = str_sub(text, sp, -1);
        id=addSClient(SClient_new(name, pass, x->ip, x->socketUID));
        printf("$SERVE$ new user %s with password %s\n", (const char*)name, (const char*)pass);
        int len = strlen(name);
        char* msg = malloc(len + 6 + 1);
        msg[len] = 0;
        memcpy(msg, name, len);
        strcat(msg, " loged");
        sendAllClients(msg,id);
      }
    }
    if (id<0){
      WIServer_closeConnection(serv,x->socketUID);
      return 0;
    }
  } else {
    if (x->ptr==0){
      WIServer_closeConnection(serv,x->socketUID);
	  clients[id] = 0;
	  return 0;
	} else {
      //need a filter to identify /private /invite /accept...
      int len = strlen(clients[id]->name);
      char* msg = malloc(len + 1);
      msg[len] = 0;
      memcpy(msg, clients[id]->name, len+2+strlen(x->ptr)+1);
      strcat(msg, ": ");
	  strcat(msg, x->ptr);
      sendAllClients(msg, id);
	}
  }
}
