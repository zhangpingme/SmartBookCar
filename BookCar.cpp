#include "BookCar.h"

int status;         //״̬��ʾ
int level;           //�㼶��ʾ
int number_1;   //�ϲ������Ŀ
int number_2;   //�²������Ŀ
long  time;        //����������ʱ��
int power;         //��ص���
int value;         //�洢��������������ֵ
bool finishLayer;       //�жϵ������Ƿ��Ѿ�����

void BookCar_init()               //�����ĳ�ʼ������
{
	pinMode(13, OUTPUT);
	StepMotor_Init();              //��ʼ�����еĲ������
	DrawstringEncoder_init();  //��ʼ������������
	BookDetect_init();            //���ϴ�������ʼ��
	Switch_init();                   //��λ���غ͵�ż̵�����ʼ��
	DCMotor_init();                //ֱ�������ʼ��
	SuperSonicInit();             //������ģ���ʼ��
	Track_init();                    //ѭ���ĺ���ģ���ʼ��
	Serial.begin(9600);          //��ʼ������
	//0��ʾ���ں�����Ҳ�ǳ����ʼ��������򣩣�1��ʾ�鳵�����˽�������������
	//2��ʾ�鳵�뿪������ǰ��ж����ж�ز�һֱ���ﵽ������
	status = 0;                      
	level = 0;                        //level��ʾ��Σ����status=0����levelΪ0��ʾ����װ�ϲ���飬Ϊ1��ʾ����װ�²����
	number_1 = 0;                
	number_2 = 0;               
	time = 0;                        //��ʼ����ʾ��ʽ��ʼ���ϰࡱ����¼�����ϰൽж�������ڼ������ʱ��

	LoadBook();                   //�鳵�Ӻ���ǰ��������
	while(true)
	{ 
		Track_forward();        //ѭ��
	}
	//���Ȼ��������½���ֱ������1����λ���أ�Ȼ��ֱ�����ֹͣ
	while (!Switch_1())
	{
		DCMotor_Big_Move(255, false);
	}
	DCMotor_Big_Stop(false);
	
	//Ȼ�����ϲ���������黬�鷴���˶���ֱ������2����ͣ�£����ͬʱ���ϲ��������黬�������˶�������5����ֹͣ
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
			StepMotor_1_Move(false, 1, StepMotor_High_Speed * 2);  //��2�Ա�֤���ش������ٶȱ仯����
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

	//Ȼ�����²���������黬�鷴���˶���ֱ������6����ͣ�£����ͬʱ���²��������黬�������˶�������9����ֹͣ
	delay(300);          //�˴���Ҫһ������ʱ
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

	//��ȡ��ǰ��С���ĵ����������͸��ֻ�APP
	power = getPower();

	Serial.println("The SmartBookCar is ready!");
	//�����źŸ��ּ�ϵͳ����ʾС���Ѿ�׼������

}

void BookCar_Move_Top()                //�ϲ�����к���
{
	while (!Switch_3())                      //�ȴ��ϲ���������������������֮��Ƕȱ仯
	{
		StepMotor_1_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	StepMotor_2_Move(false, wait_t2, StepMotor_High_Speed);   //�ϲ�Ĳ��黬�鷴���˶���ʹ֮ǰ��ѹ�鲿������
	while (!Switch_4())                      //�ȴ��ϲ���������������������֮�䷢����ײ����ʱ˵������������Ѿ���ֱ������
	{
		StepMotor_1_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	while (!Switch_5())                     //�ϲ�Ĳ��黬�������˶���ѹ��
	{
		StepMotor_2_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_2_Stop(false);          //�˴���false������true?��zhangping��
	Top_Sucker_Operate(true);       //�������ͨ�磬��������
	StepMotor_1_Move(false, wait_t3, StepMotor_High_Speed);
	Top_Sucker_Operate(false);      //������̶ϵ磬ʧȥ����
	while (!Switch_2())
	{
		StepMotor_1_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_1_Stop(false);
	number_1++;
	finishLayer = DistanceDetect(true);
}

void BookCar_Move_Bottom()           //�²�����к���
{
	while (!Switch_7())                      //�ȴ��ϲ���������������������֮��Ƕȱ仯
	{
		StepMotor_3_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	StepMotor_4_Move(false, wait_t2, StepMotor_High_Speed);   //�ϲ�Ĳ��黬�鷴���˶���ʹ֮ǰ��ѹ�鲿������
	while (!Switch_8())                      //�ȴ��ϲ���������������������֮�䷢����ײ����ʱ˵������������Ѿ���ֱ������
	{
		StepMotor_3_Move(true, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	while (!Switch_9())                     //�ϲ�Ĳ��黬�������˶���ѹ��
	{
		StepMotor_4_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_4_Stop(false);          //�˴���false������true?��zhangping��
	Bottom_Sucker_Operate(true);  //�������ͨ�磬��������
	StepMotor_3_Move(false, wait_t3, StepMotor_High_Speed);
	Bottom_Sucker_Operate(false); //������̶ϵ磬ʧȥ����
	while (!Switch_6())
	{
		StepMotor_3_Move(false, 1, StepMotor_High_Speed);
	}
	StepMotor_3_Stop(false);
	number_2++;
	finishLayer = DistanceDetect(false);
}

void ChangeLayer()                         //�ϡ��²�Ļ��㺯��
{
	value = ReadCount();
	while (!((ReadCount() - value)>3500))
	{
		//Serial.println(ReadCount() - value);
		DCMotor_Big_Move(Car_High_Speed, true);
	}
	DCMotor_Big_Stop(false);
}

void Rise()                                     //�²�װ����֮�󣬵ȴ���ť����ť������������������
{
	value = ReadCount();
	while (!((ReadCount() - value)>3500))
	{
		DCMotor_Big_Move(Car_High_Speed, true);
	}
	DCMotor_Big_Stop(false);
}

void ChangeCar()                           //������������һ�����Ѿ�װ����ǰ��ж����֮��׼��ж�أ���ʱ������
{
	//δд
}

bool BookCar_Control_Top()           //�ϲ�����п��ƺ���
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
	while (!Book_Detect()) {}               //�ȴ����ϴ���������Ƿ�������룬����У�������ѭ��
	delay(wait_t1);							    //�������󣬵Ⱥ�һ��ʱ�����������
	BookCar_Move_Top();
	return true;
}

bool BookCar_Control_Bottom()           //�²�����п��ƺ���
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
	while (!Book_Detect()) {}               //�ȴ����ϴ���������Ƿ�������룬����У�������ѭ��
	delay(wait_t1);							    //�������󣬵Ⱥ�һ��ʱ�����������
	BookCar_Move_Bottom();
	return true;
}

void BookCar_Operate()                     //���������п��ƺ���
{
	while (BookCar_Control_Top());
	while (BookCar_Control_Bottom());
	UnLoadBook();                             //�鳵ǰ��ж����
	while(Switch_10())                       //��������İ�ť���º�����������ȡ����֮���û��ٰ�һ�ΰ�ť�����临λ
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
	GoWait();                                 //�鳵ǰ������
	while (true)                              //�Ⱥ����ָ��
	{

	}
	LoadBook();                            //�鳵ǰ��������
}