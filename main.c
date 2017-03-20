

//--包含你要使用的头文件--//
#include <reg52.h>	   //此文件中定义了51的一些特殊功能寄存器
#include "number.h"
#include <intrins.h>

sbit BEEP = P1^3;
sbit RX=P1^1;
sbit TX=P1^0;
int overNum;     //计时溢出次数
//--声明全局函数--//
void Delay(unsigned int c);   //延时10ms

void Conut(long*S);
 /************************************* */ 
/* 函数名称: Init_Timer */
/* 函数说明：初始化定时器 */
/* 参 数: void */ 
/* 返 回 值: void */ 
/* 使用示例：Init_Timer() */ 
/************************************* */ 
void Init_Timer(void);



void main()
{ 
    long S;
    long i = 0;
    Init_Timer();
    showDistance(0000);
    BEEP = 0;
    Delay(100);
    BEEP = 1;
    Delay(100);
    BEEP = 0;
    //TR0= 0;

    while(1)
    {
        //showDistance(0);
        LABEL1:
        TX=1;			                //800MS  启动一次模块
        for (i=0;i<15;i++)
            _nop_(); 

        TX=0;
        //BEEP = 1;
        i= 0;
        while(!RX)
        {
            i++;
            if(i > 30000)
                goto  LABEL1;
        }
        //当RX为零时等待
        TR1=1;			    //开启计数
        i= 0;
        while(RX)
        {
        }
        //当RX为1计数并等待
        TR1=0;				//关闭计数
        Conut(&S);			//计算
        TR0 = 0;
        showDistance(S);
        TR0 = 1;
        Delay(200);
        // BEEP = 0;
        //  BEEP = ~BEEP;
    }

}


//************************************
// 函数名称: Delay     
// 函数说明：   
// 参    数: unsigned int c
// 返 回 值: void     
// 使用示例：Delay()
//************************************
void Delay(unsigned int c)   //误差 0us
{
    unsigned char a, b;

    //--c已经在传递过来的时候已经赋值了，所以在for语句第一句就不用赋值了--//
    for (;c>0;c--)
    {
        for (b=38;b>0;b--)
        {
            for (a=130;a>0;a--);
        }

    }

}


//************************************
// 函数名称: Conut     
// 函数说明：   
// 参    数: int * s
// 返 回 值: void     
// 使用示例：Conut()
//************************************
void Conut(long* S)
{
    long  time;
    time=TH1*256+TL1 + 65536*overNum;
    TH1=0;
    TL1=0;
    overNum = 0;
    *S= (time*0.172);     //算出来是MM

}



void Timer1_isr(void) interrupt 3
{

    TR0 = 0;
    TH1 = 0x00;	 //设置初始值
    TL1 = 0x00;
    overNum++;

    TR0 = 1;

}

//************************************
// 函数名称: Init_Timer     
// 函数说明：初始化定时器   
// 参    数: void
// 返 回 值: void     
// 使用示例：Init_Timer()
//************************************
void Init_Timer(void)
{
    TH0 = 0xFB;	 //设置初始值
    TL0 = 0x80;
    TH1 = 0x00;	 //设置初始值
    TL1 = 0x00;
    TMOD = 0x11;			     
    EA=1;                      //总中断使能
    ET1=1;                     //定时中断使能
    ET0 = 1;
    TR1=0;                     //打开定时器开关
    TR0 = 1;
}






