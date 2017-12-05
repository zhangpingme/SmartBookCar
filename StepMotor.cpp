/*******************************************************************************
	步进电机一共有4个，编号为1~4，由Mega2560提供脉冲信号和方向信号，由24V直流电源通过转换
	为12V来供电，作用于推书杆主动滑块上和拨书杆主动滑块上，每个步进电机通过一个A4988模块进行驱动。
	1号步进电机——————内箱第一层，推书机构
	2号步进电机——————内箱第一层，压书机构
	3号步进电机——————内箱第二层，推书机构
	4号步进电机——————内箱第二层，压书机构

	A4988的其他连线：
	VDD--------------------------+5V    其附近的GND接单片机GND
	VMOT------------------------+12V    其附近的GND接电源的GND
	SLEEP------------------------和RESET短接
	RESET------------------------和SLEEP短接
	MS3--------------------------GND（不接，悬空）
	MS2--------------------------GND（不接，悬空）
	MS1--------------------------GND（不接，悬空）
	用RAMPS1.4扩展板的话，可以直接将A4988插上去，而不必考虑接线的问题。
*******************************************************************************/

#include "StepMotor.h"

void StepMotor_Init()     //4个步进电机的初始化
{
	pinMode(StepMotor_1_DIR, OUTPUT);    
	pinMode(StepMotor_1_STEP, OUTPUT);
	pinMode(StepMotor_1_ENA, OUTPUT);
	pinMode(StepMotor_2_DIR, OUTPUT);
	pinMode(StepMotor_2_STEP, OUTPUT);
	pinMode(StepMotor_2_ENA, OUTPUT);
	pinMode(StepMotor_3_DIR, OUTPUT);
	pinMode(StepMotor_3_STEP, OUTPUT);
	pinMode(StepMotor_3_ENA, OUTPUT);
	pinMode(StepMotor_4_DIR, OUTPUT);
	pinMode(StepMotor_4_STEP, OUTPUT);
	pinMode(StepMotor_4_ENA, OUTPUT);
}

void StepMotor_1_Move(bool DIR, int num, int speed)  //1号步进电机的控制
{
	digitalWrite(StepMotor_1_ENA, LOW);      //DIR控制方向，speed控制速度，num控制距离
	if (DIR)
	{
		digitalWrite(StepMotor_1_DIR, HIGH);     //内箱第一层推书机构向左移动
	}
	else
	{
		digitalWrite(StepMotor_1_DIR, LOW);      //内箱第一层推书机构向右移动
	}
	for(int i=0;i<num;i++)
	{
		digitalWrite(StepMotor_1_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_1_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_2_Move(bool DIR, int num, int speed)  //2号步进电机的控制
{
	digitalWrite(StepMotor_2_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_2_DIR, LOW);     //内箱第一层压书机构向右移动
	}
	else
	{
		digitalWrite(StepMotor_2_DIR, HIGH);     //内箱第一层压书机构向左移动
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_2_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_2_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_3_Move(bool DIR, int num, int speed)  //3号步进电机的控制
{
	digitalWrite(StepMotor_3_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_3_DIR, HIGH);     //内箱第二层推书机构向左移动
	}
	else
	{
		digitalWrite(StepMotor_3_DIR, LOW);      //内箱第二层推书机构向右移动
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_3_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_3_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_4_Move(bool DIR, int num, int speed)  //4号步进电机的控制
{
	digitalWrite(StepMotor_4_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_4_DIR, LOW);      //内箱第二层压书机构向右移动
	}
	else
	{
		digitalWrite(StepMotor_4_DIR, HIGH);     //内箱第二层压书机构向左移动
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_4_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_4_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_1_Stop(bool flag)     //1号步进电机的停止，flag=true，则通电堵转；flag=false，则不通电
{
	if (flag == false)
	{
		digitalWrite(StepMotor_1_ENA, HIGH);
	}
	else
	{
		digitalWrite(StepMotor_1_STEP, 0);
	}
}

void StepMotor_2_Stop(bool flag)      //2号步进电机的停止，flag=true，则通电堵转；flag=false，则不通电
{
	if (flag == false)
	{
		digitalWrite(StepMotor_2_ENA, HIGH);
	}
	else
	{
		digitalWrite(StepMotor_2_STEP, 0);
	}
}

void StepMotor_3_Stop(bool flag)     //3号步进电机的停止，flag=true，则通电堵转；flag=false，则不通电
{
	if (flag == false)
	{
		digitalWrite(StepMotor_3_ENA, HIGH);
	}
	else
	{
		digitalWrite(StepMotor_3_STEP, 0);
	}
}

void StepMotor_4_Stop(bool flag)     //4号步进电机的停止，flag=true，则通电堵转；flag=false，则不通电
{
	if (flag == false)
	{
		digitalWrite(StepMotor_4_ENA, HIGH);
	}
	else
	{
		digitalWrite(StepMotor_4_STEP, 0);
	}
}