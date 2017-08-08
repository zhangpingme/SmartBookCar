#pragma once
#include "pins.h"
void StepMotor_Init();
void StepMotor_1_Move(bool DIR, int num, int speed);
void StepMotor_2_Move(bool DIR, int num, int speed);
void StepMotor_3_Move(bool DIR, int num, int speed);
void StepMotor_4_Move(bool DIR, int num, int speed);
void StepMotor_1_Stop(bool flag);
void StepMotor_2_Stop(bool flag);
void StepMotor_3_Stop(bool flag);
void StepMotor_4_Stop(bool flag);

