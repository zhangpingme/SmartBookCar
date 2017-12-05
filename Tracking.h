#pragma once
#include "pins.h"
#include "DCMotor.h"
void Track_init();       //循迹初始化。初始化5个红外传感器。
void Track_forward();    //循迹前进，沿着黑线走