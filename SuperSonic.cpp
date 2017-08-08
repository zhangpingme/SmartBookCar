/*
	上下两层均放置了超声波测距传感器，当检测到书压紧之后拨书板距离另一端的距离过小，则说明该层已满
*/

#include "SuperSonic.h"
float distance;
int pos = 0;
const int NumOfSample = 5;           //采样次数
double Samples[NumOfSample];     //每次采样得到的距离组成的数组

//计算连续N个值，返回平均值和标准差
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
	// 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
	pinMode(EchoPin_1, INPUT);
	pinMode(TrigPin_2, OUTPUT);
	pinMode(EchoPin_2, INPUT);
}

double celiang_1()
{
	// 产生一个10us的高脉冲去触发TrigPin 
	digitalWrite(TrigPin_1, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin_1, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin_1, LOW);
	// 检测脉冲宽度，并计算出距离
	distance = pulseIn(EchoPin_1, HIGH) * 0.017;

	if (pos < NumOfSample) 
	{
		// 连续读取多个返回值
		Samples[pos] = distance;
		pos++;
		delay(50);
	}
	else 
	{
		// 多个返回值已经读取完毕，计算结果是否符合要求
		pos = 0;
		double s = 0;
		double m = mean(Samples, NumOfSample, &s);
		return m;
	}
}

double celiang_2()
{
	// 产生一个10us的高脉冲去触发TrigPin 
	digitalWrite(TrigPin_2, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin_2, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin_2, LOW);
	// 检测脉冲宽度，并计算出距离
	distance = pulseIn(EchoPin_2, HIGH) * 0.017;

	if (pos < NumOfSample)
	{
		// 连续读取多个返回值
		Samples[pos] = distance;
		pos++;
		delay(50);
	}
	else
	{
		// 多个返回值已经读取完毕，计算结果是否符合要求
		pos = 0;
		double s = 0;
		double m = mean(Samples, NumOfSample, &s);
		return m;
	}
}

bool DistanceDetect(bool flag)               //true表示上层书的距离测量，false表示下层书的距离测量
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
