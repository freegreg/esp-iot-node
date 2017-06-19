#ifndef NODE_H
#define NODE_H

void ICACHE_FLASH_ATTR initNode(void);
void ICACHE_FLASH_ATTR initHttpServer(void);
void ICACHE_FLASH_ATTR setState(int newState);
void ICACHE_FLASH_ATTR  mainStateScheduler(void);

typedef enum state_type_ {
	STATE_INIT,
	STATE_SERVER_AP,
	STATE_SERVER_STA,
	STATE_MQTT_CLIENT,
	STATE_MQTT_SERVER_STA,
	STATE_RESET
} state_type;


#endif