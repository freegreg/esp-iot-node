//////////////////////////////////////////////////
// Simple NTP client for ESP8266.
// Copyright 2015 Richard A Burton
// richardaburton@gmail.com
// See license.txt for license terms.
//////////////////////////////////////////////////

#include <c_types.h>
#include <user_interface.h>
#include <espconn.h>
#include <osapi.h>
#include <mem.h>
#include <time.h>
#include <esp8266.h>
#include <sntp.h>
#include "ntp.h"
#include "ets_sys.h"
#include "osapi.h"
//#include "user_interface.h"
//#include "driver/uart.h"
#include "mem.h"

// list of major public servers http://tf.nist.gov/tf-cgi/servers.cgi
// uint8 ntp_servers_ip[][4] = {
// 	{98, 175, 203, 200},
// 	{66, 199, 22, 67},
// 	{164, 113, 32, 5},
// 	{198, 111, 152,100},
// 	{129, 6, 15, 28},
// 	{129, 6, 15, 29},
// 	{129, 6, 15, 30}	
// };

// uint8 ntp_server_i = 0;
// uint8 *ntp_server = ntp_servers_ip[0]; // microsoft


// LOCAL os_timer_t sntp_timer;
// LOCAL uint32 ntp_retry_counter = 0;
// LOCAL void sntp_start(void);

// void ICACHE_FLASH_ATTR user_check_sntp_stamp(void *arg)
// {
//    uint32 current_stamp;
//    current_stamp = sntp_get_current_timestamp();
//    if(current_stamp == 0)
//    {
//       if(++ntp_retry_counter < 200)
//          os_timer_arm(&sntp_timer, 100, 0);
//       else
//       {
   
//         sntp_setservername(0, NULL);
//        	sntp_setservername(1, NULL);
//        	sntp_setserver(2, NULL);
//          sntp_stop();    // ??
//          os_printf("sleep...\n");
      
//          os_timer_disarm(&sntp_timer);
//          os_timer_setfn(&sntp_timer, (os_timer_func_t *)user_start_ntp, NULL);
//          os_timer_arm(&sntp_timer, 10*1000, 0);
//       }
//    }
//    else
//    {
//       os_printf("sntp: %d, %s \n", current_stamp, sntp_get_real_time(current_stamp));
//       sntp_stop();
//       os_timer_disarm(&sntp_timer);
//       os_timer_setfn(&sntp_timer, (os_timer_func_t *)user_start_ntp, NULL);
//       os_timer_arm(&sntp_timer, 10*1000, 0);
//    }
// }


// LOCAL void ICACHE_FLASH_ATTR
// sntp_start(void)
// {
//    os_printf("%s\n", __func__);
//    ip_addr_t *addr = (ip_addr_t *)os_zalloc(sizeof(ip_addr_t));
//    sntp_setservername(0, "us.pool.ntp.org"); // set server 0 by domain name
//    sntp_setservername(1, "ntp.sjtu.edu.cn"); // set server 1 by domain name
//    ipaddr_aton("210.72.145.44", addr);
//    sntp_setserver(2, addr); // set server 2 by IP address
//    sntp_init();
//    os_free(addr);
//    ntp_retry_counter = 0;
//    os_timer_setfn(&sntp_timer, (os_timer_func_t *)user_check_sntp_stamp, NULL);
//    os_timer_arm(&sntp_timer, 100, 0);
// }

// LOCAL void ICACHE_FLASH_ATTR
// user_ntp_checkip_cb(void)
// {
//    os_printf("%s\n", __func__);
//    os_timer_disarm(&sntp_timer);
//    if(wifi_station_get_connect_status() != STATION_GOT_IP)
//    {
//       os_timer_setfn(&sntp_timer, (os_timer_func_t *)user_ntp_checkip_cb, NULL);
//       os_timer_arm(&sntp_timer, 500, 0);
//    }
//    else
//    {
//       sntp_start();
//    }
// }

// void user_init2(void)
// {
//    uart_init(9600, 115200);
//    os_printf("SDK version:%s\n", system_get_sdk_version());
//    wifi_set_opmode(STATION_MODE); 
//    struct station_config sta_config;
//    os_memset(&sta_config, 0, sizeof(sta_config));
//    os_sprintf(sta_config.ssid, "%s", "WiFiTest");
//    os_sprintf(sta_config.password, "%s", "12345678");
//    wifi_station_set_config(&sta_config);
//    system_init_done_cb(sntp_start);
// }


