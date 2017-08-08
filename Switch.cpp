/*******************************************************************************
	1号开关安装在上层的主动推书板和主动推书杆之间，常态的闭合态，低电平，当主动推书滑块将书推至目标处，
推书板从45°变成90°，1号开关断开，变成高电平；此后拨书滑块开始运动一定的时间wait_t1
    2号开关安装在主动拨书板和书接触的一面，常态是断开态，低电平，当
	3号开关是电磁继电器，控制主动推书板和主动推书杆之间的电磁吸盘闭合（拨书部件是否需要？？？zhangping）
	4号开关安装在主动推书滑块返程的时候，遇到限位开关停止
	5号开关是垂直升降电机的下部限位开关（上部是否需要？？？zhangping）
	

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
	pinMode(Top_Sucker, OUTPUT);               //上层的电磁继电器（控制电磁吸盘）
	pinMode(Bottom_Sucker, OUTPUT);          //下层的电磁继电器（控制电磁吸盘）
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
