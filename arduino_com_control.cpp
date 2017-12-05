#include "arduino_com_control.h"
#include "stdio.h"

//建立一个ComControl类的对象Com1
ComControl Com1;

void receive_com_data(ComControl& com)
{
	if (Serial1.available())   //若串口1接收到来自手机端发送过来的信息
	{
		if (com.end_flag)      //如果读取完成，则刷新串口1
			Serial1.flush();   
		char tmp = Serial1.read();   //每次从串口1读取一个字节的数据
		if (tmp == ':')        //读取到:字符，表示开始接收数据
		{
			com.start_flag = 1;
			com.end_flag = 0;
			com.len = 0;
			strcpy(com.buf, "\0");
			return;
		}

		if (com.start_flag)
		{
			if (tmp == '$')       //读取到$字符，说明到了字符串末尾，结束读取
			{
				com.end_flag = 1; //终止标识置1，表示读取完成
				com.buf[com.len] = '\0';
				return;
			}
			else
			{
				com.buf[com.len] = tmp;
				if (++com.len > 200)     //如果接收的字符串长度超过200，则清空，重新写入
				{
					com.start_flag = 0;
					com.end_flag = 0;
					com.len = 0;
					strcpy(com.buf, "\0");
					return;
				}
			}
		}
	}
}

