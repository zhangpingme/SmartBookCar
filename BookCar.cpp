#include "BookCar.h"

int status;         //状态显示
int level;           //层级显示
int number_1;   //上层书的数目
int number_2;   //下层书的数目
long  time;        //连续工作的时间
int power;         //电池电量
int value;         //存储拉绳编码器的数值
bool finishLayer;       //判断单层书是否已经满了

void BookCar_init()               //整车的初始化函数
{
	pinMode(13, OUTPUT);
	StepMotor_Init();              //初始化所有的步进电机
	DrawstringEncoder_init();  //初始化拉绳编码器
	BookDetect_init();            //避障传感器初始化
	Switch_init();                   //限位开关和电磁继电器初始化
	DCMotor_init();                //直流电机初始化
	SuperSonicInit();             //超声波模块初始化
	Track_init();                    //循迹的红外模块初始化
	Serial.begin(9600);          //初始化串口
	//0表示正在候车区（也是程序初始化后的区域），1表示书车到达了接书区并工作，
	//2表示书车离开接书区前往卸载区卸载并一直到达到候车区。
	status = 0;                      
	level = 0;                        //level表示层次，如果status=0，则level为0表示正在装上层的书，为1表示正在装下层的书
	number_1 = 0;                
	number_2 = 0;               
	time = 0;                        //初始化表示正式开始“上班”，记录本次上班到卸载书这期间的所有时间

	LoadBook();                   //书车从候车区前往接书区
	while(true)
	{ 
		Track_forward();        //循迹
	}
	//首先机器内箱下降，直到碰到1号限位开关，然后直流电机停止
	while (!Switch_1())
	{
		DCMotor_Big_Move(255, false);
	}
	DCMotor_Big_Stop(false);
	
	//然后是上层的主动推书滑块反向运动，直到触碰2开关停下，与此同时，上层主动拨书滑块正向运动，触动5开关停止
	while ((!Switch_2()) && (!Switch_5()))
	{
		StepMotor_1_Move(false, 1, StepMotor_High_Speed);
		StepMotor_2_Move(true, 1, StepMotor_High_Speed);
	}
	if (!Switch_2())
	{
		StepMotor_2_Stop(false);
		while (!Switch_2())
		{
			StepMotor_1_Move(false, 1, StepMotor_High_Speed * 2);  //乘2以保证开关触发后，速度变化不大
		}
		StepMotor_1_Stop(false);
	}
	else
	{
		StepMotor_1_Stop(false);
		while (!Switch_5())
		{
			StepMotor_2_Move(true, 1, StepMotor_High_Speed * 2);
		}
		StepMotor_2_Stop(false);
	}

	//然后是下层的主动推书滑块反向运动，直到触碰6开关停下，与此同时，下层主动拨书滑块正向运动，触动9开关停止
	delay(300);          //此处需要一定的延时
	while ((!Switch_6()) && (!Switch_9()))
	{
		StepMotor_3_Move(false, 1, StepMotor_High_Speed);
		StepMotor_4_Move(true, 1, StepMotor_High_Speed);
	}
	if (!Switch_6())
	{
		StepMotor_4_Stop(false);
		while (!Switch_6())
		{
			StepMotor_3_Move(false, 1, StepMotor_High_Speed * 2);
		}
		StepMotor_3_Stop(false);
	}
	else
	{
		StepMotor_3_Stop(false);
		while (!Switch_9())
		{
			StepMotor_4_Move(true, 1, StepMotor_High_Speed * 2);
		}
		StepMotor_4_Stop(false);
	}

	//获取当前的小车的电量，并传送给手机APP
	power = getPower();

	Serial.println("The SmartBookCar is ready!");
	//发送信号给分拣系统，表示小车已经准备就绪

}

void BookCar_Move_Top()                //上层的运行函数
{
	while (!Switch_3())                      //等待上层的主动推书板和主动推书杆之间角度变化
	{
		StepMotor_1_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	StepMotor_2_Move(false, wait_t2, StepMotor_High_Speed);   //上层的拨书滑块反向运动，使之前的压书部分脱离
	while (!Switch_4())                      //等待上层的主动推书板和主动推书杆之间发生碰撞，此时说明主动推书板已经竖直立起了
	{
		StepMotor_1_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	while (!Switch_5())                     //上层的拨书滑块正向运动，压书
	{
		StepMotor_2_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_2_Stop(false);          //此处用false还是用true?（zhangping）
	Top_Sucker_Operate(true);       //电磁吸盘通电，产生磁性
	StepMotor_1_Move(false, wait_t3, StepMotor_High_Speed);
	Top_Sucker_Operate(false);      //电磁吸盘断电，失去磁性
	while (!Switch_2())
	{
		StepMotor_1_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	number_1++;
	finishLayer = DistanceDetect(true);
}

void BookCar_Move_Bottom()           //下层的运行函数
{
	while (!Switch_7())                      //等待上层的主动推书板和主动推书杆之间角度变化
	{
		StepMotor_3_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	StepMotor_4_Move(false, wait_t2, StepMotor_High_Speed);   //上层的拨书滑块反向运动，使之前的压书部分脱离
	while (!Switch_8())                      //等待上层的主动推书板和主动推书杆之间发生碰撞，此时说明主动推书板已经竖直立起了
	{
		StepMotor_3_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	while (!Switch_9())                     //上层的拨书滑块正向运动，压书
	{
		StepMotor_4_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_4_Stop(false);          //此处用false还是用true?（zhangping）
	Bottom_Sucker_Operate(true);  //电磁吸盘通电，产生磁性
	StepMotor_3_Move(false, wait_t3, StepMotor_High_Speed);
	Bottom_Sucker_Operate(false); //电磁吸盘断电，失去磁性
	while (!Switch_6())
	{
		StepMotor_3_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	number_2++;
	finishLayer = DistanceDetect(false);
}

void ChangeLayer()                         //上、下层的换层函数
{
	value = ReadCount();
	while (!((ReadCount() - value)>3500))
	{
		//Serial.println(ReadCount() - value);
		DCMotor_Big_Move(Car_High_Speed, true);
	}
	DCMotor_Big_Stop(false);
}

void Rise()                                     //下层装满书之后，等待按钮，按钮按下则内箱内箱上升
{
	value = ReadCount();
	while (!((ReadCount() - value)>3500))
	{
		DCMotor_Big_Move(Car_High_Speed, true);
	}
	DCMotor_Big_Stop(false);
}

void ChangeCar()                           //换车函数，当一个车已经装满，前往卸载区之后，准备卸载，此时候车区的
{
	//未写
}

bool BookCar_Control_Top()           //上层的运行控制函数
{
	if (number_1 == MinBookNumber)
	{
		if (finishLayer == true)
		{
			Serial.println("Top layer is full!");
			level = 1;
			ChangeLayer();
			return false;
		}
	}
	while (!Book_Detect()) {}               //等待避障传感器检测是否有书进入，如果有，则跳出循环
	delay(wait_t1);							    //有书进入后，等候一定时间启动推书板
	BookCar_Move_Top();
	return true;
}

bool BookCar_Control_Bottom()           //下层的运行控制函数
{
	if (number_2 == MinBookNumber)
	{
		if (finishLayer == true)
		{
			Serial.println("Bottom layer is full!");
			Serial.println("The car is full!");
			return false;
		}
	}
	while (!Book_Detect()) {}               //等待避障传感器检测是否有书进入，如果有，则跳出循环
	delay(wait_t1);							    //有书进入后，等候一定时间启动推书板
	BookCar_Move_Bottom();
	return true;
}

void BookCar_Operate()                     //整车的运行控制函数
{
	while (BookCar_Control_Top());
	while (BookCar_Control_Bottom());
	UnLoadBook();                             //书车前往卸载区
	while(Switch_10())                       //升起内箱的按钮按下后，内箱上升，取完书之后，用户再按一次按钮，内箱复位
	{
		Rise();
	}
	while (!Switch_10())                      
	{
		while (!Switch_1())
		{
			DCMotor_Big_Move(255, false);
		}
		DCMotor_Big_Move(255, true);
		delay(200);
		DCMotor_Big_Stop(false);
	}
	GoWait();                                 //书车前往候车区
	while (true)                              //等候接书指令
	{

	}
	LoadBook();                            //书车前往接书区
}