/*******************************************************************************
采用脉冲式的拉绳编码器，拉绳每伸缩一个单位的距离，编码器输出一个脉冲。传感器的基
座安装在外箱底部，线头安装在内箱底部，初始时输出值为0，随内箱上升，编码器的输出脉
冲数不断增多，用来判断内箱相对于外箱的位置，主要在内箱上升到第二层去接书的时候用到。
*******************************************************************************/
#include "DrawstringEncoder.h"
volatile long count = 0;   //用来计算脉冲数
int pinValue;              //用来判断B相的电平状态

void DrawstringEncoder_init()
{
	pinMode(PinA, INPUT);             //记得改成输入模式
	pinMode(PinB, INPUT);
	pinMode(PinA, INPUT_PULLUP);      //一定要加上拉电阻，否则没有脉冲
	pinMode(PinB, INPUT_PULLUP);      //一定要加上拉电阻，否则没有脉冲
	attachInterrupt(0, blink, RISING); //拉绳产生位移变化的时候，会在A相输出一个上升沿
	//外部中断函数，中断源0，触发信号是上升沿，中断处理函数为blink()，中断模式为上升沿中断。
	//在Arduino中，中断源0对应的引脚为2号引脚，中断源1对应的引脚为3号引脚。
}

void blink()
{
	pinValue = digitalRead(PinB);
	if (pinValue == HIGH)  //当A相产生上升沿脉冲的时候，B相为高电平，表示拉绳伸长，否则是缩短
		count++;           //累计脉冲个数
	else
		count--;
}

int ReadCount()            //返回读取到的脉冲数，用以判断内箱上升的距离。
{
	return count;
}