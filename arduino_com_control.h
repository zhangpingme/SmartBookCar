#ifndef ARDUINO_COM_CONTROL_H
#define ARDUINO_COM_CONTROL_H
#include "Arduino.h"

typedef struct
{
	//定义一个结构体类型，用于封装手机客户端和单片机串口之间传输的数据
	bool start_flag;     //起始标识，值为true表示可以读取，即读取中
	bool end_flag ;      //终止标识，值为true表示读取完成，false表示读取中
	int len;             //传输数据的字符串长度
	char buf[200];       //传输数据的字符串
}ComControl;

void receive_com_data(ComControl& com);
#endif 
