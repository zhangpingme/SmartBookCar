#pragma once
#include "Arduino.h"

/********************************************************************************
��һ���֣������궨��
*********************************************************************************/
#define Diameter_Pulley 15.66				//С���ֵ�ֱ��Ϊ15mm
#define Car_High_Speed 250					//С���������е��ٶ�
#define Car_HighMid_Speed    200			//С���и������е��ٶ�
#define Car_Mid_Speed    150					//С���������е��ٶ�
#define Car_LowMid_Speed    100			//С���е������е��ٶ�
#define Car_Low_Speed   50					//С���������е��ٶ�
#define wait_t1     500							//���ϴ�������֪���龭��t1ʱ�䣨�����������������黬�������˶�
#define wait_t2     1000							//�������黬�����յ���������������������֮��Ƕȼ����仯�����˶�ʱ�䣨��������
#define wait_t3     500                           //���������������������ڷ��̶��ʱ��֮�󣬵������ʧȥ���ԣ���������
#define StepMotor_High_Speed 500        //ÿ�������ʱ����2*500us��ȱ����Ť�غ�С���ŵ�����ʱ����
#define StepMotor_Medium_Speed 800   //ÿ�������ʱ����2*800us
#define StepMotor_LOW_Speed 1000		//ÿ�������ʱ����2*1ms
#define MinDistance  30                         //ÿ����ѹ����֮���ó������������룬��С����˵���ò�����
#define MinBookNumber  30                   //ÿ��������Ŀ��Сֵ

/********************************************************************************
�ڶ����֣�����ȷ��
*********************************************************************************/
//1�����ϴ�����
#define PinBookDetect A3    //���ϴ���������ɫ�߽�A3

//2������������
#define PinA 2      //��ɫ��A�࣬�����ű�����PWM���ţ���Mega2560��2~13����
#define PinB 53    //��ɫ��B��

//3���������A4988ģ��
#define StepMotor_1_STEP   26     //�������1���������
#define StepMotor_1_DIR   28      //�������1�ķ������
#define StepMotor_1_ENA 24       //�������1��ʹ�ܿ���
#define StepMotor_2_STEP   36    //2��
#define StepMotor_2_DIR   34      //2��
#define StepMotor_2_ENA 30        //2��
#define StepMotor_3_STEP    A6    //3��
#define StepMotor_3_DIR    A7      //3��
#define StepMotor_3_ENA   A2      //3��
#define StepMotor_4_STEP   46    //4��
#define StepMotor_4_DIR   48      //4��
#define StepMotor_4_ENA  A8      //4��

//4����λ���أ�����NO���Ž�����ĵ�Ƭ�����ţ����ص�COM���Ž�GND
#define switch_1_NO 23              //1�ſ��ذ�װ�ڻ������棬����ʱ����    
#define switch_2_NO 25              //2�ſ��ذ�װ�ϲ�����鵼���ϣ��������黬�鷴���˶�ʱ����    
#define switch_3_NO 27              //3�ſ��ذ�װ�ϲ������������������������Ӵ��ϣ�90��Ƕȼ����仯ʱ����   
#define switch_4_NO 29              //4�ſ��ذ�װ�ϲ����������������������м䣬�Ƕȼ�����Ϊ0��ʱ����    
#define switch_5_NO 31              //5�ſ��ذ�װ�ϲ������������ϣ���������鴥��    
#define switch_6_NO 32              //6�ſ��ذ�װ�²�����鵼���ϣ��������黬�鷴���˶�ʱ����   
#define switch_7_NO 33              //7�ſ��ذ�װ�²������������������������Ӵ��ϣ�90��Ƕȼ����仯ʱ����  
#define switch_8_NO 35              //8�ſ��ذ�װ�²����������������������м䣬�Ƕȼ�����Ϊ0��ʱ����   
#define switch_9_NO 37              //9�ſ��ذ�װ�²������������ϣ���������鴥��  
#define switch_10_NO A9            //10�ſ���Ϊ��ť����װ�鳵���ϲ�����ť����ΪGND���鳵�������������ٰ�һ���������½���ԭ��λ��ƫ��

//5��������̣���ż̵������ƣ�
#define Top_Sucker        49        //�����ϲ������̵ĵ�ż̵���
#define Bottom_Sucker     39      //�����²������̵ĵ�ż̵���

//6��ֱ�����
#define DC_Big_Pin1      40            //����ֱ�����ٵ��
#define DC_Big_Pin2      42   
#define DC_Big_ENA      3
#define DC_Left_Pin1     41            //���ֵ��
#define DC_Left_Pin2     43   
#define DC_Left_ENA     4
#define DC_Right_Pin1   45            //���ֵ��
#define DC_Right_Pin2   47
#define DC_Right_ENA   5

//7��������������
#define TrigPin_1  44
#define EchoPin_1 A4
#define TrigPin_2  6
#define EchoPin_2 A5

//8�����⴫����������ѭ����
#define hongwai_1 14
#define hongwai_2 15
#define hongwai_3 16






