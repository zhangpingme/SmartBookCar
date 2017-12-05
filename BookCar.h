#pragma once
#include "BookDetect.h"         //避障传感器头文件，用于检测书是否进入小车
#include "DrawstringEncoder.h"  //拉绳编码器头文件，用于检测内箱和外箱之间相对距离
#include "StepMotor.h"          //步进电机头文件，用于驱动内箱中的压书和推书机构
#include "Switch.h"             //限位开关和电磁继电器头文件
#include "DCMotor.h"            //轮子电机和升降电机（都是直流电机）头文件
#include "Tracking.h"           //小车循迹功能头文件
#include "MsTimer2.h"           //定时器头文件，这是库函数
#include "esp8266.h"            //ESP8266串口转WiFi模块头文件
#include "arduino_com_control.h"//Arduino和手机控制端信息交互功能头文件，通过串口实现

extern ComControl Com1;         //这个定义在arduino_com_control.cpp里面，用于与手机控制端信息交互的句柄
#define Max_number_1 15         //定义内箱各层能容纳的书的本数
#define Max_number_2 10

/**
	小车有自动模式，当用手机客户端发出指令后，小车自动完成全部过程；也可以用手机手动
	控制小车。isAuto用于保存小车当前模式的变量，其中true表示自动模式，false表示手动模式
 */
extern bool isAuto;

//为实现状态机，，需要定义机器的全部状态和指令。
typedef enum {
	//指令枚举类型，类型名car_order_t。
	CAR_STOP=1,         //停止指令
	CAR_STANDBY=2,      //待定指令
	CAR_LIFT=3,         //上升指令
	CAR_DESCEND=4,      //下降指令
	CAR_FWD=5,          //前进指令
	CAR_BKD=6,          //后退指令
	CAR_LFD=7,          //左转指令
	CAR_RTD=8,          //右转指令
	CAR_AUTO_MOVE=9,    //循迹指令
	//integral
	CAR_PREPARE_GET_BOOK=14, //准备接书指令
	CAR_GET_BOOK=10,    //接书整理指令
	CAR_SET_LAYER_1=11, //下降到底指令，因为内箱行程的最低点就在第一层接书的高度
	CAR_SET_LAYER_2=12, //到达第二层指令
	CAR_RECOVER=13,     //复位指令
	CAR_PREPARE_LIFT_AND_DOWN=15,  //升降准备指令
	CAR_AUTO_RUN = 16,  //自动模式指令
	CAR_SET_TOP = 17,   //上升到顶指令
}car_order_t;

typedef enum {
	//状态枚举类型，类型名car_state_t。
	CAR_STANDINGBY = 1,              //待定状态
	CAR_MOVING = 2,                  //行驶状态
	CAR_GOING_UP_AND_DOWN = 3,       //升降状态
	CAR_PREPARING_GETTING_BOOK = 4,  //升降准备状态
	CAR_WAITING_FOR_BOOK = 5,        //等待接书状态
	CAR_GETTING_BOOK = 6,            //接书整理状态
	CAR_RECOVERING = 7,              //正在复位状态
	CAR_TRACKING = 8,                //循迹状态
}car_state_t;

extern volatile car_order_t car_order;   //指令的枚举变量
extern volatile car_state_t car_state;   //状态的枚举变量

void BookCar_init();  //小车初始化函数
bool ceshi1();        //内箱第一层接书整理
bool ceshi2();        //内箱第二层接书整理

//每个函数对应一个指令
void Car_Stop();       //停止小车的一切动作
bool Car_recover();    //复位小车，将推书机构、压书机构和升降机构全部运动到原始位置
void Car_lift();       //内箱上升
void Car_descend();    //内箱下降
void Car_set_layer_1();//内箱下降到最低处，正好是第一层接书的位置
void Car_set_layer_2();//内箱运动到第二层接书的高度
bool Car_prepare_get_book();//内箱推书机构回到最左端，做好接书准备
bool Car_get_book();   //内箱接书整理
void Car_prepare_lift_and_down();//内箱推书机构向右移动一段距离，内箱准备升降
void Car_set_top();    //内箱上升到最高处
bool reach_botton();   //判断内箱是否在最低处，即原始位置
bool reach_top();      //判断内箱是否在最高处
bool can_lift_and_down(); //判断内箱是否可以升降（即升降准备指令是否执行了）
