/*
	Tracking����ѭ������Ҫ���ú��⴫�������ڰ��ߣ������⵽���ߣ��򷵻ظߵ�ƽ�������ǵ͵�ƽ��ע��Ҫ����ÿ������ģ�����ֵ
*/

#include "Tracking.h"

void Track_init()
{
	pinMode(hongwai_1, INPUT);
	pinMode(hongwai_1,INPUT_PULLUP);
	pinMode(hongwai_2, INPUT);
	pinMode(hongwai_2, INPUT_PULLUP);
	pinMode(hongwai_3, INPUT);
	pinMode(hongwai_3, INPUT_PULLUP);
}

void Track_forward()
{
	if (digitalRead(hongwai_1) == 1)
		go_straight();
	else if (digitalRead(hongwai_1) == 0 && digitalRead(hongwai_2) == 1)
		big_right();
	else if (digitalRead(hongwai_1) == 0 && digitalRead(hongwai_3) == 1)
		big_left();
	else
		go_straight();//Ӧ��ͣ��
	delay(200);
		
}