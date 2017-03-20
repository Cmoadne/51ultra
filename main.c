

//--������Ҫʹ�õ�ͷ�ļ�--//
#include <reg52.h>	   //���ļ��ж�����51��һЩ���⹦�ܼĴ���
#include "number.h"
#include <intrins.h>

sbit BEEP = P1^3;
sbit RX=P1^1;
sbit TX=P1^0;
int overNum;     //��ʱ�������
//--����ȫ�ֺ���--//
void Delay(unsigned int c);   //��ʱ10ms

void Conut(long*S);
 /************************************* */ 
/* ��������: Init_Timer */
/* ����˵������ʼ����ʱ�� */
/* �� ��: void */ 
/* �� �� ֵ: void */ 
/* ʹ��ʾ����Init_Timer() */ 
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
        TX=1;			                //800MS  ����һ��ģ��
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
        //��RXΪ��ʱ�ȴ�
        TR1=1;			    //��������
        i= 0;
        while(RX)
        {
        }
        //��RXΪ1�������ȴ�
        TR1=0;				//�رռ���
        Conut(&S);			//����
        TR0 = 0;
        showDistance(S);
        TR0 = 1;
        Delay(200);
        // BEEP = 0;
        //  BEEP = ~BEEP;
    }

}


//************************************
// ��������: Delay     
// ����˵����   
// ��    ��: unsigned int c
// �� �� ֵ: void     
// ʹ��ʾ����Delay()
//************************************
void Delay(unsigned int c)   //��� 0us
{
    unsigned char a, b;

    //--c�Ѿ��ڴ��ݹ�����ʱ���Ѿ���ֵ�ˣ�������for����һ��Ͳ��ø�ֵ��--//
    for (;c>0;c--)
    {
        for (b=38;b>0;b--)
        {
            for (a=130;a>0;a--);
        }

    }

}


//************************************
// ��������: Conut     
// ����˵����   
// ��    ��: int * s
// �� �� ֵ: void     
// ʹ��ʾ����Conut()
//************************************
void Conut(long* S)
{
    long  time;
    time=TH1*256+TL1 + 65536*overNum;
    TH1=0;
    TL1=0;
    overNum = 0;
    *S= (time*0.172);     //�������MM

}



void Timer1_isr(void) interrupt 3
{

    TR0 = 0;
    TH1 = 0x00;	 //���ó�ʼֵ
    TL1 = 0x00;
    overNum++;

    TR0 = 1;

}

//************************************
// ��������: Init_Timer     
// ����˵������ʼ����ʱ��   
// ��    ��: void
// �� �� ֵ: void     
// ʹ��ʾ����Init_Timer()
//************************************
void Init_Timer(void)
{
    TH0 = 0xFB;	 //���ó�ʼֵ
    TL0 = 0x80;
    TH1 = 0x00;	 //���ó�ʼֵ
    TL1 = 0x00;
    TMOD = 0x11;			     
    EA=1;                      //���ж�ʹ��
    ET1=1;                     //��ʱ�ж�ʹ��
    ET0 = 1;
    TR1=0;                     //�򿪶�ʱ������
    TR0 = 1;
}






