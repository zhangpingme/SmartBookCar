﻿/*******************************************************************************
当推书板返程归零之后，安装在导书板下面的避障传感器开始检测是否有书从分拣系统中进入到小车内。
若有书进入，则避障传感器返回一个信号，待一定时间后，推书板开始工作。
*******************************************************************************/
#include "BookDetect.h"  

void BookDetect_init()  //避障传感器初始化
{
	pinMode(PinBookDetect, INPUT); 
}

bool Book_Detect()   //传感器开始工作
{
	if (analogRead(PinBookDetect) < 100)   //如果检测到上方有物体经过，避障传感器输出值明显变小（初始为255）
		return true;
	else
		return false;
}

