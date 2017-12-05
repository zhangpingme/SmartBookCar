#include "BookCar.h"
#include "Arduino.h"
#include "DrawstringEncoder.h"
    
int number_1;  //内箱第一层接到书的数目
int number_2;  //内箱第二层接到书的数目            
bool isAuto=false;  //设定小车初始时刻模式为手动控制模式

volatile car_order_t car_order=CAR_STANDBY;    //设定小车初始时刻指令为待定指令
volatile car_state_t car_state=CAR_STANDINGBY;    //设定小车初始时刻状态为待定状态

void checkUart()   //检测串口信息
{
	receive_com_data(Com1);   //接收外部传到串口1处的字符串，并将其保存在结构体Com1的buf中
	if(Book_Detect())         //如果检测到有书进入小车，则检测内箱的压书机构是否做好了接书准备，如果做好，则发送接书整理指令
	{
		if(car_state==CAR_WAITING_FOR_BOOK)
		{
			car_order=CAR_GET_BOOK;
		}
	}
	if (Com1.end_flag)        //如果字符串已经接收完全
	{
		Com1.end_flag = 0;
		/**
		   手机控制端通过WiFi将指令以字符串的形式发送给ESP8266，后者是一种串口转WiFi模块，ESP8266连接的是串口1，
		   单片机将串口1收到的字符串与事先设置好的字符串进行比对，相当于解析字符串指令，然后执行手机控制端发来的指令
		 */
		if (strcmp(Com1.buf, "STP") == 0)
		{
			//小车停止一切运动，并将模式设置为手动控制
			car_order=CAR_STOP;
			isAuto = false;
		}
		else if (strcmp(Com1.buf, "FWD") == 0)
		{
			//小车前进
			car_order=CAR_FWD;
		}
		else if (strcmp(Com1.buf, "BKD") == 0)
		{
			//小车后退
			car_order=CAR_BKD;
		}
		else if (strcmp(Com1.buf, "LFD") == 0)
		{
			//小车左转
			car_order=CAR_LFD;
		}
		else if (strcmp(Com1.buf, "RTD") == 0)
		{
			//小车右转
			car_order=CAR_RTD;
		}
		else if (strcmp(Com1.buf, "LIFT") == 0)
		{
			//内箱上升
			car_order=CAR_LIFT;
		}
		else if (strcmp(Com1.buf, "DWN") == 0)
		{
			//内箱下降
			car_order=CAR_DESCEND;
		}
		else if (strcmp(Com1.buf, "TST") == 0)
		{
			//准备接书指令，让推书机构向左移动到原始位置，到达分拣系统的出书口正下方，准备接书
			car_order=CAR_PREPARE_GET_BOOK;
		}
		else if (strcmp(Com1.buf, "TRACK") == 0)
		{
			//循迹指令，让小车循黑线前往分拣系统处接书
			car_order = CAR_AUTO_MOVE;
		}
		else if (strcmp(Com1.buf, "AUTO") == 0)
		{
			//自动模式指令，让小车切换到自动模式
			esp8266_send("AUTO");     //通过串口1向手机控制端发送字符串
			car_order = CAR_AUTO_RUN;
		}
		else if (strcmp(Com1.buf, "SECOND") == 0)
		{
			//到达第二层指令
			esp8266_send("SECOND");   //通过串口1向手机控制端发送字符串
			car_order = CAR_SET_LAYER_2;
		}
		else if (strcmp(Com1.buf, "LTOP") == 0)
		{
			//内箱上升到顶指令
			esp8266_send("LTOP");     //通过串口1向手机控制端发送字符串
			car_order = CAR_SET_TOP;
		}
		else if (strcmp(Com1.buf, "DBTM") == 0)
		{
			//内箱下降到底指令
			esp8266_send("DBTM");     //通过串口1向手机控制端发送字符串
			car_order = CAR_SET_LAYER_1;
		}
	}
}
void BookCar_init()          //初始化小车
{
	StepMotor_Init();        //步进电机的初始化。步进电机用在内箱中，用于驱动推书、压书机构。
	DrawstringEncoder_init();//拉绳编码器的初始化。拉绳编码器用于检测内箱与外箱之间的距离，主要用于判断内箱是否达到第二层接书位置。
	BookDetect_init();       //避障传感器的初始化。避障传感器用于检测是否有书进入小车内。
	Switch_init();           //各开关和电磁吸盘的初始化。
	DCMotor_init();          //直流电机的初始化。包括驱动升降机构和驱动轮子的直流电机。
	Track_init();            //红外传感器的初始化。红外传感器用于小车循迹。
	Serial.begin(115200);    //串口0的初始化，用于调试。

	esp8266_init();          //ESP8266串口转WiFi模块的初始化。该模块用于手机连接WiFi，将指令发送给单片机。
	MsTimer2::set(1, checkUart);    //设置定时器2，每隔1ms检测一下串口信息
	MsTimer2::start();       //开启定时器2
                 
	number_1 = 0;            //设置内箱第一层接书数目为0     
	number_2 = 0;            //设置内箱第二层接书数目为0                                        
	esp8266_send("The SmartBookCar is ready!");
}

bool start = true;    //用来判断正在工作的内箱层数，如果正在接书的是第一层，则start=true，如果是第二层，则start=false。
bool ceshi1()         //内箱第一层接书整理过程
{
	if(number_1>=Max_number_1) //第一步，判断内箱第一层书是否已满，如果满，则返回true，不执行这个函数
	{
		start=false;
		return true;
	}
	while (!Switch_5())        //第二步，如果内箱第一层书没有满，其压书机构向右运动，复位，直到将已有书压紧
	{
		StepMotor_2_Move(true, 1, StepMotor_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_2_Stop(true);
	while (Switch_3())         //第三步，内箱第一层的推书机构向右运动，直到书碰到阻碍，导致推书板和连杆之间的角度变化
	{
		StepMotor_1_Move(false, 1, StepMotor57_Medium_Speed / 4);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_1_Stop(true);    
	for (int i = 0; i<wait_t2; i++)   //第四步，内箱第一层的压书机构向左运动一定距离
	{
		StepMotor_2_Move(false, 1, StepMotor_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	for (int i = 0; i<wait_t4; i++)   //第五步，内箱第一层的推书机构继续向右运动一定距离，将书推到竖直状态
	{
		StepMotor_1_Move(false, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_1_Stop(true);
	Top_Sucker_Operate(true);         //第六步，内箱第一层推书机构的电磁吸盘通电产生磁性，推书板和连杆贴紧，推书板与水平面呈90度
	
	while (!Switch_5())               //第七步，内箱第一层压书机构向右运动，直至将书压紧
	{
		StepMotor_2_Move(true, 1, StepMotor_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_2_Stop(true);
	for (int i = 0; i<2 * wait_t4; i++)   //第八步，内箱的第一层推书板向左移动一定距离
	{
		StepMotor_1_Move(true, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
		if (Switch_2())                   //如果在此过程中触发了开关2，则断开电磁吸盘
		{
			Top_Sucker_Operate(false);
			return true;
		}
	}
	Top_Sucker_Operate(false);      //第九步，内箱的第一层电磁吸盘断电，主动推书板和连杆之间不再贴紧，在弹簧合页作用下，推书板与水平面呈45°
	while (!Switch_2())             //第十步，内箱的第一层推书板向左移动，回到初始位置，等待下一次接书
	{
		StepMotor_1_Move(true, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}

	number_1++;          //书整理完毕后，内箱第一层书增加一本
	if(number_1>=Max_number_1) //判断内箱第一层书是否已满
	{
		esp8266_send("Layer one full!");
		start=false;
	}
	return true;
}

bool ceshi2()         //内箱第二层接书整理过程				                   
{
	if(number_2>=Max_number_2) //第一步，判断内箱第二层书是否已满，如果满，则返回true，不执行这个函数
	{
		start=true;
		return true;
	}
	while (!Switch_9())        //第二步，如果内箱第二层书没有满，其压书机构向右运动，复位，直到将已有书压紧                    
	{
		StepMotor_4_Move(true, 1, StepMotor_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_4_Stop(true);   
	while (Switch_7())         //第三步，内箱第二层的推书机构向右运动，直到书碰到阻碍，导致推书板和连杆之间的角度变化
	{
		StepMotor_3_Move(false, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_3_Stop(true);
	for(int i=0;i<wait_t2;i++) //第四步，内箱第二层的压书机构向左运动一定距离
	{
		StepMotor_4_Move(false, 1, StepMotor_Medium_Speed)
		if (car_order == CAR_STOP)
			return false;
	}
	for(int i=0;i<wait_t4;i++)  //第五步，内箱第二层的推书机构继续向右运动一定距离，将书推到竖直状态
	{
		StepMotor_3_Move(false, 1, StepMotor57_Medium_Speed);
	}
	StepMotor_3_Stop(true);
	Bottom_Sucker_Operate(true);//第六步，内箱第二层推书机构的电磁吸盘通电产生磁性，推书板和连杆贴紧，推书板与水平面呈90度
	while (!Switch_9())         //第七步，内箱第二层压书机构向右运动，直至将书压紧             
	{
		StepMotor_4_Move(true, 1, StepMotor_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	StepMotor_4_Stop(true);
	for (int i = 0; i<2 * wait_t4; i++)   //第八步，内箱的第二层推书板向左移动一定距离
	{
		StepMotor_3_Move(true, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
		if (Switch_6())                   //如果在此过程中触发了开关6，则断开电磁吸盘
		{
			Top_Sucker_Operate(false);
			return true;
		}
	}
	Bottom_Sucker_Operate(false);    //第九步，内箱的第二层电磁吸盘断电，主动推书板和连杆之间不再贴紧，在弹簧合页作用下，推书板与水平面呈45°
	while(!Switch_6())               //第十步，内箱的第二层推书板向左移动，回到初始位置，等待下一次接书
	{
		StepMotor_3_Move(true, 1, StepMotor57_Medium_Speed);
		if (car_order == CAR_STOP)
			return false;
	}
	start = 0;
	number_2++;          //书整理完毕后，内箱第二层书增加一本
	if(number_2>=Max_number_2) //第一步，判断内箱第二层书是否已满，如果满，则返回true，不执行这个函数
	{
		Serial.println("Layer two full!");
		start=true;
	}
	return true;
}

void Car_prepare_lift_and_down()   //内箱升降准备
{
	if(!can_lift_and_down())       //如果内箱没有做好升降准备工作，不能升降，则执行下面的函数
	{
		int step=5000;
		while(step--)              //升降前，内箱第一层和第二层的推书机构均向右移动一定距离，防止升降与外箱的铝型材干涉
		{
			StepMotor_1_Move(false, 1, StepMotor57_Medium_Speed/2);
			StepMotor_3_Move(false, 1, StepMotor57_Medium_Speed/2);
		}
	}
}

bool Car_recover()                 //小车复位
{
	car_state=CAR_RECOVERING;      //将小车状态设置为正在复位
	int tmp=0;                     //用于记录复位进程到哪一步
	while(car_order!=CAR_STOP)
	{
		if(!Switch_5())            //内箱第一层的压书机构向右移动，直至压紧书或者与内箱右壁接触
			StepMotor_2_Move(true, 1, StepMotor_Medium_Speed);
		else
			tmp |=0x01;
		if(!Switch_9())            //内箱第二层的压书机构向右移动，直至压紧书或者与内箱右壁接触
			StepMotor_4_Move(true, 1, StepMotor_Medium_Speed);
		else
			tmp |=0x02;
		if(!Switch_2())            //内箱第一层的推书机构向左移动，直至推书板复位到最左端
			StepMotor_1_Move(true, 1, StepMotor57_Medium_Speed/2);
		else
			tmp |=0x04;
		if(!Switch_6())            //内箱第二层的推书机构向左移动，直至推书板复位到最左端
			StepMotor_3_Move(true, 1, StepMotor57_Medium_Speed/2);
		else
			tmp |=0x08;
		if(tmp==0x0f)
			break;
	}
	int step=10000;
	while(car_order!=CAR_STOP && step--)  //推书机构向右移动一定距离，防止内箱升降时，推书机构与外箱铝型材碰撞
	{
		StepMotor_1_Move(false, 1, StepMotor57_Medium_Speed/2);
		StepMotor_3_Move(false, 1, StepMotor57_Medium_Speed/2);
	}
	while(car_order!=CAR_STOP && ! reach_botton()) //内箱下降到最低位置处
	{
		DCMotor_Big_Move(255, 1);
	}
	count = 0;
	DCMotor_Big_Stop(true);
	car_state=CAR_STANDINGBY;
	if (isAuto)  //如果是自动模式，则复位完成后，立即进入循迹前进环节
	{
		esp8266_send("recover finished.");
		delay(500);
		car_order = CAR_AUTO_MOVE;
	}
	return true;
}

void Car_Stop()      //停止小车，停止升降直流电机和驱动车轮的直流电机的运行
{
	car_state = CAR_STANDINGBY;  //设置小车状态为待定
	car_order = CAR_STANDBY;     //发送待定指令
	DCMotor_Left_Stop(false);
	DCMotor_Right_Stop(false);
	DCMotor_Big_Stop(true);
}

bool reach_botton()  //判断内箱是否位于最低位置，如果在最低位置，则返回true，否则返回false
{
	return (Switch_10()==false);
}

bool reach_top()    //判断内箱是否位于最高位置，如果在最高位置，则返回true，否则返回false
{
	return (Switch_12() == false);
}

bool can_lift_and_down()  //判断当前状态是否可以让内箱升降，如果开关2或者开关6闭合，
{                         //说明至少有一个推书板在左侧初始位置，不能执行升降动作。
	if(Switch_2() || Switch_6())
		return false;
	return true;
}

bool Car_prepare_get_book()   //准备接书整理函数
{
	int tmp=0;
	car_state=CAR_PREPARING_GETTING_BOOK;
	car_order = CAR_STANDBY;
	while(car_order!=CAR_STOP)
	{
		if(!Switch_2())
			StepMotor_1_Move(true, 1, StepMotor57_Medium_Speed/2);
		else
			tmp |=0x01;
		if(!Switch_6())
			StepMotor_3_Move(true, 1, StepMotor57_Medium_Speed/2);
		else
			tmp |=0x02;
		if(tmp==0x03)
			break;
	}
	if(car_order==CAR_STOP)
		return false;
	if (isAuto)  //如果是自动模式，则准备完成后，立即进入接书整理环节
	{
		esp8266_send("waiting for book!");
		car_order = CAR_GET_BOOK;
	}
	car_state = CAR_WAITING_FOR_BOOK;
	return true;
}

bool Car_get_book()    //内箱接书、整理书的函数，也是本程序的核心
{
	car_order = CAR_STANDBY;
	if(car_state==CAR_WAITING_FOR_BOOK)
	{
		car_state=CAR_GETTING_BOOK;
		for(int i=0;i<800;i++)
		{
			if(car_order==CAR_STOP)
				return false;
			delay(1);
		}
		if(ceshi1()&&start==true)
		{
			car_state=CAR_WAITING_FOR_BOOK;
			return true;
		}
		else if(ceshi1()&&start==false)
		{
			car_state=CAR_WAITING_FOR_BOOK;
			return true;
		}
	}
	return false;
}

void Car_set_layer_1()      //内箱下降到底函数
{
	Car_prepare_lift_and_down();
	car_state = CAR_GOING_UP_AND_DOWN;
	while (car_order != CAR_STOP && !reach_botton())
	{
		DCMotor_Big_Move(255, 1);
	}
	DCMotor_Big_Stop(false);
	car_state = CAR_STANDINGBY;
	car_order = CAR_STANDBY;
}

void Car_set_layer_2()      //内箱到达第二层函数
{
	Car_prepare_lift_and_down();
	car_state = CAR_GOING_UP_AND_DOWN;
	Car_set_layer_1();     //内箱必须先到达最低位置，然后再往上升，用拉绳编码器的值来确定高度值
	int a=count;           //内箱从最低位置上升到第二层位置，大约经过1789个拉绳编码器脉冲
	while(abs(count-1789-a)>20)
	{
		DCMotor_Big_Move(255,0);
	}
	DCMotor_Big_Stop(false);
	car_state = CAR_STANDINGBY;
	car_order = CAR_STANDBY;
}

void Car_set_top()      //内箱上升到顶函数
{
	Car_prepare_lift_and_down();
	car_state = CAR_GOING_UP_AND_DOWN;
	while (car_order != CAR_STOP && !reach_top())
	{
		DCMotor_Big_Move(255, 0);
	}
	DCMotor_Big_Stop(false);
	car_state = CAR_STANDINGBY;
	car_order = CAR_STANDBY;
}