/*******************************************************************************
直流电机的相关操作函数存放在此。
1、DC_Big指用于内箱升降的带抱闸的直流电机；
2、DC_Left指用于驱动左轮运动的直流电机；
2、DC_Right指用于驱动右轮运动的直流电机。
*******************************************************************************/
#include "DCMotor.h"

void DCMotor_init()      //三个直流电机都初始化
{
	pinMode(DC_Big_Pin1, OUTPUT);
	pinMode(DC_Big_Pin2, OUTPUT);
	pinMode(DC_Big_ENA, OUTPUT);
	pinMode(DC_Left_Pin1, OUTPUT);
	pinMode(DC_Left_Pin2, OUTPUT);
	pinMode(DC_Left_ENA, OUTPUT);
	pinMode(DC_Right_Pin1, OUTPUT);
	pinMode(DC_Right_Pin2, OUTPUT);
	pinMode(DC_Right_ENA, OUTPUT);
}

void DCMotor_Big_Move(int speed, bool DIR)    //升降直流电机的调速和调向，speed用于设置速度大小，DIR设置上升或下降。
{
	analogWrite(DC_Big_ENA, speed);
	if (DIR == true)                          //true表示方向向下
	{
		digitalWrite(DC_Big_Pin1, 0);
		digitalWrite(DC_Big_Pin2, 1);
	}
	else                                      //false表示方向向上
	{
		digitalWrite(DC_Big_Pin1, 1);
		digitalWrite(DC_Big_Pin2, 0);
	}
}

void DCMotor_Big_Stop(bool flag)             //停止升降直流电机，一般使用flag=false就可以了。
{
	if (flag == true)                        //flag=true 电机刹车 
	{
		digitalWrite(DC_Big_ENA, HIGH);
		digitalWrite(DC_Big_Pin1, 0);
		digitalWrite(DC_Big_Pin2, 0);
	}
	else                                      //flag=false 电机禁能
	{
		digitalWrite(DC_Big_ENA, LOW);
		digitalWrite(DC_Big_Pin1, 1);
		digitalWrite(DC_Big_Pin2, 1);
	}
}

void DCMotor_Left_Move(int speed, bool DIR)   //左轮电机的调速和调向
{
	analogWrite(DC_Left_ENA, speed);
	if (DIR == true)                          //true表示前进，false表示后退
	{
		digitalWrite(DC_Left_Pin1, 0);
		digitalWrite(DC_Left_Pin2, 1);
	}
	else
	{
		digitalWrite(DC_Left_Pin1, 1);
		digitalWrite(DC_Left_Pin2, 0);
	}
}

void DCMotor_Left_Stop(bool flag)             //停止左轮直流电机，一般使用flag=false就可以了。
{
	if (flag == true)                         //flag=true 电机刹车 
	{
		digitalWrite(DC_Left_ENA, HIGH);
		digitalWrite(DC_Left_Pin1, 0);
		digitalWrite(DC_Left_Pin2, 0);
	}
	else                                      //flag=false 电机禁能
	{
		digitalWrite(DC_Left_ENA, LOW);
		digitalWrite(DC_Left_Pin1, 1);
		digitalWrite(DC_Left_Pin2, 1);
	}
}

void DCMotor_Right_Move(int speed, bool DIR)   //右轮电机的调速和调向
{
	analogWrite(DC_Right_ENA, speed);
	if (DIR == true)                           //true表示前进，false表示后退
	{
		digitalWrite(DC_Right_Pin1, 1);
		digitalWrite(DC_Right_Pin2, 0);
	}
	else
	{
		digitalWrite(DC_Right_Pin1, 0);
		digitalWrite(DC_Right_Pin2, 1);
	}
}

void DCMotor_Right_Stop(bool flag)              //停止右轮直流电机，一般使用flag=false就可以了。
{
	if (flag == true)                           //flag=true 电机刹车 
	{
		digitalWrite(DC_Right_ENA, HIGH);
		digitalWrite(DC_Right_Pin1, 0);
		digitalWrite(DC_Right_Pin2, 0);
	}
	else                                        //flag=false 电机禁能
	{
		digitalWrite(DC_Right_ENA, LOW);
		digitalWrite(DC_Right_Pin1, 1);
		digitalWrite(DC_Right_Pin2, 1);
	}
}

//下面是小车运动时方向控制的函数，通过左右轮速度不同，实现差速转向
void go_straight()  //小车向前直线行驶，两边车轮均最大速度运行
{
	DCMotor_Left_Move(Car_High_Speed, true);
	DCMotor_Right_Move(Car_High_Speed, true);
}
void go_back()      //小车向后直线倒退，两边车轮均最大速度运行
{
	DCMotor_Left_Move(Car_High_Speed, false);
	DCMotor_Right_Move(Car_High_Speed, false);
}
void big_left()     //向左转大弯
{
	DCMotor_Left_Move(Car_Low_Speed, true);
	DCMotor_Right_Move(Car_High_Speed, true);
}
void big_right()	//向右转大弯
{
	DCMotor_Right_Move(Car_Low_Speed, true);
	DCMotor_Left_Move(Car_High_Speed, true);
}
void bigMid_left()     //向左转大弯
{
	DCMotor_Left_Move(Car_LowMid_Speed, true);
	DCMotor_Right_Move(Car_High_Speed, true);
}
void bigMid_right()	//向右转大弯
{
	DCMotor_Right_Move(Car_LowMid_Speed, true);
	DCMotor_Left_Move(Car_High_Speed, true);
}
void small_left()    //向左转小弯
{
	DCMotor_Left_Move(Car_LowMid_Speed, true);
	DCMotor_Right_Move(Car_Mid_Speed, true);
}
void small_right()   //向右转小弯
{
	DCMotor_Right_Move(Car_LowMid_Speed, true);
	DCMotor_Left_Move(Car_Mid_Speed, true);
}
void smallMid_left()    //向左转小弯
{
	DCMotor_Left_Move(Car_LowMid_Speed, true);
	DCMotor_Right_Move(Car_HighMid_Speed, true);
}
void smallMid_right()   //向右转小弯
{
	DCMotor_Right_Move(Car_LowMid_Speed, true);
	DCMotor_Left_Move(Car_HighMid_Speed, true);
}
