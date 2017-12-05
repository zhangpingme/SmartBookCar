#ifndef ESP_8266
#define ESP_8266
#include "stdint.h"
void esp8266_init();
void esp8266_send(int id,char * pBuf);
#endif // !ESP_8266
