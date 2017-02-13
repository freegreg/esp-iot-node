
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */


#include <esp8266.h>


//ESP8266 PIN	FUNCTION	GPIO	CONNECTED TO
//9 – MTMS		GPIO		GPIO14	J1 Pin 5
//10 – MTDI		GPIO		GPIO12	Relay (HIGH to turn on)
//12 – MTCK		GPIO		GPIO13	LED (LOW to turn on)

#define LEDGPIO 13
#define BTNGPIO 0
#define RELAYGPIO 12

char ioGetLedState() 	{ return (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << LEDGPIO));}
char ioGetButtonState() { return !(GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << BTNGPIO));}
char ioGetRelayState() 	{ return (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << RELAYGPIO));}

void ioSetRelayOn() 	{gpio_output_set((1 << RELAYGPIO), 0, 0, 0);}
void ioSetRelayOff() 	{gpio_output_set(0, (1 << RELAYGPIO), 0, 0);}

void ioSetLedOn() 		{gpio_output_set(0, (1 << LEDGPIO), 0, 0);}
void ioSetLedOff() 		{gpio_output_set((1 << LEDGPIO), 0, 0, 0);}

static ETSTimer resetBtntimer;

void ICACHE_FLASH_ATTR ioLed(int ena) {
	//gpio_output_set is overkill. ToDo: use better mactos
	if (ena) {
		gpio_output_set((1 << LEDGPIO), 0, (1 << LEDGPIO), 0);
	} else {
		gpio_output_set(0, (1 << LEDGPIO), (1 << LEDGPIO), 0);
	}
}

static void ICACHE_FLASH_ATTR resetBtnTimerCb(void *arg) {
	static int resetCnt = 0;
	if (!GPIO_INPUT_GET(BTNGPIO)) {
		resetCnt++;
	} else {
		if (resetCnt >= 6) { //3 sec pressed
			wifi_station_disconnect();
			wifi_set_opmode(0x3); //reset to AP+STA mode
			os_printf("Reset to AP mode. Restarting system...\n");
			system_restart();
		}
		resetCnt = 0;
	}
}

void ICACHE_FLASH_ATTR ioToggleLed() {
	//Do blinky stuff
	if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << LEDGPIO))
	{
		// set gpio low
		gpio_output_set(0, (1 << LEDGPIO), 0, 0);
	}
	else
	{
		// set gpio high
		gpio_output_set((1 << LEDGPIO), 0, 0, 0);
	}
}

void ioInit() {
	// configure UART TXD to be GPIO1, set as output
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);

	gpio_output_set(0, 0, (1 << LEDGPIO) | (1 << RELAYGPIO), (1 << BTNGPIO));
	gpio_output_set((1 << LEDGPIO), 0, 0, 0);
	gpio_output_set(0, (1 << RELAYGPIO), 0, 0);

	os_timer_disarm(&resetBtntimer);
	os_timer_setfn(&resetBtntimer, resetBtnTimerCb, NULL);
	os_timer_arm(&resetBtntimer, 500, 1);
}

