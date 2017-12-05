#include "esp8266.h"
#include "Arduino.h"
#include "stdio.h"

void esp8266_init()       //ESP8266模块的初始化
{
	Serial1.begin(9600);  //串口1初始化波特率9600
	delay(100);
	//使ESP8266工作在AP模式，在这种模式下，ESP8266模块发出无线WiFi信号，可以用手机端连接这个信号
	Serial1.println("AT+CWMODE=2");
	delay(500);
	//重启模块，使之前的设置生效
	Serial1.println("AT+RST");
	delay(500);
	//启动多连接，即允许多个手机客户端连接（最多5个，每个客户端对应id值为0~4）。
	Serial1.println("AT+CIPMUX=1");
	delay(500);
	//使模块作为服务器，开启服务器模式，端口号8080。
	Serial1.println("AT+CIPSERVER=1,8080");
	delay(500);
	//手机客户端只要输入模块的IP地址和端口号，连接上模块产生的WiFi，就可以实现与模块的通信，进而实现与单片机的信息交互。
}

void esp8266_send(int id, char * pBuf)    //单片机的串口1向特定手机客户端（根据id值）发送字符串pBuf
{
	char buf[60];
	int len = strlen(pBuf);
	sprintf(buf, "AT+CIPSEND=%d,%d", id, len);
	Serial1.println(buf);
	Serial.print("Send::");
	Serial.println(buf);
	delay(100);
	Serial1.print(pBuf);
}
