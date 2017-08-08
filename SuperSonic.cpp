/*
	��������������˳�������ഫ����������⵽��ѹ��֮����������һ�˵ľ����С����˵���ò�����
*/

#include "SuperSonic.h"
float distance;
int pos = 0;
const int NumOfSample = 5;           //��������
double Samples[NumOfSample];     //ÿ�β����õ��ľ�����ɵ�����

//��������N��ֵ������ƽ��ֵ�ͱ�׼��
double mean(double a[], int n, double *ps)
{
	double sum = 0.0, aver = 0.0, e = 0.0;

	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	aver = sum / n;
	return aver;
}

void SuperSonicInit()
{
	pinMode(TrigPin_1, OUTPUT);
	// Ҫ�������������������ȣ���Ҫ������Ϊ����״̬
	pinMode(EchoPin_1, INPUT);
	pinMode(TrigPin_2, OUTPUT);
	pinMode(EchoPin_2, INPUT);
}

double celiang_1()
{
	// ����һ��10us�ĸ�����ȥ����TrigPin 
	digitalWrite(TrigPin_1, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin_1, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin_1, LOW);
	// ��������ȣ������������
	distance = pulseIn(EchoPin_1, HIGH) * 0.017;

	if (pos < NumOfSample) 
	{
		// ������ȡ�������ֵ
		Samples[pos] = distance;
		pos++;
		delay(50);
	}
	else 
	{
		// �������ֵ�Ѿ���ȡ��ϣ��������Ƿ����Ҫ��
		pos = 0;
		double s = 0;
		double m = mean(Samples, NumOfSample, &s);
		return m;
	}
}

double celiang_2()
{
	// ����һ��10us�ĸ�����ȥ����TrigPin 
	digitalWrite(TrigPin_2, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin_2, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin_2, LOW);
	// ��������ȣ������������
	distance = pulseIn(EchoPin_2, HIGH) * 0.017;

	if (pos < NumOfSample)
	{
		// ������ȡ�������ֵ
		Samples[pos] = distance;
		pos++;
		delay(50);
	}
	else
	{
		// �������ֵ�Ѿ���ȡ��ϣ��������Ƿ����Ҫ��
		pos = 0;
		double s = 0;
		double m = mean(Samples, NumOfSample, &s);
		return m;
	}
}

bool DistanceDetect(bool flag)               //true��ʾ�ϲ���ľ��������false��ʾ�²���ľ������
{
	if (flag == true)
	{
		distance = celiang_1();
	}
	else
	{
		distance = celiang_2();
	}

	if (distance <= MinDistance&&distance>0.1)
	{
		return true;
	}
	else
		return false;
}
