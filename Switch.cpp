/*******************************************************************************
10个微动开关和2个电磁吸盘的控制程序，开关的引脚值检测到外部输入为低电平，说明开关
闭合，开关被按下，否则开关是断开，未被按下。电磁吸盘写入值为高电平，则通电，产生
磁性，否则断电，无磁性。
*******************************************************************************/
#include "Switch.h"
#include "StepMotor.h"
void Switch_init()      //全部的微动开关和电磁吸盘的初始化
{
	pinMode(switch_2_NO, INPUT);
	pinMode(switch_2_NO, INPUT_PULLUP);
	pinMode(switch_3_NO, INPUT);
	pinMode(switch_3_NO, INPUT_PULLUP);
	pinMode(switch_5_NO, INPUT);
	pinMode(switch_5_NO, INPUT_PULLUP);
	pinMode(switch_6_NO, INPUT);
	pinMode(switch_6_NO, INPUT_PULLUP);
	pinMode(switch_7_NO, INPUT);
	pinMode(switch_7_NO, INPUT_PULLUP);
	pinMode(switch_9_NO, INPUT);
	pinMode(switch_9_NO, INPUT_PULLUP);
	pinMode(switch_10_NO, INPUT);
	pinMode(switch_10_NO, INPUT_PULLUP);
	pinMode(switch_12_NO, INPUT);
	pinMode(switch_12_NO, INPUT_PULLUP);
	pinMode(Top_Sucker, OUTPUT);               
	pinMode(Bottom_Sucker, OUTPUT);          
	digitalWrite(Top_Sucker, LOW);
	digitalWrite(Bottom_Sucker,LOW);
}

bool Switch_2()          //2号开关用于检测内箱第一层推书机构是否在最左端初始位置，若在则开关闭合，输出低电平，返回true   
{
	if (digitalRead(switch_2_NO) == 0)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_2_NO) == 0)
		{
			return true;
		} 
	}
	return false;
}

bool Switch_3()          //3号开关用于检测内箱第一层推书板与连杆之间，当推书板和水平面呈45度时，开关被压紧，保持闭合，输出低电平，返回false  
{                        //当推书板倾斜角度发生变化，3号开关脱离压紧状态，开关断开，输出高电平，返回true 
	if (digitalRead(switch_3_NO) == 1)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_3_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Switch_5()          //5号开关用于检测内箱第一层压书机构是否将书已经压紧或者（如果该层无书）是否处于内箱最右侧，与内箱右壁接触
{                        //如果压书机构处于可到达的最右位置，则开关闭合，输出低电平，返回true。
	if (digitalRead(switch_5_NO) == 0)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_5_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_6()          //6号开关用于检测内箱第二层推书机构是否在最左端初始位置，若在则开关闭合，输出低电平，返回true   
{
	if (digitalRead(switch_6_NO) == 0)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_6_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_7()          //7号开关用于检测内箱第二层推书板与连杆之间，当推书板和水平面呈45度时，开关被压紧，保持闭合，输出低电平，返回false  
{                        //当推书板倾斜角度发生变化，3号开关脱离压紧状态，开关断开，输出高电平，返回true 
	if (digitalRead(switch_7_NO) == 1)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_7_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Switch_9()          //9号开关用于检测内箱第二层压书机构是否将书已经压紧或者（如果该层无书）是否处于内箱最右侧，与内箱右壁接触
{                        //如果压书机构处于可到达的最右位置，则开关闭合，输出低电平，返回true。
	if (digitalRead(switch_9_NO) == 0)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_9_NO) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Switch_10()        //10号开关用于检测内箱是否下降到最底部，下降到最底，则按下，输出低电平，返回false 
{
	if (digitalRead(switch_10_NO) == 1)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_10_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Switch_12()        //12号开关用于检测内箱是否上升到最顶部，上升到最顶，则按下，输出低电平，返回false
{
	if (digitalRead(switch_12_NO) == 1)
	{
		delayMicroseconds(1);
		if (digitalRead(switch_12_NO) == 1)
		{
			return true;
		}
	}
	return false;
}

void Top_Sucker_Operate(bool flag)    //该电磁吸盘安装在内箱第一层推书机构中，flag=true表示通电，否则是断电
{
	if (flag == true)
	{
		digitalWrite(Top_Sucker, HIGH);  //通电产生磁性，推书板和第一连杆吸合贴紧，推书板与水平面垂直
	}
	else
	{
		digitalWrite(Top_Sucker, LOW);   //断电失去磁性，在弹簧合页作用下，推书板和第一连杆分离，推书板与水平面成45度
	}
}

void Bottom_Sucker_Operate(bool flag)    //该电磁吸盘安装在内箱第二层推书机构中，flag=true表示通电，否则是断电
{
	if (flag == true)
	{
		digitalWrite(Bottom_Sucker, HIGH);  //通电产生磁性，推书板和第二连杆吸合贴紧，推书板与水平面垂直
	}
	else
	{
		digitalWrite(Bottom_Sucker, LOW);   //断电失去磁性，在弹簧合页作用下，推书板和第二连杆分离，推书板与水平面成45度
	}
}
