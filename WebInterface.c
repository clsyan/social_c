#include "WebInterface.h"
//backend not implemented, need a tcp/udp socket library
#define OFFLINE_TEST
#ifndef OFFLINE_TEST
//...
#else
#define TEST_MSG(text) x=malloc(sizeof(text));memcpy(x,text,sizeof(text));x = (void*)WIData_new(x,sizeof(text),0,0)
WIServer* WIServer_new(long* ips, int nips, int port) {
  WIServer* n = (WIServer*)malloc(sizeof(WIServer));
  n->notImplementedYet = 1;
  return n;
}
char WIServer_delete(WIServer* self) {
  free(self);
  return 0;
}
long WIServer_getMyIP(WIServer* self) {
  return ipv4Pack(128, 0, 0, 1);
}
int  WIServer_getMyPort(WIServer* self) {
  return 1050;
}
char WIServer_getPendingMsgs(WIServer* self, WIData*** msgs, int* n) {
  if (self->notImplementedYet) {
    void* x = 0;
    (*msgs) = (WIData**)malloc(sizeof(WIData*)*3);
	TEST_MSG("reg&HelloWorldMachine&1234");
	(*msgs)[0] = (WIData*)x;
	TEST_MSG("HelloWorld, and you!");
	(*msgs)[1] = (WIData*)x;
	TEST_MSG("How are you?");
	(*msgs)[2] = (WIData*)x;
	self->notImplementedYet = 0;
	(*n) = 3;
  }
  else (*n) = 0;
  return 0;
}
char WIServer_sendMsg(WIServer* self, WIData* msg) { return 0; }
char WIServer_closeConnection(WIServer* self, long uid) { return 0; }
WISocket* WISocket_new(long ip, int port) {
  WISocket* n = (WISocket*)malloc(sizeof(WISocket));
  n->notImplementedYet = 1;
  return n;
}
char WISocket_delete(WISocket* self) {
	free(self);
	return 0;
}
char WISocket_getPendingMsgs(WISocket* self, WIData*** msgs, int* n) {
	if (self->notImplementedYet) {
		void* x = 0;
		(*msgs) = (WIData * *)malloc(sizeof(WIData*) * 3);
		TEST_MSG("new user: HelloWorldMachine");
		(*msgs)[0] = (WIData*)x;
		TEST_MSG("HelloWorldMachine: HelloWorld, and you!");
		(*msgs)[1] = (WIData*)x;
		TEST_MSG("HelloWorldMachine: How are you?");
		(*msgs)[2] = (WIData*)x;
		self->notImplementedYet = 0;
		(*n) = 3;
	} else (*n) = 0;
	return 0;
}
char WISocket_sendMsg(WISocket* self, WIData* msg) { return 0; }
char WISocket_getStatus(WISocket* self) { return 1; }
long WI_getMyLocalIP() { return 0; }//whitout socket library to get ip
#undef TEST_MSG
#endif

WIData* WIData_new(void* ptr, unsigned int size, int ip, int uid) {
	WIData* n = (WIData*)malloc(sizeof(WIData));
	n->ptr = ptr;
	n->size = size;
	n->ip = ip;
	n->socketUID = uid;
	return n;
}
char WIData_delete(WIData* self) {
	free(self->ptr);
	free(self);
	return 0;
}
long ipv4Pack(char a, char b, char c, char d) {
	return a * 256 * 256 * 256 + b * 256 * 256 + c * 256 + d;
}
int ipv4Unpack(long ip, char* a, char* b, char* c, char* d) {
	*d = ip % 256;
	*c = (ip / 256) % 256;
	*b = (ip / (256 * 256)) % 256;
	*a = (ip / (256 * 256 * 256)) % 256;
	return (ip / (256 * 256 * 256 * 256));//overflow
}