#pragma once
#include "pins.h"
void DCMotor_init();
void DCMotor_Big_Move(int speed, bool DIR);
void DCMotor_Big_Stop(bool flag);
void DCMotor_Left_Move(int speed, bool DIR);
void DCMotor_Left_Stop(bool flag);
void DCMotor_Right_Move(int speed, bool DIR);
void DCMotor_Right_Stop(bool flag);

//С�����˶�����
void go_back();
void big_left();    //����ת��
void big_right();	//����ת��
void small_left();
void small_right();
void go_straight();//ֱ��
void UnLoadBook();
void LoadBook();
void GoWait();
void Car_Stop();
