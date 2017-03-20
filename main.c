

//--包含你要使用的头文件--//
#include <reg52.h>	   //此文件中定义了51的一些特殊功能寄存器
#include "number.h"
#include <intrins.h>

sbit RX=P1^1;
sbit TX=P1^0;

unsigned int  time=0;
unsigned long S=0;
//--声明全局函数--//
void Delay10ms(unsigned int c);   //延时10ms



/*-----------------------------------------------
初始化定时器，做为动态扫描
------------------------------------------------*/
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

void Conut(void)
{
    time=TH1*256+TL1;
    TH1=0;
    TL1=0;

    S= (long)(time*0.172);     //算出来是MM

}
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void main()
{ 
    long i = 0;
    Init_Timer();
    showDistance(2234);
    BEEP = 0;
    Delay10ms(100);
    BEEP = 1;
    Delay10ms(100);
    BEEP = 0;
    //TR0= 0;

    while(1)
    {
        //showDistance(0);
LABEL1:
        TX=1;			                //800MS  启动一次模块
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_();
        _nop_(); 
        _nop_(); 
        _nop_(); 
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
            i++;
            if(i > 60000)
            {
                TR1 = 0;
                TH1=0;
                TL1=0;
                goto  LABEL1;
            }
        }
        //当RX为1计数并等待
        TR1=0;				//关闭计数
        Conut();			//计算
        TR0 = 0;
        showDistance(S);
        TR0 = 1;
        Delay10ms(200);
        // BEEP = 0;
        //  BEEP = ~BEEP;
    }

}

/*******************************************************************************
* 函 数 名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Delay10ms(unsigned int c)   //误差 0us
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












