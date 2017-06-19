//#include "mqtt.h"
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

#include "mqtt/mqtt_control.h"
#include "cgi-test.h"
#include "ntp.h"
#include "node.h"


//The example can print out the heap use every 3 seconds. You can use this to catch memory leaks.
//#define SHOW_HEAP_USE

//Function that tells the authentication system what users/passwords live on the system.
//This is disabled in the default build; if you want to try it, enable the authBasic line in
//the builtInUrls below.
int myPassFn(HttpdConnData *connData, int no, char *user, int userLen, char *pass, int passLen) {
	if (no==0) {
		os_strcpy(user, "admin");
		os_strcpy(pass, "the8time");
		return 1;
//Add more users this way. Check against incrementing no for each user added.
//	} else if (no==1) {
//		os_strcpy(user, "user1");
//		os_strcpy(pass, "something");
//		return 1;
	}
	return 0;
}

#ifdef ESPFS_POS
CgiUploadFlashDef uploadParams={
	.type=CGIFLASH_TYPE_ESPFS,
	.fw1Pos=ESPFS_POS,
	.fw2Pos=0,
	.fwSize=ESPFS_SIZE,
};
#define INCLUDE_FLASH_FNS
#endif
#ifdef OTA_FLASH_SIZE_K
CgiUploadFlashDef uploadParams={
	.type=CGIFLASH_TYPE_FW,
	.fw1Pos=0x1000,
	.fw2Pos=((OTA_FLASH_SIZE_K*1024)/2)+0x1000,
	.fwSize=((OTA_FLASH_SIZE_K*1024)/2)-0x1000,
	.tagName=OTA_TAGNAME
};
#define INCLUDE_FLASH_FNS
#endif

#ifdef SHOW_HEAP_USE
static ETSTimer prHeapTimer;

static void ICACHE_FLASH_ATTR prHeapTimerCb(void *arg) {
	os_printf("Heap: %ld\n", (unsigned long)system_get_free_heap_size());
}
#endif

/*
This is the main url->function dispatching data struct.
In short, it's a struct with various URLs plus their handlers. The handlers can
be 'standard' CGI functions you wrote, or 'special' CGIs requiring an argument.
They can also be auth-functions. An asterisk will match any url starting with
everything before the asterisks; "*" matches everything. The list will be
handled top-down, so make sure to put more specific rules above the more
general ones. Authorization things (like authBasic) act as a 'barrier' and
should be placed above the URLs they protect.
*/
HttpdBuiltInUrl builtInUrls[]={
	{"*", cgiRedirectApClientToHostname, "esp8266.nonet"},
	{"/", cgiRedirect, "/index.html"},
	{"/relayToggle", cgiRelayToggle, NULL},
	{"/updateRelay", cgiUpdateRelay, NULL},
#ifdef INCLUDE_FLASH_FNS
	{"/flash/next", cgiGetFirmwareNext, &uploadParams},
	{"/flash/upload", cgiUploadFirmware, &uploadParams},
#endif
	{"/flash/reboot", cgiRebootFirmware, NULL},

	//Routines to make the /wifi URL and everything beneath it work.

//Enable the line below to protect the WiFi configuration with an username/password combo.
	{"/wifi/*", authBasic, myPassFn},

	{"/wifi", cgiRedirect, "/wifi/wifi.tpl"},
	{"/wifi/", cgiRedirect, "/wifi/wifi.tpl"},
	{"/wifi/wifiscan.cgi", cgiWiFiScan, NULL},
	{"/wifi/wifi.tpl", cgiEspFsTemplate, tplWlan},
	{"/wifi/connect.cgi", cgiWiFiConnect, NULL},
	{"/wifi/connstatus.cgi", cgiWiFiConnStatus, NULL},
	{"/wifi/setmode.cgi", cgiWiFiSetMode, NULL},

	{"*", cgiEspFsHook, NULL}, //Catch-all cgi function for the filesystem
	{NULL, NULL, NULL}
};


volatile state_type state = STATE_INIT;
static ETSTimer WiFiLinker;
uint16 numberOfTries = 0;
#define MAX_TRIES 5

void ICACHE_FLASH_ATTR initNode(void){

	mqtt_init();
	//try station mode
	//wifi_set_opmode(STATION_MODE); 
	//system_init_done_cb(mainStateScheduler);
	//get default config 
#ifdef USER_DEBUG
	struct station_config default_station_config;

	wifi_station_get_config_default(&default_station_config);
	
	os_printf("Default Station WiFi SSID: %s\n", default_station_config.ssid);
	os_printf("Default Station WiFi Password: %s\n", default_station_config.password);

	struct softap_config default_softap_config;
	wifi_softap_get_config_default(&default_softap_config);

	os_printf("Default SoftAP WiFi SSID: %s\n", default_softap_config.ssid);
	os_printf("Default SoftAP WiFi Password: %s\n", default_softap_config.password);
#endif
	//trying to join preconfigured wifi network as client - set station mode


	//struct station_config sta_config;
   //os_memset(&sta_config, 0, sizeof(sta_config));
   //os_sprintf(sta_config.ssid, "%s", "WiFiTest");
   //os_sprintf(sta_config.password, "%s", "12345678");
   //wifi_station_set_config(&sta_config);
   
	//os_timer_disarm(&prMainTimer);
	//os_timer_setfn(&prMainTimer, ntp_get_time, NULL);
	//os_timer_arm(&prMainTimer, 1000, 1);
}




//wifi_station_disconnect();
//wifi_set_opmode(0x3); //reset to AP+STA mode
//os_printf("Reset to AP mode. Restarting system...\n");
//system_restart();

void ICACHE_FLASH_ATTR  mainStateScheduler(void){

	os_timer_disarm(&WiFiLinker);
	struct ip_info ipConfig;
	static uint8_t wifiStatus = STATION_IDLE;
  	wifi_get_ip_info(STATION_IF, &ipConfig);

	

	if (wifiStatus == STATION_GOT_IP && ipConfig.ip.addr != 0){
		//node conected to AP
		//starting Server
		initHttpServer();
		// os_timer_setfn(&WiFiLinker, (os_timer_func_t *)nodeCheckState, NULL);
  //   	os_timer_arm(&WiFiLinker, 200, 0);
	}
	else{
		
	}
	// switch(state){
	// 	case STATE_INIT:
	// 		//stateInit();
 //  			if (wifiStatus == STATION_GOT_IP && ipConfig.ip.addr != 0)
 //  			{
 //    			setState(STATE_SERVER_STA);
 //  			}
 //  			else{	
 //  				setState(STATE_SERVER_AP);
 //  			}
 //  			  os_timer_setfn(&WiFiLinker, (os_timer_func_t *)nodeCheckState, NULL);
 //    		  os_timer_arm(&WiFiLinker, 200, 0);
	// 		break;
	// 	case STATE_SERVER_AP:
	// 		initHttpServer();


	// 		break;
	// 	case STATE_SERVER_STA:
	// 		initHttpServer();

	// 		break;
	// 	case STATE_MQTT_CLIENT:
	// 		//mqqt init
	// 		break;
	// 	case STATE_RESET:
	// 		wifi_station_disconnect();
	// 		wifi_set_opmode(STATION_MODE); //reset to AP+STA mode
	// 		os_printf("Restarting system...\n");
	// 		system_restart();
	// 		break;
	// 	default:
	// 		state = STATE_INIT;
	// 		break;
	// 	}
}

void ICACHE_FLASH_ATTR setState(int newState){

	state = newState;
}

void ICACHE_FLASH_ATTR initHttpServer(void){
	// 0x40200000 is the base address for spi flash memory mapping, ESPFS_POS is the position
	// where image is written in flash that is defined in Makefile.
	#ifdef ESPFS_POS
		espFsInit((void*)(0x40200000 + ESPFS_POS));
	#else
		espFsInit((void*)(webpages_espfs_start));
	#endif
	//http server init
	httpdInit(builtInUrls, 80);
	captdnsInit();
}

void ICACHE_FLASH_ATTR  stateInit(void){
	//wait for server mqtt


	// os_printf("\nReady\n");

	// //get default config 

	// struct station_config default_station_config;

	// wifi_station_get_config_default(&default_station_config);
		

	// os_printf("Default Station WiFi SSID: %s\n", default_station_config.ssid);
	// os_printf("Default Station WiFi Password: %s\n", default_station_config.password);

	// struct softap_config default_softap_config;
	// wifi_softap_get_config_default(&default_softap_config);

	// os_printf("Default SoftAP WiFi SSID: %s\n", default_softap_config.ssid);
	// os_printf("Default SoftAP WiFi Password: %s\n", default_softap_config.password);
}