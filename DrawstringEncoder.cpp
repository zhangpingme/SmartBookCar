/*******************************************************************************
拉绳编码器，在


Date:    2017.08.01
Version: V1.0
*******************************************************************************/
#include "DrawstringEncoder.h"
volatile long count = 0;
int pinValue;

void DrawstringEncoder_init()
{
	pinMode(PinA, INPUT); //记得改成输入模式
	pinMode(PinB, INPUT);
	pinMode(PinA, INPUT_PULLUP);      //一定要加上拉电阻，否则没有脉冲
	pinMode(PinB, INPUT_PULLUP);      //一定要加上拉电阻，否则没有脉冲
	attachInterrupt(0, blink, RISING); //拉绳产生位移变化的时候，会在A相输出一个上升沿
	Serial.begin(9600);
}

void blink()
{
	pinValue = digitalRead(PinB);
	if (pinValue == HIGH)  //当A相产生上升沿脉冲的时候，B相为高电平，表示拉绳伸长，否则是缩短
	{
		count++;
	}
	else
	{
		count--;
	}
}

int ReadCount()
{
	return count;
}