/*******************************************************************************
	1�ſ��ذ�װ���ϲ���������������������֮�䣬��̬�ıպ�̬���͵�ƽ�����������黬�齫������Ŀ�괦��
������45����90�㣬1�ſ��ضϿ�����ɸߵ�ƽ���˺��黬�鿪ʼ�˶�һ����ʱ��wait_t1
    2�ſ��ذ�װ��������������Ӵ���һ�棬��̬�ǶϿ�̬���͵�ƽ����
	3�ſ����ǵ�ż̵����������������������������֮��ĵ�����̱պϣ����鲿���Ƿ���Ҫ������zhangping��
	4�ſ��ذ�װ���������黬�鷵�̵�ʱ��������λ����ֹͣ
	5�ſ����Ǵ�ֱ����������²���λ���أ��ϲ��Ƿ���Ҫ������zhangping��
	

Date:    2017.07.20
Version: V1.0
*******************************************************************************/
#include "Switch.h"
#include "StepMotor.h"
void Switch_init()
{
	pinMode(switch_1_NO, INPUT);
	pinMode(switch_1_NO, INPUT_PULLUP);
	pinMode(switch_2_NO, INPUT);
	pinMode(switch_2_NO, INPUT_PULLUP);
	pinMode(switch_3_NO, INPUT);
	pinMode(switch_3_NO, INPUT_PULLUP);
	pinMode(switch_4_NO, INPUT);
	pinMode(switch_4_NO, INPUT_PULLUP);
	pinMode(switch_5_NO, INPUT);
	pinMode(switch_5_NO, INPUT_PULLUP);
	pinMode(switch_6_NO, INPUT);
	pinMode(switch_6_NO, INPUT_PULLUP);
	pinMode(switch_7_NO, INPUT);
	pinMode(switch_7_NO, INPUT_PULLUP);
	pinMode(switch_8_NO, INPUT);
	pinMode(switch_8_NO, INPUT_PULLUP);
	pinMode(switch_9_NO, INPUT);
	pinMode(switch_9_NO, INPUT_PULLUP);
	pinMode(switch_10_NO, INPUT);
	pinMode(switch_10_NO, INPUT_PULLUP);
	pinMode(Top_Sucker, OUTPUT);               //�ϲ�ĵ�ż̵��������Ƶ�����̣�
	pinMode(Bottom_Sucker, OUTPUT);          //�²�ĵ�ż̵��������Ƶ�����̣�
}

bool Switch_1()
{
	if (digitalRead(switch_1_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_1_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_2()
{
	if (digitalRead(switch_2_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_2_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_3()
{
	if (digitalRead(switch_3_NO) == 1)
	{
		delay(1);
		if (digitalRead(switch_3_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Switch_4()
{
	if (digitalRead(switch_4_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_4_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_5()
{
	if (digitalRead(switch_5_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_5_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_6()
{
	if (digitalRead(switch_6_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_6_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_7()
{
	if (digitalRead(switch_7_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_7_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_8()
{
	if (digitalRead(switch_8_NO) == 0)
	{
		delay(1);
		if (digitalRead(switch_8_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_9()
{
	if (digitalRead(switch_9_NO) == 1)
	{
		delay(1);
		if (digitalRead(switch_9_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Switch_10()
{
	if (digitalRead(switch_10_NO) == 1)
	{
		delay(1);
		if (digitalRead(switch_10_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

void Top_Sucker_Operate(bool flag)
{
	if (flag == true)
	{
		digitalWrite(Top_Sucker, HIGH);
	}
	else
	{
		digitalWrite(Top_Sucker, LOW);
	}
}

void Bottom_Sucker_Operate(bool flag)
{
	if (flag == true)
	{
		digitalWrite(Bottom_Sucker, HIGH);
	}
	else
	{
		digitalWrite(Bottom_Sucker, LOW);
	}
}
