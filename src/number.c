#include "number.h"
#include "reg52.h"

//定义四位数码管
sbit bit4 = P2^0;
sbit bit3 = P1^6;
sbit bit2 = P1^5;
sbit bit1 = P2^7;

//数码管的各段
sbit dpyA = P2^6;
sbit dpyB = P1^7;
sbit dpyC = P2^2;
sbit dpyD = P2^4;
sbit dpyE = P2^5;
sbit dpyF = P1^4;
sbit dpyG = P2^1;
sbit dpyH = P2^3;



char forth = 0;
char third = 0;
char second = 0;
char first = 0;
char index = 0;


static void allOn(void)
{
    bit4 = 1;
    bit3 = 1;
    bit2 = 1;
    bit1 = 1;

    dpyA = 0;
    dpyB = 0;
    dpyC = 0;
    dpyD = 0;
    dpyE = 0;
    dpyF = 0;
    dpyG = 0;
    dpyH = 0;
}
static void allOff(void)
{
    bit4 = 0;
    bit3 = 0;
    bit2 = 0;
    bit1 = 0;

    dpyA = 0;
    dpyB = 0;
    dpyC = 0;
    dpyD = 0;
    dpyE = 0;
    dpyF = 0;
    dpyG = 0;
    dpyH = 0;
}
static void showNumber(char number)
{
    switch(number)
    {
    case 0:
        dpyA = 0;
        dpyB = 0;
        dpyC = 0;
        dpyD = 0;
        dpyE = 0;
        dpyF = 0;
        dpyG = 1;
        dpyH = 1;
        break;
    case 1:
        dpyA = 1;
        dpyB = 1;
        dpyC = 1;
        dpyD = 1;
        dpyE = 0;
        dpyF = 0;
        dpyG = 1;
        dpyH = 1;
        break;
    case 2:
        dpyA = 0;
        dpyB = 0;
        dpyC = 1;
        dpyD = 0;
        dpyE = 0;
        dpyF = 1;
        dpyG = 0;
        dpyH = 1;
        break;
    case 3:
        dpyA = 0;
        dpyB = 0;
        dpyC = 0;
        dpyD = 0;
        dpyE = 1;
        dpyF = 1;
        dpyG = 0;
        dpyH = 1;
        break;
    case 4:
        dpyA = 1;
        dpyB = 0;
        dpyC = 0;
        dpyD = 1;
        dpyE = 1;
        dpyF = 0;
        dpyG = 0;
        dpyH = 1;
        break;
    case 5:
        dpyA = 0;
        dpyB = 1;
        dpyC = 0;
        dpyD = 0;
        dpyE = 1;
        dpyF = 0;
        dpyG = 0;
        dpyH = 1;
        break;
    case 6:
        dpyA = 0;
        dpyB = 1;
        dpyC = 0;
        dpyD = 0;
        dpyE = 0;
        dpyF = 0;
        dpyG = 0;
        dpyH = 1;
        break;
    case 7:
        dpyA = 0;
        dpyB = 0;
        dpyC = 0;
        dpyD = 1;
        dpyE = 1;
        dpyF = 1;
        dpyG = 1;
        dpyH = 1;
        break;
    case 8:
        dpyA = 0;
        dpyB = 0;
        dpyC = 0;
        dpyD = 0;
        dpyE = 0;
        dpyF = 0;
        dpyG = 0;
        dpyH = 1;
        break;
    case 9:
        dpyA = 0;
        dpyB = 0;
        dpyC = 0;
        dpyD = 1;
        dpyE = 1;
        dpyF = 0;
        dpyG = 0;
        dpyH = 1;
        break;
    default:
        break;
    }
}

void showDistance(int distance)
{

    if(distance > 10000)
        distance = 9999;
    forth = distance /1000%10;
    third = distance/100%10;
    second = distance/10%10;
    first = distance%10;

    //allOn();

    //allOff();
    //allOff();
    //bit1 = 1;
    //showNumber(1);

}
void Timer0_isr(void) interrupt 1 
{

    TR0 = 0;
    TH0 = 0xef;	 //设置初始值
    TL0 = 0xff;
    //      allOff();
    switch(index)
    {
    case 0:
        bit4 = 0;
        bit3 = 0;
        bit2 = 0;
        bit1 = 1;
        showNumber(forth);
        break;
    case 1:

        bit4 = 0;
        bit3 = 0;
        bit2 = 1;
        bit1 = 0;
        showNumber(third);
        break;
    case 2:

        bit4 = 0;
        bit3 = 1;
        bit2 = 0;
        bit1 = 0;
        showNumber(second);
        break;
    case 3:

        bit4 = 1;
        bit3 = 0;
        bit2 = 0;
        bit1 = 0;
        showNumber(first);
        break;
    default:break;
    }
    index ++;
    if(index > 3)
        index = 0;
    
    TR0 = 1;

}


