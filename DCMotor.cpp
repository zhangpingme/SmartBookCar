#include "DCMotor.h"

void DCMotor_init()
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

void DCMotor_Big_Move(int speed, bool DIR)         //升降的直流大电机的调速和调向
{
	analogWrite(DC_Big_ENA, speed);
	if (DIR == true)                                              //true表示方向向上
	{
		digitalWrite(DC_Big_Pin1, 0);
		digitalWrite(DC_Big_Pin2, 1);
	}
	else                                                              //false表示方向向下
	{
		digitalWrite(DC_Big_Pin1, 1);
		digitalWrite(DC_Big_Pin2, 0);
	}
}

void DCMotor_Big_Stop(bool flag)                         //flag=true  电机刹车   ;    flag=false   电机禁能
{
	if (flag == true)
	{
		digitalWrite(DC_Big_ENA, HIGH);
		digitalWrite(DC_Big_Pin1, 0);
		digitalWrite(DC_Big_Pin2, 0);
	}
	else
	{
		digitalWrite(DC_Big_ENA, LOW);
		digitalWrite(DC_Big_Pin1, 1);
		digitalWrite(DC_Big_Pin2, 1);
	}
}

void DCMotor_Left_Move(int speed, bool DIR)         //左轮电机的调速和调向
{
	analogWrite(DC_Left_ENA, speed);
	if (DIR == true)                                               //true表示前进，false表示后退
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

void DCMotor_Left_Stop(bool flag)                         //flag=true  电机刹车   ;    flag=false   电机禁能
{
	if (flag == true)
	{
		digitalWrite(DC_Left_ENA, HIGH);
		digitalWrite(DC_Left_Pin1, 0);
		digitalWrite(DC_Left_Pin2, 0);
	}
	else
	{
		digitalWrite(DC_Left_ENA, LOW);
		digitalWrite(DC_Left_Pin1, 1);
		digitalWrite(DC_Left_Pin2, 1);
	}
}

void DCMotor_Right_Move(int speed, bool DIR)       //右轮电机的调速和调向
{
	analogWrite(DC_Right_ENA, speed);
	if (DIR == true)                                               //true表示前进，false表示后退
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

void DCMotor_Right_Stop(bool flag)                       //flag=true  电机刹车   ;    flag=false   电机禁能
{
	if (flag == true)
	{
		digitalWrite(DC_Right_ENA, HIGH);
		digitalWrite(DC_Right_Pin1, 0);
		digitalWrite(DC_Right_Pin2, 0);
	}
	else
	{
		digitalWrite(DC_Right_ENA, LOW);
		digitalWrite(DC_Right_Pin1, 1);
		digitalWrite(DC_Right_Pin2, 1);
	}
}

void go_straight()//直走
{
	DCMotor_Left_Move(255, true);
	DCMotor_Right_Move(255, true);
}

void go_back()    //倒退
{
	DCMotor_Left_Move(Car_LowMid_Speed, false);
	DCMotor_Right_Move(Car_LowMid_Speed, false);
}
void big_left()     //向左转大弯
{
	DCMotor_Left_Move(0,true);
	DCMotor_Right_Move(Car_High_Speed, true);
}
void big_right()	//向右转大弯
{
	DCMotor_Right_Move(0, true);
	DCMotor_Left_Move(Car_High_Speed, true);
}
void small_left()    //向左转小弯
{
	DCMotor_Left_Move(0, true);
	DCMotor_Right_Move(Car_HighMid_Speed, true);
}
void small_right()   //向右转小弯
{
	DCMotor_Right_Move(Car_LowMid_Speed, true);
	DCMotor_Left_Move(Car_HighMid_Speed, true);
}

void LoadBook()             //候车区的小车接到换车指令，前往接书区接书
{
	go_straight();
}

void UnLoadBook()        //接书区的小车装满书后，前往卸载区卸书
{
	go_back();
}

void GoWait()               //卸载区的小车卸完书后，前往候车区等待
{
	//go_back();
}

void Car_Stop()
{
	DCMotor_Left_Stop(false);
	DCMotor_Right_Stop(false);
}