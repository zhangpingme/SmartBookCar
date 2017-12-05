#pragma once
#include "pins.h"
void StepMotor_Init();     //4个步进电机的初始化
void StepMotor_1_Move(bool DIR, int num, int speed);    //1号步进电机的控制
void StepMotor_2_Move(bool DIR, int num, int speed);    //2号步进电机的控制
void StepMotor_3_Move(bool DIR, int num, int speed);    //3号步进电机的控制
void StepMotor_4_Move(bool DIR, int num, int speed);    //4号步进电机的控制
void StepMotor_1_Stop(bool flag);    //1号步进电机的停止
void StepMotor_2_Stop(bool flag);    //2号步进电机的停止
void StepMotor_3_Stop(bool flag);    //3号步进电机的停止
void StepMotor_4_Stop(bool flag);    //4号步进电机的停止

