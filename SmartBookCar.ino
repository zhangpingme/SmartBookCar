/*******************************************************************************
这个文件是Arduino工程的执行起点，包括两个函数。setup函数用于初始化小车，loop用于执行工作循环
*******************************************************************************/
#include "BookCar.h"

//初始化小车之后，立即停止小车的一切动作，防止出现意外，每次小车开启，上电之后，就立即执行这个函数，执行之后，就不再进入这个函数内。
void setup()
{
	BookCar_init();
	Car_Stop();
}
extern bool start;
//工作循环函数，所有的任务动作都在这个函数内完成，并一直往复执行下去，直到小车断电，程序终止，才会退出循环。
void loop()
{
	switch (car_order)  //使用状态机，car_order用于传递小车内部产生的或者来自外部的（比如手机端）的指令，然后用switch判断指令，并执行。
	{
		case CAR_STOP:   //停止指令。向手机控制端发送信息，并暂停小车的一切动作，该指令可以用于紧急停止小车及其他场合。
		{
			Car_Stop();
			esp8266_send("stop");//书车已停止();
		}break;
		case CAR_RECOVER:   //复位指令。向手机控制端发送信息，并复位小车。
		{
			esp8266_send("recover");//正在复位，请稍候……
			delay(500);
			Car_recover();
		}break;
		case CAR_PREPARE_LIFT_AND_DOWN:   //升降准备指令。向手机控制端发送信息，并准备执行内箱升降命令。               
		{                                 //（为保证安全，在内箱升降之前，原来在最左端初始位置的推书板需要向右移动一定距离，否则会导致内箱的推书板与外箱的铝型材碰撞）
			Car_prepare_lift_and_down();
		}break;
		case CAR_STANDBY: //待定指令。延时10微秒，然后再询问新指令。
		{
			delayMicroseconds(10);
		}break;
		case CAR_FWD: //前进指令。小车直线向前行驶，并修改小车的状态为CAR_MOVING。  
		{
			car_state = CAR_MOVING;
			go_straight();
		}break;
		case CAR_BKD: //后退指令。小车直线向后行驶，并修改小车的状态为CAR_MOVING。  
		{
			car_state = CAR_MOVING;
			go_back();
		}break;
		case CAR_LFD: //左转指令。小车向左转弯行驶，并修改小车的状态为CAR_MOVING。  
		{
			car_state = CAR_MOVING;
			small_left();
		}break;
		case CAR_RTD: //右转指令。小车向右转弯行驶，并修改小车的状态为CAR_MOVING。  
		{
			car_state = CAR_MOVING;
			small_right();
		}break;
		case CAR_LIFT: //上升指令。让内箱上升。
		{
			if (!can_lift_and_down()) //当小车已经准备好升降后，才可以让内箱上升，否则就先执行升降准备指令。
			{
				car_order = CAR_PREPARE_LIFT_AND_DOWN;
			}
			else if (!reach_top())    //当内箱没有升到最高位置前，内箱上升。
			{
				car_state = CAR_GOING_UP_AND_DOWN;
				DCMotor_Big_Move(255, 0);
			}
			else
			{
				car_order = CAR_STOP;
			}
		}break;
		case CAR_DESCEND: //下降指令。让内箱下降。
		{
			if (!can_lift_and_down()) //当小车已经准备好升降后，才可以让内箱下降，否则就先执行升降准备指令。
			{
				car_order = CAR_PREPARE_LIFT_AND_DOWN;
			}
			else if (!reach_botton())      //修改小车的状态为CAR_GOING_UP_AND_DOWN，内箱下降，直至遇到并触发下限位开关。
			{
				car_state = CAR_GOING_UP_AND_DOWN;
				DCMotor_Big_Move(255, 1);
			}
			else          //遇到下限位开关后，执行停止指令。
			{
				car_order = CAR_STOP;
			}
		}break;
		case CAR_PREPARE_GET_BOOK:      //准备接书指令，主动推书板向左移动，到达最左端，准备接书。  
		{
			esp8266_send("waitbook");//等待进书
			Car_prepare_get_book();
		}break;
		case CAR_GET_BOOK:    //接书整理指令	
		{
			esp8266_send("havebook");//正在码书！
			Car_get_book();
		}break;
		case CAR_AUTO_MOVE:    //循迹指令。设置小车的状态为循迹运行模式，使小车循黑线前进。
		{
			esp8266_send("tracking!");   //正在循迹前进
			car_state = CAR_TRACKING;
			Track_forward();
		}break;
		case CAR_AUTO_RUN:    //自动模式指令。暂停小车的动作，让小车进入自动运行模式。
		{
			car_order = CAR_STANDBY;
			if (!isAuto)
			{
				esp8266_send("Going to auto mode");
				isAuto = true;
				car_order = CAR_RECOVER;   //自动模式下，先复位，然后才是循迹等动作
			}
		}break;
		case CAR_SET_LAYER_1:     //下降到底指令。向手机控制端发送信息，并且让内箱下降到最低处，直到遇到底部的下限位开关停止。  
		{
			Car_set_layer_1();
			esp8266_send("layer_one");//下降到最底
		}break;
		case CAR_SET_LAYER_2:     //到达第二层指令。向手机控制端发送信息，并且让内箱上升到第二层接书处，使书从分拣系统中可以落到内箱第二层。  
		{
			Car_set_layer_2();
			esp8266_send("layer_two");//到达第二层
		}break;
		case CAR_SET_TOP:     //上升到顶指令。向手机控制端发送信息，并且让内箱上升到最高处，直到遇到顶部的上限位开关停止。  
		{
			Car_set_top();
			esp8266_send("at_top");//等待取书
		}break;
	}
}

