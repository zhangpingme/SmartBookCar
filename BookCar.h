#pragma once
#include "BookDetect.h"            //避障传感器检测书的头文件
#include "DrawstringEncoder.h"  //拉绳编码器头文件
#include "StepMotor.h"              //步进电机头文件
#include "Switch.h"                   //限位开关和电磁继电器头文件
#include "DCMotor.h"                //轮子电机和升降电机（都是直流电机）头文件
#include "CarPower.h"               //电量检测单元头文件
#include "Connect.h"                 //与分拣系统和手机APP的通信头文件
#include "SuperSonic.h"            //超声波传感器头文件
#include "Tracking.h"                //小车循迹头文件

void BookCar_init();
void BookCar_Move_Top();
void BookCar_Move_Bottom();
bool BookCar_Control_Top();
bool BookCar_Control_Bottom();
void ChangeLayer();
void Rise();
void BookCar_Operate();