#pragma once
#include "pins.h"
void DCMotor_init();   //三个直流电机都初始化
void DCMotor_Big_Move(int speed, bool DIR);//升降直流电机的调速和调向
void DCMotor_Big_Stop(bool flag);//停止升降直流电机
void DCMotor_Left_Move(int speed, bool DIR);//左轮电机的调速和调向
void DCMotor_Left_Stop(bool flag);//停止左轮直流电机
void DCMotor_Right_Move(int speed, bool DIR);//右轮电机的调速和调向
void DCMotor_Right_Stop(bool flag);//停止右轮直流电机

//小车的运动控制
void go_back();         //小车向后直线倒退
void big_left();        //向左转大弯
void big_right();	    //向右转大弯
void small_left();      //向左转小弯
void small_right();     //向右转小弯
void smallMid_left();   //向左转中小弯
void smallMid_right();  //向右转中小弯
void bigMid_left();     //向左转大弯
void bigMid_right();    //向左转大弯
void go_straight();     //小车向前直线行驶

