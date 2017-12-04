#include "p33Fxxxx.h"
#include "main.h"
#include "display.h"
#include "ecan.h"
#include "buttons.h"
#include "timer.h"
#include "initports.h"
#include "delay.h"
#include "ecan.h"

/*--------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------Mode1----------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/



void mod1(unsigned char *out,unsigned char ModeCh,unsigned char *TimeCh1,unsigned int *t11,unsigned int *t12,unsigned int *cycle1)
{


unsigned char Up=0,Down=0;
unsigned char start=0, stop=1, prestart=0, prestop=0,pause=0;
unsigned int identm1=0,msm10=0,msm11=0,msm12=0,msm13=0,msm14=0,msm15=0,msm16=0,msm17=0; 
unsigned int did=0;

unsigned int i=0; 


displey_mask3(ModeCh,*t11,*t12,*cycle1);
HL1=1;HL2=1;HL6=0;
Scroll(*TimeCh1);
while(out)
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



if(SW19||SW15||SW4||SW12||SW3||SW11)
{
	if(*TimeCh1==1)
	numb_ch(18,8,t11,2,50,10);
	if(*TimeCh1==2)
	numb_ch(20,16,t12,5,30,2);
	if(*TimeCh1==3)
	numb_ch(20,24,cycle1,5,10000,1);
}
//++++++++++//
if(SW20)
{
for(i=0;i<450;i++)
{
if(SW20)
{delay(1);}
else 
{break;}
}

if(SW20)
{
HL6=1;
delay(200);
transmition_modes(0b0111000011100,*t11,*t12,0,0,*cycle1);
delay(600);

HL6=0;
/*	while(identm1==0)
	{
	can_read(&identm1,&msm10,&msm11,&msm12,&msm13,&msm14,&msm15,&msm16,&msm17);
	}
if(identm1==0b01110000111)
{
HL6=0;
identm1=0,msm10=0,msm11=0,msm12=0,msm13=0,msm14=0,msm15=0,msm16=0,msm17=0; 
}
else {identm1=0,msm10=0,msm11=0,msm12=0,msm13=0,msm14=0,msm15=0,msm16=0,msm17=0; }
*/	
}
}

//++++++++++//


if(Down==1)
	{
	if(*TimeCh1<4)
		{
		(*TimeCh1)++;
		}
	if(*TimeCh1==4)
		{
		*TimeCh1=1;
		}
	Scroll(*TimeCh1);
	Down=0;

	}
if(Up==1)
	{
	if(*TimeCh1>0)
		{
		(*TimeCh1)--;
		}
	if(*TimeCh1==0)
		{
		*TimeCh1=3;
		}
	Scroll(*TimeCh1);
	Up=0;
	}


///////////////////////////////////////
if(SW5)
{
delay(40);
if(SW5)
{
delay(40);
transmition_modes(0b0111000000000,*t11,*t12,0,0,*cycle1);
delay(50);
HL1=0;HL2=1;HL6=1;
prestart=1;
	while(prestart)
	{
		can_read(&identm1,&msm10,&msm11,&msm12,&msm13,&msm14,&msm15,&msm16,&msm17);

		if(identm1==0b10000000000&&start==1&&stop==0)
			{
			did=msm15;
			did=(did<<8);
			did=(did+msm14);
			number_out(52,32,did,5);

			if(did==*cycle1)
			{
			delay(500);
			start=0;
			stop=1;
			transmition_command(0xFF);
			did=0;
			noth_done();
			noth_paus();
			HL1=0;HL2=1;
			delay(50);
			}
			identm1=0,msm10=0,msm11=0,msm12=0,msm13=0,msm14=0,msm15=0,msm16=0,msm17=0;
			}
		if(identm1!=0)
			{
			identm1=0,msm10=0,msm11=0,msm12=0,msm13=0,msm14=0,msm15=0,msm16=0,msm17=0;
			}
	
		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		start=1;
		stop=0;
			if(pause)
			{pause=0;noth_paus();}
		done_cyvles(did);
		transmition_command(0xAA);
		delay(50);
		HL1=1;HL2=0;
		}
		}

		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		start=0;
		stop=1;
			if(pause)
			{pause=0;noth_paus();}
		transmition_command(0xFF);

		did=0;
		noth_done();
		delay(50);
		HL1=0;HL2=1;
		delay(200);
		}
		}
/*-----*/
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		pause=1;
		transmition_command(0xDD);
		paus();
		HL1=0;HL2=1;
		delay(20);
		}
		}

/*-----*/
		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		transmition_command(0xAF);
		did=0;
		noth_done();
		delay(50);
		HL1=1;HL2=1;HL6=0;
		prestart=0;
		delay(200);
		}
		}	
}
}
}

////////////////////////////////////////
if(SW6==1)
	{
	delay(40);
		if(SW6==1)
		{
		out=0;
		displey_mask2(ModeCh);
		HL1=0;HL2=0;HL6=1;
		Scroll(ModeCh);
		}
	}
}
};


/*------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Mode2----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------*/


void mod2(unsigned char *out,unsigned char ModeCh,unsigned char *TimeCh2,unsigned int *t21,unsigned int *t22,unsigned int *cycle2)

{
unsigned char Up=0,Down=0;
unsigned char start=0, stop=1, prestart=0, prestop=0, pause=0;

unsigned int did=0;
unsigned int i=0;  
unsigned int identm2=0,msm20=0,msm21=0,msm22=0,msm23=0,msm24=0,msm25=0,msm26=0,msm27=0; 


displey_mask4(ModeCh,*t21,*t22,*cycle2);
HL1=1;HL2=1;HL6=0;
Scroll(*TimeCh2);

while(out)
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


if(SW19||SW15||SW4||SW12||SW3||SW11)
{
	if(*TimeCh2==1)
	numb_ch(18,8,t21,5,200,20);
	if(*TimeCh2==2)
	numb_ch(18,16,t22,5,30,2);
	if(*TimeCh2==3)
	numb_ch(18,24,cycle2,5,10000,1);
}


//++++++++++//
if(SW20)
{

for(i=0;i<450;i++)
{
if(SW20)
{delay(1);}
else 
{break;}
}

if(SW20)
{
HL6=1;
delay(200);
transmition_modes(0b1011000011100,*t21,*t22,0,0,*cycle2);
delay(600);
HL6=0;
/*
	while(identm2==0)
	{
	can_read(&identm2,&msm20,&msm21,&msm22,&msm23,&msm24,&msm25,&msm26,&msm27);
	}
if(identm2==0b10110000111)
{
HL6=0;
identm2=0,msm20=0,msm21=0,msm22=0,msm23=0,msm24=0,msm25=0,msm26=0,msm27=0; 
}
else {identm2=0,msm20=0,msm21=0,msm22=0,msm23=0,msm24=0,msm25=0,msm26=0,msm27=0; }	
*/
}
}

//++++++++++//


if(Down==1)
	{
	if(*TimeCh2<4)
		{
		(*TimeCh2)++;
		}
	if(*TimeCh2==4)
		{
		*TimeCh2=1;
		}
	Scroll(*TimeCh2);
	Down=0;

	}
if(Up==1)
	{
	if(*TimeCh2>0)
		{
		(*TimeCh2)--;
		}
	if(*TimeCh2==0)
		{
		*TimeCh2=3;
		}
	Scroll(*TimeCh2);
	Up=0;
	}

///////////////////////////////////////
if(SW5)
{
delay(40);
if(SW5)
{
delay(40);
transmition_modes(0b1011000000000,*t21,*t22,0,0,*cycle2);
delay(50);
HL1=0;HL2=1;HL6=1;
prestart=1;
	while(prestart)
	{
		can_read(&identm2,&msm20,&msm21,&msm22,&msm23,&msm24,&msm25,&msm26,&msm27);

		if(identm2==0b10000000000&&start==1&&stop==0)
			{
			did=msm25;
			did=(did<<8);
			did=(did+msm24);
			number_out(52,32,did,5);
			if(did==*cycle2)
			{
			delay(500);
			start=0;
			stop=1;
			transmition_command(0xFF);
			did=0;
			noth_done();
			noth_paus();
			delay(50);
			HL1=0;HL2=1;
			}
			identm2=0,msm20=0,msm21=0,msm22=0,msm23=0,msm24=0,msm25=0,msm26=0,msm27=0;
			}
		if(identm2!=0)
			{
			identm2=0,msm20=0,msm21=0,msm22=0,msm23=0,msm24=0,msm25=0,msm26=0,msm27=0;
			}


		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		start=1;
		stop=0;
			if(pause)
			{pause=0;noth_paus();}
		done_cyvles(did);
		transmition_command(0xAA);
		delay(50);
		HL1=1;HL2=0;
		}
		}

		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		start=0;
		stop=1;
			if(pause)
			{pause=0;noth_paus();}
		transmition_command(0xFF);
		did=0;
		noth_done();
		delay(50);
		HL1=0;HL2=1;
		}
		}
/*-----*/
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		pause=1;
		transmition_command(0xDD);
		paus();
		HL1=0;HL2=1;
		delay(20);
		}
		}

/*-----*/

		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		transmition_command(0xAF);
		did=0;
		noth_done();
		delay(50);
		HL1=1;HL2=1;HL6=0;
		prestart=0;
		delay(200);
		}
		}
}
}
}
////////////////////////////////////////
if(SW6==1)
	{
	delay(40);
		if(SW6==1)
		{
		out=0;
		displey_mask2(ModeCh);
		HL1=0;HL2=0;HL6=1;
		Scroll(ModeCh);
		}
	}
}
};


/*------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Mode3----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------*/


void mod3(unsigned char *out,unsigned char ModeCh,unsigned char *TimeCh3,unsigned int *t31,unsigned int *t32,unsigned int *t33,unsigned int *t34,unsigned int *cycle3)

{
unsigned char Up=0,Down=0;
unsigned char start=0, stop=1, prestart=0, prestop=0, pause=0;

unsigned int did=0;
unsigned int i=0; 
unsigned int identm3=0,msm30=0,msm31=0,msm32=0,msm33=0,msm34=0,msm35=0,msm36=0,msm37=0;  


displey_mask5(ModeCh,*t31,*t32,*t33,*t34,*cycle3);
HL1=1;HL2=1;HL6=0;
Scroll(*TimeCh3);

while(out)
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


if(SW19||SW15||SW4||SW12||SW3||SW11)
{
	if(*TimeCh3==1)
	numb_ch(18,8,t31,5,200,20);
	if(*TimeCh3==2)
	numb_ch(18,16,t32,5,30,2);
	if(*TimeCh3==3)
	numb_ch(18,24,t33,5,500,50);
	if(*TimeCh3==4)
	numb_ch(18,32,t34,5,30,2);
	if(*TimeCh3==5)
	numb_ch(52,8,cycle3,5,10000,1);
}


//++++++++++//
if(SW20)
{

for(i=0;i<450;i++)
{
if(SW20)
{delay(1);}
else 
{break;}
}

if(SW20)
{
HL6=1;
delay(200);
transmition_modes(0b1101000011100,*t31,*t32,*t33,*t34,*cycle3);
delay(600);
HL6=0;
/*
	while(identm3==0)
	{
	can_read(&identm3,&msm30,&msm31,&msm32,&msm33,&msm34,&msm35,&msm36,&msm37);
	}
if(identm3==0b11010000111)
{
HL6=0;
identm3=0,msm30=0,msm31=0,msm32=0,msm33=0,msm34=0,msm35=0,msm36=0,msm37=0; 
}
else {identm3=0,msm30=0,msm31=0,msm32=0,msm33=0,msm34=0,msm35=0,msm36=0,msm37=0; }	
*/
}
}

//++++++++++//


if(Down==1)
	{
	if(*TimeCh3<6)
		{
		(*TimeCh3)++;
		}
	if(*TimeCh3==6)
		{
		*TimeCh3=1;
		}
	Scroll(*TimeCh3);
	Down=0;

	}
if(Up==1)
	{
	if(*TimeCh3>0)
		{
		(*TimeCh3)--;
		}
	if(*TimeCh3==0)
		{
		*TimeCh3=5;
		}
	Scroll(*TimeCh3);
	Up=0;
	}

///////////////////////////////////////
if(SW5)
{
delay(40);
if(SW5)
{
delay(40);
transmition_modes(0b1101000000000,*t31,*t32,*t33,*t34,*cycle3);
delay(50);
HL1=0;HL2=1;HL6=1;
prestart=1;
	while(prestart)
	{
		can_read(&identm3,&msm30,&msm31,&msm32,&msm33,&msm34,&msm35,&msm36,&msm37);

		if(identm3==0b10000000000&&start==1&&stop==0)
			{
			did=msm35;
			did=(did<<8);
			did=(did+msm34);
			number_out(52,32,did,5);
			
			if(did==*cycle3)
			{
			delay(500);
			start=0;
			stop=1;
			transmition_command(0xFF);
			did=0;
			noth_done();
			noth_paus();
			delay(50);
			HL1=0;HL2=1;
			}
			identm3=0,msm30=0,msm31=0,msm32=0,msm33=0,msm34=0,msm35=0,msm36=0,msm37=0;
			}
		if(identm3!=0)
			{
			identm3=0,msm30=0,msm31=0,msm32=0,msm33=0,msm34=0,msm35=0,msm36=0,msm37=0;
			}


		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		start=1;
		stop=0;
			if(pause)
			{pause=0;noth_paus();}
		done_cyvles(did);
		transmition_command(0xAA);
		delay(50);
		HL1=1;HL2=0;
		}
		}

		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		start=0;
		stop=1;
			if(pause)
			{pause=0;noth_paus();}
		transmition_command(0xFF);
		did=0;
		noth_done();
		delay(50);
		HL1=0;HL2=1;
		}
		}

/*-----*/
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		pause=1;
		transmition_command(0xDD);
		paus();
		HL1=0;HL2=1;
		delay(20);
		}
		}

/*-----*/

		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		transmition_command(0xAF);
		did=0;
		noth_done();
		delay(50);
		HL1=1;HL2=1;HL6=0;
		prestart=0;
		delay(200);
		}
		}	
	}
}
}
////////////////////////////////////////
if(SW6==1)
	{
	delay(40);
		if(SW6==1)
		{
		out=0;
		displey_mask2(ModeCh);
		HL1=0;HL2=0;HL6=1;
		Scroll(ModeCh);
		}
	}
}
};


/*------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Mode4----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------*/

void mod4(unsigned char *out,unsigned char ModeCh,unsigned char *TimeCh4,unsigned int *t41,unsigned int *t42,unsigned int *t43)

{
unsigned char Up=0,Down=0;
unsigned char start=0, stop=1, prestart=0, prestop=0, pause=0;
unsigned int identm4=0,msm40=0,msm41=0,msm42=0,msm43=0,msm44=0,msm45=0,msm46=0,msm47=0;
unsigned int i=0;  
unsigned int did=0;

displey_mask6(ModeCh,*t41,*t42,*t43);
HL1=1;HL2=1;HL6=0;
Scroll(*TimeCh4);

while(out)
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
	delay(20);
	if(SW10)
		{
		Down=1;
		Up=0;
		delay(50);
		}
	}


if(SW19||SW15||SW4||SW12||SW3||SW11)
{
	if(*TimeCh4==1)
	numb_ch(18,8,t41,5,200,20);
	if(*TimeCh4==2)
	numb_ch(18,16,t42,5,30,2);
	if(*TimeCh4==3)
	numb_ch(18,24,t43,5,500,50);
}



//++++++++++//
if(SW20)
{

for(i=0;i<450;i++)
{
if(SW20)
{delay(1);}
else 
{break;}
}

if(SW20)
{
HL6=1;
delay(200);
transmition_modes (0b1110000011100,*t41,*t42,*t43,0,0);
delay(600);
HL6=0;
/*
	while(identm4==0)
	{
	can_read(&identm4,&msm40,&msm41,&msm42,&msm43,&msm44,&msm45,&msm46,&msm47);
	}
if(identm4==0b11100000111)
{
HL6=0;
identm4=0,msm40=0,msm41=0,msm42=0,msm43=0,msm44=0,msm45=0,msm46=0,msm47=0; 
}
else {identm4=0,msm40=0,msm41=0,msm42=0,msm43=0,msm44=0,msm45=0,msm46=0,msm47=0; }	
*/
}
}

//++++++++++//



if(Down==1)
	{
	if(*TimeCh4<4)
		{
		(*TimeCh4)++;
		}
	if(*TimeCh4==4)
		{
		*TimeCh4=1;
		}
	Scroll(*TimeCh4);
	Down=0;

	}
if(Up==1)
	{
	if(*TimeCh4>0)
		{
		(*TimeCh4)--;
		}
	if(*TimeCh4==0)
		{
		*TimeCh4=3;
		}
	Scroll(*TimeCh4);
	Up=0;
	}


///////////////////////////////////////
if(SW5)
{
delay(40);
if(SW5)
{
delay(80);
transmition_modes(0b1110000000000,*t41,*t42,*t43,0,0);
delay(50);
HL1=0;HL2=1;HL6=1;
prestart=1;
	while(prestart)
	{
		can_read(&identm4,&msm40,&msm41,&msm42,&msm43,&msm44,&msm45,&msm46,&msm47);

		if(identm4==0b10000000000&&start==1&&stop==0)
			{
			did=msm45;
			did=(did<<8);
			did=(did+msm44);
			if(did)
			{
			start=0;
			stop=1;
			transmition_command(0xFF);
			did=0;
			delay(50);
			noth_paus();
			HL1=0;HL2=1;
			}
			identm4=0,msm40=0,msm41=0,msm42=0,msm43=0,msm44=0,msm45=0,msm46=0,msm47=0;
			}
		if(identm4!=0)
			{
			identm4=0,msm40=0,msm41=0,msm42=0,msm43=0,msm44=0,msm45=0,msm46=0,msm47=0;
			}

		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(40);
		if((SW1&&!SW6&&!SW2&&start==0&&stop==1)||(SW1&&!SW6&&!SW2&&pause))
		{
		delay(80);
		start=1;
		stop=0;
			if(pause)
			{pause=0;noth_paus();}
		transmition_command(0xAA);
		delay(50);
		HL1=1;HL2=0;
		}
		}

		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(40);
		if((SW6&&!SW1&&!SW2&&start==1&&stop==0)||(SW6&&!SW1&&!SW2&&pause))
		{
		delay(80);
		start=0;
		stop=1;
			if(pause)
			{pause=0;noth_paus();}
		transmition_command(0xFF);
		did=0;
		delay(50);
		HL1=0;HL2=1;
		}
		}

/*-----*/
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		if(SW2&&!SW1&&!SW6&&start==1&&stop==0)
		{
		delay(40);
		pause=1;
		transmition_command(0xDD);
		paus();
		HL1=0;HL2=1;
		delay(20);
		}
		}

/*-----*/

		if(SW6&&start==0&&stop==1)
		{
		delay(40);
		if(SW6&&start==0&&stop==1)
		{
		delay(80);
		transmition_command(0xAF);
		did=0;
		noth_done();
		delay(50);
		HL1=1;HL2=1;HL6=0;
		prestart=0;
		delay(200);
		}
		}
	}
}
}
////////////////////////////////////////
if(SW6==1)
	{
	delay(40);
		if(SW6==1)
		{
		delay(80);
		out=0;
		displey_mask2(ModeCh);
		HL1=0;HL2=0;HL6=1;
		Scroll(ModeCh);
		}
	}
}
};
