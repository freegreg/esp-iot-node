/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */

/*
This is example code for the esphttpd library. It's a small-ish demo showing off 
the server, including WiFi connection management capabilities, some IO and
some pictures of cats.
*/

#include <esp8266.h>
#include "httpd.h"
#include "io.h"
#include "httpdespfs.h"
#include "cgi.h"
#include "cgiwifi.h"
#include "cgiflash.h"
#include "stdout.h"
#include "auth.h"
#include "espfs.h"
#include "captdns.h"
#include "webpages-espfs.h"

#include "node.h"
#include "cgi-test.h"
//#include "ntp.h"



//static void ICACHE_FLASH_ATTR timerTestFunction(void *arg);

//static ETSTimer prMainTimer;

//Main routine. Initialize stdout, the I/O, filesystem and the webserver and we're done.
void user_init(void) {

	//basic init 
	stdoutInit();
	ioInit();

	initNode();

 //  	os_timer_disarm(&prMainTimer);
	// os_timer_setfn(&prMainTimer, timerTestFunction, NULL);
	// os_timer_arm(&prMainTimer, 1000, 1);

}

void user_rf_pre_init() {
	//Not needed, but some SDK versions want this defined.
}

// static void ICACHE_FLASH_ATTR timerTestFunction(void *arg)
// {	
// 	static uint32 t = 0;

// 	os_printf("test %d\n", t);
// 		#define PRIV_PARAM_START_SEC        0x3E
// 	#define PRIV_PARAM_SAVE     0
// 	uint32 to_write = t;

// 	SpiFlashOpResult result;
// 	spi_flash_erase_sector(0x3E);
//     result = spi_flash_write((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE, &to_write, 4);
//     os_printf("result of writing: %d\r\n", result);
//     uint8 *addr2 = (uint8	*)&to_write;
//     os_printf("write 0x3E sec:%02x%02x%02x%02x\r\n",	addr2[0],	addr2[1],	addr2[2],	addr2[3]);
// 	uint32	value;

// 	uint8 *addr	= (uint8	*)&value;
//     result = spi_flash_read((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE,	(uint32	*)addr,	4);
//     os_printf("result of reading: %d\r\n", result);
// 	os_printf("read 0x3E sec:%02x%02x%02x%02x\r\n",	addr[0],	addr[1],	addr[2],	addr[3]);
// 	t++;

// }