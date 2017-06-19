// #include "cgiwebsocket.h"
// //static ETSTimer websockTimer;

// //Broadcast the uptime in seconds every second over connected websockets
// static void ICACHE_FLASH_ATTR websockTimerCb(void *arg) {
// 	static int ctr=0;
// 	char buff[128];
// 	ctr++;
// 	os_sprintf(buff, "Up for %d minutes %d seconds!\n", ctr/60, ctr%60);
// 	cgiWebsockBroadcast("/websocket/ws.cgi", buff, os_strlen(buff), WEBSOCK_FLAG_NONE);

// }

// //On reception of a message, send "You sent: " plus whatever the other side sent
// void myWebsocketRecv(Websock *ws, char *data, int len, int flags) {
// 	int i;
// 	char buff[128];
// 	os_sprintf(buff, "You sent: ");
// 	for (i=0; i<len; i++) buff[i+10]=data[i];
// 	buff[i+10]=0;
// 	cgiWebsocketSend(ws, buff, os_strlen(buff), WEBSOCK_FLAG_NONE);
// }

// //Websocket connected. Install reception handler and send welcome message.
// void myWebsocketConnect(Websock *ws) {
// 	ws->recvCb=myWebsocketRecv;
// 	cgiWebsocketSend(ws, "Hi, Websocket!", 14, WEBSOCK_FLAG_NONE);
// }

// //On reception of a message, echo it back verbatim
// void myEchoWebsocketRecv(Websock *ws, char *data, int len, int flags) {
// 	os_printf("EchoWs: echo, len=%d\n", len);
// 	cgiWebsocketSend(ws, data, len, flags);
// }

// //Echo websocket connected. Install reception handler.
// void myEchoWebsocketConnect(Websock *ws) {
// 	os_printf("EchoWs: connect\n");
// 	ws->recvCb=myEchoWebsocketRecv;
// }
