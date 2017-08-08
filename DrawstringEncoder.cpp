/*******************************************************************************
��������������


Date:    2017.08.01
Version: V1.0
*******************************************************************************/
#include "DrawstringEncoder.h"
volatile long count = 0;
int pinValue;

void DrawstringEncoder_init()
{
	pinMode(PinA, INPUT); //�ǵøĳ�����ģʽ
	pinMode(PinB, INPUT);
	pinMode(PinA, INPUT_PULLUP);      //һ��Ҫ���������裬����û������
	pinMode(PinB, INPUT_PULLUP);      //һ��Ҫ���������裬����û������
	attachInterrupt(0, blink, RISING); //��������λ�Ʊ仯��ʱ�򣬻���A�����һ��������
	Serial.begin(9600);
}

void blink()
{
	pinValue = digitalRead(PinB);
	if (pinValue == HIGH)  //��A����������������ʱ��B��Ϊ�ߵ�ƽ����ʾ�����쳤������������
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