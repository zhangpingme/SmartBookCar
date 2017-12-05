#pragma once
#include "pins.h"
extern volatile long count;      //用于存储脉冲数目

void DrawstringEncoder_init();   //初始化拉绳编码器
int ReadCount();   //读取引脚上的外部中断的脉冲数，用于判断内箱上升的距离
void blink();      //外部中断的处理函数，用于累计外部中断的脉冲数
