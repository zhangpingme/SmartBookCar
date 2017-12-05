/*******************************************************************************************************************************
Tracking用于循迹，主要是用红外传感器检测黑白线，如果检测到黑线，则返回高电平，否则是低电平，注意要调节每个红外模块的阈值。
小车的前端下表面均布有5个红外传感器，依次编号为2~6号，4号传感器居中，2号在最左侧，6号在最右侧。
*******************************************************************************************************************************/

#include "Tracking.h"
#include "BookCar.h"

void Track_init()        //循迹初始化。初始化5个红外传感器。
{
	pinMode(hongwai_2, INPUT);
	pinMode(hongwai_2, INPUT_PULLUP);
	pinMode(hongwai_3, INPUT);
	pinMode(hongwai_3, INPUT_PULLUP);
	pinMode(hongwai_4, INPUT);
	pinMode(hongwai_4, INPUT_PULLUP);
	pinMode(hongwai_5, INPUT);
	pinMode(hongwai_5, INPUT_PULLUP);
	pinMode(hongwai_6, INPUT);
	pinMode(hongwai_6, INPUT_PULLUP);
}

void Track_forward()    //循迹前进，沿着黑线走
{
	if (digitalRead(hongwai_4) == 1 && digitalRead(hongwai_3) == 1 && digitalRead(hongwai_5) == 1 && digitalRead(hongwai_2) ==0 && digitalRead(hongwai_6) == 0)
		go_straight();  //如果4号、3号、1号红外传感器同时检测到黑线，则黑线位于小车中央，小车直线行驶即可。
	else if (digitalRead(hongwai_4) == 1 && digitalRead(hongwai_5) == 0 && digitalRead(hongwai_3) == 0)
		go_straight();  //如果只有4号红外传感器检测到黑线，则黑线位于小车中央，小车直线行驶即可。
	else if (digitalRead(hongwai_4) == 1 && digitalRead(hongwai_5) == 1 && digitalRead(hongwai_3) == 0)
		small_left();   //如果只有4号和5号红外传感器检测到黑线，则黑线略微在小车右侧，小车小幅左转即可。
	else if (digitalRead(hongwai_4) == 1 && digitalRead(hongwai_3) == 1 && digitalRead(hongwai_5) == 0)
		small_right();  //如果只有4号和3号红外传感器检测到黑线，则黑线略微在小车左侧，小车小幅右转即可。
	else if (digitalRead(hongwai_3) == 1 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_2) == 0)
		smallMid_right();   //如果只有3号红外传感器检测到黑线，则黑线位于小车左侧，小车右转。
	else if (digitalRead(hongwai_5) == 1 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_6) == 0)
		smallMid_left();    //如果只有5号红外传感器检测到黑线，则黑线位于小车右侧，小车左转。
	else if (digitalRead(hongwai_3) == 1 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_2) == 1)
		bigMid_right();  //如果只有2号和3号红外传感器检测到黑线，则黑线位于小车左侧，小车右转。
	else if (digitalRead(hongwai_5) == 1 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_6) == 1)
		bigMid_left();  //如果只有5号和6号红外传感器检测到黑线，则黑线位于小车右侧，小车左转。
	else if (digitalRead(hongwai_2) == 1 && digitalRead(hongwai_3) == 0 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_5) == 0 && digitalRead(hongwai_6) == 0)
		big_right();    //如果只有2号红外传感器检测到黑线，则黑线位于小车左侧，小车大幅度右转。
	else if (digitalRead(hongwai_2) == 0 && digitalRead(hongwai_3) == 0 && digitalRead(hongwai_4) == 0 && digitalRead(hongwai_5) == 0 && digitalRead(hongwai_6) == 1)
		big_left();     //如果只有6号红外传感器检测到黑线，则黑线位于小车右侧，小车大幅度左转。
	else if (digitalRead(hongwai_2) == 1 && digitalRead(hongwai_3) == 1 && digitalRead(hongwai_4) == 1 && digitalRead(hongwai_5) == 1 && digitalRead(hongwai_6) == 1)
	{
		Car_Stop();    //如果所有红外传感器都检测到黑线，则小车到达循迹终点，即图书分拣系统正下方，小车停止运动。
		if (isAuto)
		{
			esp8266_send("ok");      //向手机控制端发送信息
			car_order = CAR_PREPARE_GET_BOOK;    //如果此时是自动模式，则进入下一步操作，发送准备接书指令。
		}
	}
	else    //如果不是上面的任一种情况，则说明小车脱离预定轨迹，发生错误，停止运动，等待用户手动控制。
	{
		Car_Stop();
		esp8266_send("WRONG!");    //向手机控制端发送信息
		isAuto = false;              //设置小车模式为手动控制模式
	}
	delay(100);                     //每0.1秒查询一次红外传感器的输出值，以判断小车的位置，并及时作出相应调整
}