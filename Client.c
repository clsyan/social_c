#define _CRT_SECURE_NO_WARNINGS
#include "client.h"
#include "WebInterface.h"
#include "utils.h"
//need a thread API...
char running = 0;
char* msg_to_send = 0;
char runAsClient(long ip, char* user, char* password) {
  char* msg = malloc(5);
  memcpy(msg, "log&", 5+ strlen(user) + strlen(password));
  strcat(msg, user);
  strcat(msg, "&");
  strcat(msg, password);
  msg_to_send = msg;
  WISocket* socket = WISocket_new(ip, 1050);
  running = 1;
  //need start a thread to client_thread
  WIData** msgs;
  int nMsgs = 0;
  
  while (WISocket_getStatus(socket)) {
#ifdef _WIN32
    Sleep(5);
#else
    sleep(5);
#endif
    if (msg_to_send) {
      WISocket_sendMsg(socket, WIData_new(msg_to_send, strlen(msg_to_send), ip, 0));
      msg_to_send = 0;
    }
    WISocket_getPendingMsgs(socket, &msgs, &nMsgs);
    if (nMsgs) {
      for (int i = 0; i < nMsgs;i++) {
        printf("[received]%s\n", (char*)msgs[i]->ptr);
        WISocket_delete(msgs[i]);
      }
      free(msgs);
    }
  }
  running = 0;
  return 0;
}
char client_thread() {
  while (running) {
    msg_to_send = _getline();
  }
  printf("connection closed.\n");
  return 0;
}