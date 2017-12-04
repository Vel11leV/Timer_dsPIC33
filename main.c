
#include "p33Fxxxx.h"
#include "display.h"
#include "delay.h"
#include "n5x8.h"
#include "words.h"
#include "initports.h"
#include "buttons.h"
#include "ecan.h"
#include "dma.h"
#include "modes.h"


void main(void)
{

/*---------Initialisation of the hardware and initial image on displey ---------*/
initports();
HL1=1;HL2=1;HL6=1;HL14=1;
TimerInit();
disp_init();
bit_timing();
ecan_init();
conreceiveinit();
 //__attribute__(( interrupt, auto_psv )) _C1Interrupt();


/*-------------------------------Initial setting--------------------------------*/

unsigned int T11=10,T12=2;			//установки мода 1
unsigned int cycles1=1;	
	
unsigned int T21=20,T22=2; 			//установки мода 2
unsigned int cycles2=1;

unsigned int T31=20,T32=2,T33=50,T34=2; 	//установки мода 3
unsigned int cycles3=1;

unsigned int T41=20,T42=2,T43=50;		//установки мода 4

unsigned int ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0; 

unsigned char a=0;
//unsigned int Mode1=1,Mode2=2,Mode3=3,Mode4=4;												//идентификаторы главного меню

unsigned char Up=0, Down=0, In=0, Out=0;													//управление в главном меню

unsigned char ModeCheck=1, TimeCheck1=1, TimeCheck2=1, TimeCheck3=1, TimeCheck4=1; 			//позиции курсоров в каждом моде и главном меню

unsigned char start=0,stop=0;

/////////////////////////////////////////////////////////
frame1_out();
/*===================*/

/*===================*/

line2_out();
displey_mask2(ModeCheck);	
Scroll(ModeCheck);
HL1=0;HL2=0;HL6=1;HL14=1;
transmition_command(0x11);
/////////////////////////////////////////////////////////
/*--------------------------------program---------------------------------------*/
while(1)
{
can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7);


if(a)
{
if(SW7)
	{
	delay(40);
	if(SW7)
	{
	Up=1;
	Down=0;
	delay(50);
	}
	}
if(SW10)
	{
	delay(40);
	if(SW10)
	{
	Down=1;
	Up=0;
	delay(50);
	}
	}
if(SW5)
	{
	delay(40);
	if(SW5)
	{
	In=1;
	delay(100);
	}
	}
if(SW1&&!SW2)
	{
	delay(40);
	if(SW1&&!SW2)
	{
	start=1;
	delay(10);
	}
	}
if(SW2&&!SW1)
	{
	delay(40);
	if(SW2&&!SW1)
	{
	stop=1;
	delay(10);
	}
	}
}

if(Down==1)
	{
	if(ModeCheck<5)
	{ModeCheck++;}
	if(ModeCheck==5)
	{ModeCheck=1;}
	Scroll(ModeCheck);
	ModeExpl(ModeCheck);
	Down=0;

	}
if(Up==1)
	{
	if(ModeCheck>0)
	{ModeCheck--;}
	if(ModeCheck==0)
	{ModeCheck=4;}
	Scroll(ModeCheck);
	ModeExpl(ModeCheck);
	Up=0;
	}
if(In==1)
	{
	In=0;
	Out=1;
	if(ModeCheck==1)
	{mod1(&Out,ModeCheck,&TimeCheck1,&T11,&T12,&cycles1);}
	if(ModeCheck==2)
	{mod2(&Out,ModeCheck,&TimeCheck2,&T21,&T22,&cycles2);}
	if(ModeCheck==3)
	{mod3(&Out,ModeCheck,&TimeCheck3,&T31,&T32,&T33,&T34,&cycles3);}
	if(ModeCheck==4)
	{mod4(&Out,ModeCheck,&TimeCheck4,&T41,&T42,&T43);}
	
	}


if(start==1)
{
delay(70);
transmition_command(0x0F);
start=0;
delay(50);
}
if(stop==1)
{
delay(70);
transmition_command(0xF0);
stop=0;
delay(50);
}


if(!a)
{
//+++++++++//
if(ident==0b01110000000)
{
T11=ms0;
T12=ms1;
cycles1=ms5;
cycles1=(cycles1<<8);
cycles1=cycles1+ms4;
ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0;
}

if(ident==0b10110000000)
{
T21=ms0;
T22=ms1;
cycles2=ms5;
cycles2=(cycles2<<8);
cycles2=cycles2+ms4;
ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0;
}

if(ident==0b11010000000)
{
T31=ms0;
T32=ms1;
T33=ms2;
T34=ms3;
cycles3=ms5;
cycles3=(cycles3<<8);
cycles3=cycles3+ms4;
ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0;
}

if(ident==0b11100000000)
{
T41=ms0;
T42=ms1;
T43=ms2;
ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0;
a=1;
}

if(ident!=0)
{
ident=0,ms0=0,ms1=0,ms2=0,ms3=0,ms4=0,ms5=0,ms6=0,ms7=0;
a=1;
}

//+++++++++//
}



}
}






