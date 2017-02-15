#ifndef IO_H
#define IO_H

void ICACHE_FLASH_ATTR ioLed(int ena);
void ICACHE_FLASH_ATTR ioToggleLed();

int ioGetLedState();
int ioGetButtonState();
int ioGetRelayState();

void ioSetRelayOn();
void ioSetRelayOff();

void ioSetLedOn();
void ioSetLedOff();

void ioInit(void);

#endif