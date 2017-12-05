#pragma once
#include "pins.h"

void BookDetect_init();  //避障传感器初始化
bool Book_Detect();      //若有书进入小车，返回true，否则是false