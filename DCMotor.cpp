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

void DCMotor_Big_Move(int speed, bool DIR)         //������ֱ�������ĵ��ٺ͵���
{
	analogWrite(DC_Big_ENA, speed);
	if (DIR == true)                                              //true��ʾ��������
	{
		digitalWrite(DC_Big_Pin1, 0);
		digitalWrite(DC_Big_Pin2, 1);
	}
	else                                                              //false��ʾ��������
	{
		digitalWrite(DC_Big_Pin1, 1);
		digitalWrite(DC_Big_Pin2, 0);
	}
}

void DCMotor_Big_Stop(bool flag)                         //flag=true  ���ɲ��   ;    flag=false   �������
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

void DCMotor_Left_Move(int speed, bool DIR)         //���ֵ���ĵ��ٺ͵���
{
	analogWrite(DC_Left_ENA, speed);
	if (DIR == true)                                               //true��ʾǰ����false��ʾ����
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

void DCMotor_Left_Stop(bool flag)                         //flag=true  ���ɲ��   ;    flag=false   �������
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

void DCMotor_Right_Move(int speed, bool DIR)       //���ֵ���ĵ��ٺ͵���
{
	analogWrite(DC_Right_ENA, speed);
	if (DIR == true)                                               //true��ʾǰ����false��ʾ����
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

void DCMotor_Right_Stop(bool flag)                       //flag=true  ���ɲ��   ;    flag=false   �������
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

void go_straight()//ֱ��
{
	DCMotor_Left_Move(255, true);
	DCMotor_Right_Move(255, true);
}

void go_back()    //����
{
	DCMotor_Left_Move(Car_LowMid_Speed, false);
	DCMotor_Right_Move(Car_LowMid_Speed, false);
}
void big_left()     //����ת����
{
	DCMotor_Left_Move(0,true);
	DCMotor_Right_Move(Car_High_Speed, true);
}
void big_right()	//����ת����
{
	DCMotor_Right_Move(0, true);
	DCMotor_Left_Move(Car_High_Speed, true);
}
void small_left()    //����תС��
{
	DCMotor_Left_Move(0, true);
	DCMotor_Right_Move(Car_HighMid_Speed, true);
}
void small_right()   //����תС��
{
	DCMotor_Right_Move(Car_LowMid_Speed, true);
	DCMotor_Left_Move(Car_HighMid_Speed, true);
}

void LoadBook()             //������С���ӵ�����ָ�ǰ������������
{
	go_straight();
}

void UnLoadBook()        //��������С��װ�����ǰ��ж����ж��
{
	go_back();
}

void GoWait()               //ж������С��ж�����ǰ�������ȴ�
{
	//go_back();
}

void Car_Stop()
{
	DCMotor_Left_Stop(false);
	DCMotor_Right_Stop(false);
}