#pragma once
#include "Arduino.h"

/********************************************************************************
第一部分：参数宏定义
*********************************************************************************/
#define Diameter_Pulley 15.66				//小带轮的直径为15mm
#define Car_High_Speed 250					//小车高速运行的速度
#define Car_HighMid_Speed    200			//小车中高速运行的速度
#define Car_Mid_Speed    150					//小车中速运行的速度
#define Car_LowMid_Speed    100			//小车中低速运行的速度
#define Car_Low_Speed   50					//小车低速运行的速度
#define wait_t1     500							//避障传感器感知到书经过t1时间（毫秒数）后，主动推书滑块正向运动
#define wait_t2     1000							//主动拨书滑块在收到主动推书板与主动推书杆之间角度即将变化后反向运动时间（脉冲数）
#define wait_t3     500                           //主动推书板与主动推书杆在返程多久时间之后，电磁吸盘失去磁性（脉冲数）
#define StepMotor_High_Speed 500        //每个脉冲的时间是2*500us，缺点是扭矩很小，优点是用时很少
#define StepMotor_Medium_Speed 800   //每个脉冲的时间是2*800us
#define StepMotor_LOW_Speed 1000		//每个脉冲的时间是2*1ms
#define MinDistance  30                         //每本书压紧好之后，用超声波测量距离，过小，则说明该层已满
#define MinBookNumber  30                   //每层的书的数目最小值

/********************************************************************************
第二部分：引脚确定
*********************************************************************************/
//1、避障传感器
#define PinBookDetect A3    //避障传感器的蓝色线接A3

//2、拉绳编码器
#define PinA 2      //绿色，A相，该引脚必须是PWM引脚，即Mega2560的2~13引脚
#define PinB 53    //白色，B相

//3、步进电机A4988模块
#define StepMotor_1_STEP   26     //步进电机1的脉冲控制
#define StepMotor_1_DIR   28      //步进电机1的方向控制
#define StepMotor_1_ENA 24       //步进电机1的使能控制
#define StepMotor_2_STEP   36    //2号
#define StepMotor_2_DIR   34      //2号
#define StepMotor_2_ENA 30        //2号
#define StepMotor_3_STEP    A6    //3号
#define StepMotor_3_DIR    A7      //3号
#define StepMotor_3_ENA   A2      //3号
#define StepMotor_4_STEP   46    //4号
#define StepMotor_4_DIR   48      //4号
#define StepMotor_4_ENA  A8      //4号

//4、限位开关，常开NO引脚接下面的单片机引脚，开关的COM引脚接GND
#define switch_1_NO 23              //1号开关安装在机器下面，升降时触碰    
#define switch_2_NO 25              //2号开关安装上层的推书导轨上，主动推书滑块反向运动时触碰    
#define switch_3_NO 27              //3号开关安装上层的主动推书板和主动推书杆连接处上，90°角度即将变化时触碰   
#define switch_4_NO 29              //4号开关安装上层的主动推书板和主动推书杆中间，角度即将变为0°时触碰    
#define switch_5_NO 31              //5号开关安装上层的主动拨书板上，拨书板与书触碰    
#define switch_6_NO 32              //6号开关安装下层的推书导轨上，主动推书滑块反向运动时触碰   
#define switch_7_NO 33              //7号开关安装下层的主动推书板和主动推书杆连接处上，90°角度即将变化时触碰  
#define switch_8_NO 35              //8号开关安装下层的主动推书板和主动推书杆中间，角度即将变为0°时触碰   
#define switch_9_NO 37              //9号开关安装下层的主动拨书板上，拨书板与书触碰  
#define switch_10_NO A9            //10号开关为按钮，安装书车最上部，按钮按下为GND，书车的内箱上升，再按一下则内箱下降到原点位置偏上

//5、电磁吸盘（电磁继电器控制）
#define Top_Sucker        49        //控制上层电磁吸盘的电磁继电器
#define Bottom_Sucker     39      //控制下层电磁吸盘的电磁继电器

//6、直流电机
#define DC_Big_Pin1      40            //升降直流减速电机
#define DC_Big_Pin2      42   
#define DC_Big_ENA      3
#define DC_Left_Pin1     41            //左轮电机
#define DC_Left_Pin2     43   
#define DC_Left_ENA     4
#define DC_Right_Pin1   45            //右轮电机
#define DC_Right_Pin2   47
#define DC_Right_ENA   5

//7、超声波传感器
#define TrigPin_1  44
#define EchoPin_1 A4
#define TrigPin_2  6
#define EchoPin_2 A5

//8、红外传感器（用于循迹）
#define hongwai_1 14
#define hongwai_2 15
#define hongwai_3 16






