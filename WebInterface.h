#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//backend not implemented, need a tcp/udp socket library
typedef struct WIData {
	void* ptr;
	unsigned int size;
	/*IP
	 - when received, its the ip of sender
	 - when sender, the ip of client/receiver
	*/
	long ip;
	long socketUID;
} WIData;
WIData* WIData_new(void* ptr, unsigned int size, int ip, int uid);
char WIData_delete(WIData* self);
long ipv4Pack(char a, char b, char c, char d);
int ipv4Unpack(long ip, char* a, char* b, char* c, char* d);

typedef struct WIServer {
  int notImplementedYet;
} WIServer;
//a server can be called by multiple IPs, like 127.0.0.1(just for the same pc), 192.168.0.-(just PCs in same network), 240.-,-,-(internet), et cetera
WIServer* WIServer_new(long* ips, int nips, int port);
char WIServer_delete(WIServer* self);
long WIServer_getMyIP(WIServer* self);
int  WIServer_getMyPort(WIServer* self);
char WIServer_getPendingMsgs(WIServer* self, WIData*** msgs, int* n);
char WIServer_sendMsg(WIServer* self, WIData* msg);
char WIServer_closeConnection(WIServer* self, long uid);

typedef struct WISocket {
  int notImplementedYet;
} WISocket;
WISocket* WISocket_new(long ip, int port);
char WISocket_delete(WISocket* self);
char WISocket_getPendingMsgs(WISocket* self, WIData*** msgs, int* n);
char WISocket_sendMsg(WISocket* self, WIData* msg);
char WISocket_getStatus(WISocket* self);

long WI_getMyLocalIP();
#endif