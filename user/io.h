#ifndef IO_H
#define IO_H

void ICACHE_FLASH_ATTR ioLed(int ena);
void ICACHE_FLASH_ATTR ioToggleLed();
void ICACHE_FLASH_ATTR ioToggleLed();

char ioGetLedState();
char ioGetButtonState();
char ioGetRelayState();

void ioSetRelayOn();
void ioSetRelayOff();

void ioSetLedOn();
void ioSetLedOff();

void ioInit(void);

#endif