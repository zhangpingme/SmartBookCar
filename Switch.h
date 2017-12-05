#pragma once
#include "pins.h"
void Switch_init();    //开关和电磁吸盘的初始化
bool Switch_2();       //获取开关的状态，以判断开关是否被按下，输出true表示被按下，否则是未按下
bool Switch_3();
bool Switch_5();
bool Switch_6();
bool Switch_7();
bool Switch_9();
bool Switch_10();
bool Switch_12();
void Top_Sucker_Operate(bool flag);   //设置电磁吸盘的状态，输入为true表示通电产生磁性，否则不产生磁性
void Bottom_Sucker_Operate(bool flag);
