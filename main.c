#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit Buzzer = P2^5;

#define SPEED 775 
#define P   0
#define L1  1
#define L1_ 2
#define L2  3
#define L2_ 4
#define L3  5
#define L4  6
#define L4_ 7
#define L5  8
#define L5_ 9
#define L6  10
#define L6_ 11
#define L7  12
#define M1  13
#define M1_ 14
#define M2  15
#define M2_ 16
#define M3  17
#define M4  18
#define M4_ 19
#define M5  20
#define M5_ 21
#define M6  22
#define M6_ 23
#define M7  24
#define H1  25
#define H1_ 26
#define H2  27
#define H2_ 28
#define H3  29
#define H4  30
#define H4_ 31
#define H5  32
#define H5_ 33
#define H6  34
#define H6_ 35
#define H7  36



//音调频率表，重装载值，下标对应简谱音符
unsigned int FreqTable[] = {
	0,
	63777,63872,63969,64054,64140,64216,64291,64360,64426,64489,64547,64603,
	64655,64704,64751,64795,64837,64876,64913,64948,64981,65012,65042,65070,
	65095,65120,65144,65166,65186,65206,65225,65242,65259,65274,65289,65303,
};

unsigned char FreqSelect,MusicSelect;

unsigned char code Music[] ={
//第1行
L6,2,
M1,2,
M5,2,
M1,2,
L4,2,
L5,1,
L6,1,
M5,2,
M1,2,
	
L1,2,
L5,2,
M5,2,
M1,2,
L1,2,
L5,2,
L7,2,
M5,2,
	
L6,2,
M1,2,
M5,2,
M1,2,
L4,2,
L5,1,
L6,1,
M5,2,
L5,2,

L1,2,
L5,2,
M5,2,
M1,2,
L1,2,
L5,2,
L7,1,
M1,1,
M5,2,

//第2行
P,2,
M5,2,
M5,2,
M1,2,
M1,4,
M2,2,
M3,2,
	
P,2,
M5,2,
M5,2,
M1,2,
M1,2,
M2,1,
M3,1,
M2,1,
M1,1,
L5,2,

P,2,
M5,2,
M5,2,
M1,2,
M1,4,
M2,2,
M3,2,

P,2,
M3,2,
M3,2,
M2,1,
M3,1,
M4,1,
M3,1,
M2,1,
M4,1,
M3,1,
M2,1,
M1,2,

//第3行
L5,2,
M1,2,
M1,2,
M3,2,
M4,2,
M3,2,
M2,2,
M1,1,
M2,1,

M3,2,
M3,2,
M3,2,
M3,2,
M2,1,
M3,1,
M2,2,
M1,4,

L5,2,
M1,2,
M1,2,
M3,2,
M4,2,
M3,2,
M2,2,
M1,1,
M2,1,

M3,2,
M3,2,
M3,2,
M3,2,
M2,1,
M3,1,
M2,2,
M1,3,
L7,1,

//第4行
M1,1,
M1,1,
M1,1,
M1,1,
L7,1,
M1,2,
M1,2,
M1,1,
M1,1,
M1,1,
L7,1,
M1,2,
M1,2,

M1,1,
M1,1,
M1,1,
L7,1,
M1,2,
M1,2,
M1,1,
M1,1,
M1,1,
M5,1,
M5,2,
M5,1,

P,1,
M5,1,
M5,1,
M5,1,
M5,1,
M5,2,
M5,2,
M5,1,
M5,1,
M5,1,
M5,1,
M4,1,
M4,1,
M3,9,

//第5行
P,4,
M2,1,
M1,1,
L7,1,
M1,1,

L6,2,
L7,2,
M1,2,
M5,2,
M4,2,
M3,2,
M1,2,
M1,6,

P,3,
L6,2,
M1,1,
M1,1,
M1,1,
M3,2,
M1,2,

L6,2,
L7,2,
M1,2,
M5,2,
M4,2,
M3,2,
M1,2,
M2,10,

//第6行
P,4,
P,4,

M3,2,
M2,2,
M4,2,
M3,4,
M1,2,
M5,2,
M7,2,

H1,2,
M7,2,
M5,2,
M1,4,
M1,2,
M6,2,
M6,4,

M6,2,
M5,2,
M5,4,
M5,2,
M4,2,
M3,2,

//第7行
M2,2,
M3,2,
M4,2,
M3,10,

M3,2,
M4_,2,
M5_,2,
M3,4,
M4_,2,
M5_,2,
M7,2,

H2,2,
M7,2,
H1,2,
H1,6,
P,2,
H1,2,

H1,2,
M5,2,
M5,2,
M6,2,
M5,2,
M4,2,
M2,2,
M3,2,

//第8行
M4,2,
M5,2,
M6,2,
M1,2,
M6,3,
M7,1,
M7,4,

M3,2,
M2,2,
M4,2,
M3,4,
M1,2,
M5,2,
M7,2,

H1,2,
M7,2,
M5,2,
M1,4,
M1,2,
M6,2,
M6,4,

M6,2,
M5,2,
M5,4,
M5,2,
M4,2,
M3,2,

//第9行
M2,2,
M3,2,
M4,2,
M3,10,

M3,2,
M4_,2,
M5_,2,
M3,4,
M4_,2,
M5_,2,
M7,2,

H2,2,
M7,2,
H1,2,
H1,6,
P,2,
H1,2,

H1,2,
M5,2,
M5,2,
M6,2,
M5,2,
M4,2,
L6,2,
L7,2,
//第10行

M1,2,
M2,2,
M3,2,
M2,2,
P,3,
L5,1,
M3,2,
M1,10,

//P,4,
//P,4,

//M5,2,
//M1,6,
//M5,2,
//M1,2,
//L6,2,
//M1,2,

//M5,2,
//M1,6,
//M5,2,
//M1,2,
//M2,2,
//M1,2,

0xFF
};
//16分音符为1，8分为2，4分为4，2分为8
void main()
{
	Timer0_Init();//开启中断，准备生成方波
	while(1)//无限循环播放音乐
	{
		if(Music[MusicSelect] != 0xFF)//判断是否到旋律末尾
		{
			FreqSelect = Music[MusicSelect];
			MusicSelect++;
			Delay(SPEED/4*Music[MusicSelect]);
			MusicSelect++;
			TR0 = 0;
			Delay(5);
			TR0 = 1;
		}
		else
		{
			TR0 = 0;
			while(1);
		}
	}
}
 
void Timer0_Routine() interrupt 1   //定时器0中断函数 中断关键字
{
	if(FreqTable[FreqSelect])
	TL0 = FreqTable[FreqSelect] % 256;
	TH0 = FreqTable[FreqSelect] / 256;	                    //重新赋初值
	Buzzer = !Buzzer;
}