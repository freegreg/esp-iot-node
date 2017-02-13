#ifndef CGI_H
#define CGI_H

#include "httpd.h"

int cgiLed(HttpdConnData *connData);
int tplLed(HttpdConnData *connData, char *token, void **arg);
int tplCounter(HttpdConnData *connData, char *token, void **arg);

int ICACHE_FLASH_ATTR cgiRelayToggle(HttpdConnData *connData);
int ICACHE_FLASH_ATTR cgiUpdateRelay(HttpdConnData *connData);

#endif