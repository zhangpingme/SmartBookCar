/*******************************************************************************
	�������һ����4�������Ϊ1~4����Mega2560�ṩ�����źźͷ����źţ���24Vֱ����Դͨ��ת��Ϊ12V�����磬
	��������������������ϺͲ��������������	ÿ���������ͨ��һ��A4988ģ�����������
	1�Ų�������������������ϲ㣬���黬��
	2�Ų�������������������ϲ㣬���黬��
	3�Ų�������������������²㣬���黬��
	4�Ų�������������������²㣬���黬��

	A4988���������ߣ�
	VDD--------------------------+5V    �丽����GND�ӵ�Ƭ��GND
	VMOT------------------------+12V   �丽����GND�ӵ�Դ��GND������Ҫ�����أ�zhangping��
	SLEEP------------------------��RESET�̽�
	RESET------------------------��SLEEP�̽�
	MS3--------------------------GND�����ӣ����գ�
	MS2--------------------------GND�����ӣ����գ�
	MS1--------------------------GND�����ӣ����գ�
	��RAMPS1.4��չ������֮����Щ���Բ���ȥ�ܣ���Ϊ�����Ѿ�������

	Date:    2017.08.01
	Version: V1.0
*******************************************************************************/

#include "StepMotor.h"

void StepMotor_Init()
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

void StepMotor_1_Move(bool DIR, int num, int speed)  //DIR���Ʒ���speed�����ٶȣ�num���ƾ���
{
	digitalWrite(StepMotor_1_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_1_DIR, HIGH);     //�����г�
	}
	else
	{
		digitalWrite(StepMotor_1_DIR, LOW);     //�����г�
	}
	for(int i=0;i<num;i++)
	{
		digitalWrite(StepMotor_1_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_1_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_2_Move(bool DIR, int num, int speed)  //DIR���Ʒ���speed�����ٶȣ�num���ƾ���
{
	digitalWrite(StepMotor_2_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_2_DIR, HIGH);     //�����г�
	}
	else
	{
		digitalWrite(StepMotor_2_DIR, LOW);     //�����г�
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_2_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_2_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_3_Move(bool DIR, int num, int speed)  //DIR���Ʒ���speed�����ٶȣ�num���ƾ���
{
	digitalWrite(StepMotor_3_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_3_DIR, HIGH);     //�����г�
	}
	else
	{
		digitalWrite(StepMotor_3_DIR, LOW);     //�����г�
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_3_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_3_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_4_Move(bool DIR, int num, int speed)  //DIR���Ʒ���speed�����ٶȣ�num���ƾ���
{
	digitalWrite(StepMotor_4_ENA, LOW);
	if (DIR)
	{
		digitalWrite(StepMotor_4_DIR, HIGH);     //�����г�
	}
	else
	{
		digitalWrite(StepMotor_4_DIR, LOW);     //�����г�
	}
	for (int i = 0; i<num; i++)
	{
		digitalWrite(StepMotor_4_STEP, HIGH);
		delayMicroseconds(speed);
		digitalWrite(StepMotor_4_STEP, LOW);
		delayMicroseconds(speed);
	}
}

void StepMotor_1_Stop(bool flag)                //flag=true����ͨ���ת��flag=false����ͨ��
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

void StepMotor_2_Stop(bool flag)                //flag=true����ͨ���ת��flag=false����ͨ��
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

void StepMotor_3_Stop(bool flag)                //flag=true����ͨ���ת��flag=false����ͨ��
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

void StepMotor_4_Stop(bool flag)                //flag=true����ͨ���ת��flag=false����ͨ��
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