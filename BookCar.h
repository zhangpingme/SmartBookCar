#pragma once
#include "BookDetect.h"            //���ϴ�����������ͷ�ļ�
#include "DrawstringEncoder.h"  //����������ͷ�ļ�
#include "StepMotor.h"              //�������ͷ�ļ�
#include "Switch.h"                   //��λ���غ͵�ż̵���ͷ�ļ�
#include "DCMotor.h"                //���ӵ�����������������ֱ�������ͷ�ļ�
#include "CarPower.h"               //������ⵥԪͷ�ļ�
#include "Connect.h"                 //��ּ�ϵͳ���ֻ�APP��ͨ��ͷ�ļ�
#include "SuperSonic.h"            //������������ͷ�ļ�
#include "Tracking.h"                //С��ѭ��ͷ�ļ�

void BookCar_init();
void BookCar_Move_Top();
void BookCar_Move_Bottom();
bool BookCar_Control_Top();
bool BookCar_Control_Bottom();
void ChangeLayer();
void Rise();
void BookCar_Operate();