#pragma once
#include "pins.h"
void DCMotor_init();
void DCMotor_Big_Move(int speed, bool DIR);
void DCMotor_Big_Stop(bool flag);
void DCMotor_Left_Move(int speed, bool DIR);
void DCMotor_Left_Stop(bool flag);
void DCMotor_Right_Move(int speed, bool DIR);
void DCMotor_Right_Stop(bool flag);

//小车的运动控制
void go_back();
void big_left();    //向左转弯
void big_right();	//向右转弯
void small_left();
void small_right();
void go_straight();//直走
void UnLoadBook();
void LoadBook();
void GoWait();
void Car_Stop();
