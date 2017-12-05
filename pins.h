#pragma once
#include "Arduino.h"

/********************************************************************************
小车参数的常量宏定义
*********************************************************************************/	
#define Car_High_Speed 250					
#define Car_HighMid_Speed    200			
#define Car_Mid_Speed    150					
#define Car_LowMid_Speed    100			
#define Car_Low_Speed   50											
#define wait_t2     1000							                           
#define wait_t4     13100                           
#define StepMotor_High_Speed 500        
#define StepMotor_Medium_Speed 800   
#define StepMotor_LOW_Speed 1000		
#define StepMotor57_High_Speed 10        
#define StepMotor57_Medium_Speed 20   
#define StepMotor57_LOW_Speed 60		             

/********************************************************************************
引脚的定义
*********************************************************************************/
//检测书本进入小车的避障传感器的输入引脚
#define PinBookDetect A3    
//检测内箱上升高度的拉绳编码器输入引脚
#define PinA 2      
#define PinB 53    

//内箱中四个步进电机的脉冲STEP、方向DIR、使能ENA控制引脚
#define StepMotor_1_STEP   26         //步进电机1驱动第一层的推书机构
#define StepMotor_1_DIR   28      
#define StepMotor_1_ENA 24       
#define StepMotor_2_STEP   36         //步进电机2驱动第一层的压书机构
#define StepMotor_2_DIR   34      
#define StepMotor_2_ENA 30        
#define StepMotor_3_STEP    A6        //步进电机3驱动第二层的推书机构
#define StepMotor_3_DIR    A7      
#define StepMotor_3_ENA   A2      
#define StepMotor_4_STEP   46         //步进电机4驱动第二层的压书机构
#define StepMotor_4_DIR   48      
#define StepMotor_4_ENA  A8      

//10个开关的触发引脚
#define switch_2_NO 25        //2号开关安装在内箱第一层最左端，检测第一层推书机构是否在初始位置        
#define switch_3_NO 27        //3号开关安装在内箱第一层推书板与连杆之间，检测推书板的倾斜角度               
#define switch_5_NO 31        //5号开关安装在内箱第一层压书机构的右侧，用于检测内箱第一层压书机构是否将书已经压紧或与内箱右壁接触        
#define switch_6_NO 32        //6号开关安装在内箱第二层最左端，检测第二层推书机构是否在初始位置               
#define switch_7_NO 33        //7号开关安装在内箱第二层推书板与连杆之间，检测推书板的倾斜角度                
#define switch_9_NO 37        //9号开关安装在内箱第二层压书机构的右侧，用于检测内箱第二层压书机构是否将书已经压紧或与内箱右壁接触                  
#define switch_10_NO A9       //10号开关安装在内箱行程的最低处，用于检测内箱是否下降到最低位置
#define switch_12_NO 6        //12号开关安装在内箱行程的最高处，用于检测内箱是否上升到最高位置

//电磁吸盘通断电控制引脚，Top为内箱第二层的推书机构中的电磁吸盘，Bottom为内箱第一层的推书机构中的电磁吸盘。
#define Top_Sucker        49        
#define Bottom_Sucker     39      

//直流电机的控制引脚，DC_Big为驱动内箱升降的直流电机，DC_Left为驱动左轮的直流电机，DC_Right为驱动右轮的直流电机
#define DC_Big_Pin1      40            
#define DC_Big_Pin2      42   
#define DC_Big_ENA      3
#define DC_Left_Pin1     41            
#define DC_Left_Pin2     43   
#define DC_Left_ENA     4
#define DC_Right_Pin1   45            
#define DC_Right_Pin2   47
#define DC_Right_ENA   5

//5个红外传感器的检测引脚
#define hongwai_2 15
#define hongwai_3 16
#define hongwai_4 17
#define hongwai_5 20
#define hongwai_6 21