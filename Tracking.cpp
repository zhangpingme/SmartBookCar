/*
	Tracking用于循迹，主要是用红外传感器检测黑白线，如果检测到黑线，则返回高电平，否则是低电平，注意要调节每个红外模块的阈值
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
		go_straight();//应该停车
	delay(200);
		
}