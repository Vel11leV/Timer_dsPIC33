#include "p33Fxxxx.h"
#include "display.h"
#include "delay.h"
#include "n5x8.h"
#include "words.h"



#define X_Offset 28

#define Ind_Data_Port 	LATE

#define Ind_D_WR(i) \
	{ \
		Ind_Data_Port = i; \
		_NOP; \
	}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void port_conf(void)
{
TRISGbits.TRISG15=0; //ports have been configurated as OUT-ports
TRISGbits.TRISG14=0;
TRISGbits.TRISG13=0;
TRISGbits.TRISG12=0;

TRISCbits.TRISC1=0;

TRISAbits.TRISA0=0;

TRISE=0;



}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void comm_out(unsigned char i)
{
DC=0;
_NOP;
CS=0;
_NOP;

WR=0;

Ind_Data_Port=i;
_NOP;

WR=1;
_NOP;
CS=1;
_NOP;
DC=1;
_NOP;
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void data_out(unsigned char i)
{
DC=1;
_NOP;
CS=0;
_NOP;
WR=0;

Ind_Data_Port=i;
_NOP;

WR=1;
_NOP;
CS=1;
_NOP;
DC=1;
_NOP;
};

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void reset(void)
{
	ISDN=0;
	_NOP;

	CS=1;
	_NOP;

	WR=1;
	_NOP;

	RD = 1;
	_NOP;

	RES = 1;
	_NOP;

	delay(4);
	RES = 0;	// Reset Driver IC
	_NOP;
	delay(4);

	RES = 1;
	_NOP;
	delay(4);

	
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
unsigned char	data_read(void)
{
	static unsigned char (Temp_in);
	// Port E as input
	TRISE = 0xFFFF;
	_NOP;

	DC = 1;		// DC SET HIGH FOR DATA
	_NOP;
	CS = 0;	// CHIP SELECT SET TO LOW
	_NOP;
	
	RD = 0;	// LOW FOR READ
	_NOP;
	_NOP;
	_NOP;
	_NOP;
	_NOP;
	_NOP;

	Temp_in = data_bus;
	_NOP;

	RD = 1;	// NO READ
	_NOP;
	CS = 1;	// CHIP SELECT SET TO HIGH
	_NOP;
	DC = 1;		// DC SET HIGH TO DATA
	_NOP;
	// Port E as output
	TRISE = 0;
	_NOP;

	return (Temp_in);
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void IND_Lock(void)
{
comm_out(0xFD);
data_out(0x12);
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void IND_Unlock(void)
{
comm_out(0xFD);
data_out(0x16);
//Refresh_Regs();
};

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void Refresh_Regs (void)
{
	comm_out(0xB3); // SCLK CLOCK DIVIDER RATIO SELECT
	data_out(0x91); 

	comm_out(0xCA); // MUX RATIO
	data_out(0x3F); 

	comm_out(0xA2); // Set dispay offset
	data_out(0x00); 

	comm_out(0xA1); // Set display Start Line
	data_out(0x00);

	comm_out(0xA0); //Set horisontal adress increment,disable column addres remap,
	data_out(0x10); //disable nibble remap,scan from com 0 to (N-1),disable com split;
	data_out(0x1);  

	comm_out(0xB5); // Set GPIO
	data_out(0x00); 

	comm_out(0xAB); // Function Selection (Internal VDD)
	data_out(0x01); 

	comm_out(0xB4); // Enable Exteral VSL
	data_out(0xA0); 
	data_out(0xFD); 

	comm_out(0xC1); // Set Contrast Current
	data_out(0x9F); 

	comm_out(0xC7); // Master Contrast Current control 
	data_out(0x0F); 

	comm_out(0x00); // Set GrayScale Table

	comm_out(0xB8); // Set GrayScale Table
	data_out(0); 
	data_out(0); 
	data_out(8); 
	data_out(16); 
	data_out(24); 
	data_out(32); 
	data_out(40); 
	data_out(48); 
	data_out(56); 
	data_out(64); 
	data_out(72); 
	data_out(80); 
	data_out(88); 
	data_out(96); 
	data_out(104); 
	data_out(112); 

	comm_out(0xB9); // Set Default Linear Gray Scale Table

	comm_out(0xB1); // Set Phase Length
	data_out(0xE2);

	comm_out(0xD1); // Enhance Driving Scheme Capability
	data_out(0x82); 
	data_out(0x20); 

	comm_out(0xBB); // Set Precharge Voltage
	data_out(0x1F); 

	comm_out(0xB6); // Set Second Precharge Voltage
	data_out(0x08); 

	comm_out(0xBE); // Set VCOMH deselect level
	data_out(0x07); 

	comm_out(0xA9); // Exit from Partial Display

ISDN=1;
	_NOP;
	
delay(120);

	comm_out(0xA6); // Set Display Mode
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void init_OLED_GS_DC (void)
{
	              /////COMMAND SETTING//////

	comm_out(0xFD); // Command lock
	data_out(0x12); 

	comm_out(0xAE); // Sleep In

	comm_out(0xB3); // SCLK CLOCK DIVIDER RATIO SELECT
	data_out(0x91); 

	comm_out(0xCA); // MUX RATIO
	data_out(0x3F); 

	comm_out(0xA2); // Set dispay offset
	data_out(0x00); 

	comm_out(0xA1); // Set display Start Line
	data_out(0x00);

	comm_out(0xA0);  // Set horisontal adress increment,disable column addres remap,  
	data_out(0x14); // disable nibble remap,scan from com 0 to (N-1),disable com split;
	data_out(0x11); 

	comm_out(0xB5); // Set GPIO
	data_out(0x00); 

	comm_out(0xAB); // Function Selection (Internal VDD)
	data_out(0x01); 

	comm_out(0xB4); // Enable Exteral VSL
	data_out(0xA0); 
	data_out(0xFD); 

	comm_out(0xC1); // Set Contrast Current
	data_out(0x9F); 

	comm_out(0xC7); // Master Contrast Current control 
	data_out(0x0F); 

	comm_out(0xB9); // Set Default Linear Gray Scale Table

	comm_out(0xB1); // Set Phase Length
	data_out(0xE2);

	comm_out(0xD1); // Enhance Driving Scheme Capability
	data_out(0x82); 
	data_out(0x20); 

	comm_out(0xBB); // Set Precharge Voltage
	data_out(0x1F); 

	comm_out(0xB6); // Set Second Precharge Voltage
	data_out(0x08); 

	comm_out(0xBE); // Set VCOMH deselect level
	data_out(0x07); 


	ISDN = 1;
	_NOP;
	
	delay(120);

	comm_out(0xA6); // Set Display Mode
	// Clear Screen

	
comm_out(0xAF); // Sleep Out
write_RAM();



};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void write_RAM (void)
{

	
	unsigned int i, j;
	
	//IND_Unlock();

//	sub_comm();
	Pos(0,0);
	comm_out(0x5C); // Enable write to RAM
	
	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 256; j++)
		{
			data_out(0x0);

		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void disp_init (void)
{
port_conf();
reset();
init_OLED_GS_DC();


}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void collumn_start_end(unsigned char start, unsigned end)   //column start and end point in RAM range:0....63!!!offset 28!!!
{
comm_out(0x15);
data_out(start);
data_out(end);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void row_start_end(unsigned char start, unsigned end)       //row start and end point in RAM range:0....63
{
comm_out(0x75);                                               
data_out(start);
data_out(end);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void frame1_out(void)

{
unsigned int i,j;

/*---------------------------------*/


Pos(0,0);

comm_out(0x5C); // Enable write to RAM


for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xFF);
		}
	}

/////////////////////////////////////////////////////////
Pos(0,63);

comm_out(0x5C); // Enable write to RAM

for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xFF);
		}
	}
/////////////////////////////////////////////////////////
collumn_start_end(28,28);
row_start_end(1,62);

comm_out(0x5C);
for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xF0);
			data_out(0x0);
		}
	}
/////////////////////////////////////////////////////////
collumn_start_end(28+63,28+63);
row_start_end(1,62);

comm_out(0x5C);
for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0x00);
			data_out(0x0F);
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void number_out(unsigned char x, unsigned char y,unsigned int N, unsigned char n)
{
unsigned char j,x0, z=0;
unsigned long NN=N;
x0=x;
if(NN<10)
	{
		j=1;
	x=x+(n-1)*2;
	}
if((NN<100)&&(NN>=10))
	{
		j=2;
	x=x+(n-2)*2;
	}
if((NN<1000)&&(NN>=100))
	{
		j=3;
	x=x+(n-3)*2;
	}
if((NN<10000)&&(NN>=1000))
	{
		j=4;
	x=x+(n-4)*2;

	}
if((NN<100000)&&(NN>=10000))
	{
		j=5;
x=x+(n-5)*2;
	}
unsigned char p=0,i;
unsigned char mass[j];
for(p=0;p<j;p++)
{
z=(char)(NN%10);
mass[(j-1)-p]=z;
NN=(NN/10);
}
	stroka_out(x0,y,n,NOTH35 );
 	for(i=0;i<j;i++)
	{
		z=mass[i];
		symbol_numb_out((x+i*2),y,z);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void number_p_out(unsigned char x, unsigned char y,unsigned int N)
{
unsigned int p;
unsigned char mass[4];
for(p=0;p<4;p++)
{
	if(p!=1)
	{
	mass[3-p]=N%10;
	N=N/10;
	};
	if(p==1)
	{mass[3-p]=10;}
}
unsigned char i;
 	for(i=0;i<4;i++)
	{
	symbol_numb_out((x+i*2),y,(mass[i]));
	}
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void symbol_out(unsigned char x, unsigned char y,unsigned char N) //letter is out
{
unsigned char a,i,j;
unsigned char line_1, line_2;
unsigned char bit_1, bit_2;
unsigned char mass[8];
//IND_Unlock();

for (a=0;a<8;a++)
{
if (a<5)
{mass[a]=letters[N][a];};
if (a>=5)
{mass[a]=0x00;};
}


collumn_start_end(x+X_Offset+1,x+X_Offset+2);
row_start_end(y+4,y+4+7);
comm_out(0x5C);


for(i=0;i<8;i++)
{

for(j=0;j<8;j=j+2)
	{
			
		line_1=mass[j];
		line_2=mass[j+1];

		bit_1=(line_1&1);
		bit_2=(line_2&1);
		
		if(bit_1&&bit_2)
			{data_out(0xFF);}
		
		if((!bit_1)&&(bit_2))
			{data_out(0x0F);}
		
		if(bit_1&&(!bit_2))
			{data_out(0xF0);}
		
		if((!bit_1)&&(!bit_2))
			{data_out(0x00);}
		
		mass[j]=(mass[j]>>1);
		mass[j+1]=(mass[j+1]>>1);
			
	}


}

	
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void symbol_numb_out(unsigned char x, unsigned char y, unsigned long int N) //number is out
{
unsigned char a,i,j;
unsigned char line_1, line_2;
unsigned char bit_1, bit_2;
unsigned char mass[8];
//IND_Unlock();
// unsigned char num[10][5]=
//	{
 //   0x3e,0x51,0x49,0x45,0x3e,	/* 0 0x30 */
//	0x00,0x42,0x7f,0x40,0x00,	/* 1 */
//	0x42,0x61,0x51,0x49,0x46,	/* 2 */
//	0x21,0x41,0x45,0x4b,0x31,	/* 3 */
//	0x18,0x14,0x12,0x7f,0x10,	/* 4 */
//	0x27,0x45,0x45,0x45,0x39,	/* 5 */
//	0x3c,0x4a,0x49,0x49,0x30,	/* 6 */
//	0x01,0x71,0x09,0x05,0x03,	/* 7 */
//	0x36,0x49,0x49,0x49,0x36,	/* 8 */
//	0x06,0x49,0x49,0x29,0x1e	/* 9 */
 //   };

for(j=0;j<8;j++)
{mass[j]=0;}

for (a=0;a<8;a++)
{
if (a<5)
{mass[a]=numbers[N][a];};
if (a>=5)
{mass[a]=0x00;};
}

collumn_start_end(x+X_Offset+1,x+X_Offset+2);
row_start_end(y+4,y+4+7);
comm_out(0x5C);


for(i=0;i<8;i++)
{

for(j=0;j<8;j=j+2)
	{
			
		line_1=mass[j];
		line_2=mass[j+1];

		bit_1=(line_1&1);
		bit_2=(line_2&1);
		
		if(bit_1&&bit_2)
			{data_out(0xFF);}
		
		if((!bit_1)&&(bit_2))
			{data_out(0x0F);}
		
		if(bit_1&&(!bit_2))
			{data_out(0xF0);}
		
		if((!bit_1)&&(!bit_2))
			{data_out(0x00);}
		
		mass[j]=(mass[j]>>1);
		mass[j+1]=(mass[j+1]>>1);
			
	}


}

	
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void stroka_out(unsigned char x, unsigned char y,unsigned char N, unsigned char *a )
{
unsigned char i;
 	for(i=0;i<N;i++)
	{
	symbol_out(x+i*2,y,a[i]);
	}
}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void	Pos (unsigned char x, unsigned char y)
{
	unsigned char N_chr;

	// pos y
	comm_out(0x75); // Column adress command
	data_out(y); 
	data_out(0x3F); 

	// pos x
	comm_out(0x15); // Column adress command
	data_out((x>>1)+X_Offset); 
	data_out(0x7F); 

	if (x&1)
	{
		comm_out(0x5D); // Read enable command
		data_read(); // Dummy read
		N_chr = data_read();
		data_read();
	
		// pos x
		comm_out(0x15); // Column adress command
		data_out((x>>1)+X_Offset); 
		data_out(0x7F); 
	
		comm_out(0x5C); // Write enable command
		data_out(N_chr); 
		
	}
	else 
		comm_out(0x5C); // Write enable command

}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void	displey_mask1(void)
{
stroka_out(17,0,14, heading);
stroka_out(0,15,7, Mode);
stroka_out(0,25,7, Phase1);
stroka_out(0,35,7, Phase2);
stroka_out(0,45,7, Phase3);
//stroka_out(15,15,4, a_uto);
//stroka_out(15,25,4, zero);
//stroka_out(15,35,4, zero);
//stroka_out(15,45,4, zero);
stroka_out(24,25,2, ms);
stroka_out(24,35,2, ms);
stroka_out(24,45,2, ms);
stroka_out(35,15,5, Time);
//stroka_out(46,15,4, zero);
stroka_out(56,15,2, ms);
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void	displey_mask2(unsigned char mode)
{
unsigned char i;
for(i=0;i<5;i++)
{stroka_out(0,(i*8),31,NOTH35);}
stroka_out(12,0,18,Timer_synchronizer);
stroka_out(4,8,5, Mode1);
stroka_out(4,16,5, Mode2);
stroka_out(4,24,5, Mode3);
stroka_out(4,32,5, Mode4);
ModeExpl(mode);
/*stroka_out(4,48,17,O_tb_BO_t_BO_t_BO);
symbol_out(1,8,74);
symbol_out(1,16,74);
symbol_out(1,24,74);
symbol_out(1,32,74);*/
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void line2_out(void)

{
unsigned int i,j;

Pos(2,47);

comm_out(0x5C); // Enable write to RAM


for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 62; j++)
		{
			data_out(0xFF);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void Scroll(unsigned int n)
{
if (n==1)
{symbol_out(1,8,74);
symbol_out(1,16,59);
symbol_out(1,24,59);
symbol_out(1,32,59);
symbol_out(35,8,59);

}
if (n==2)
{symbol_out(1,8,59);
symbol_out(1,16,74);
symbol_out(1,24,59);
symbol_out(1,32,59);
symbol_out(35,8,59);

}
if (n==3)
{symbol_out(1,8,59);
symbol_out(1,16,59);
symbol_out(1,24,74);
symbol_out(1,32,59);
symbol_out(35,8,59);

}
if (n==4)
{
symbol_out(1,8,59);
symbol_out(1,16,59);
symbol_out(1,24,59);
symbol_out(1,32,74);
symbol_out(35,8,59);
}
if (n==5)
{
symbol_out(1,8,59);
symbol_out(1,16,59);
symbol_out(1,24,59);
symbol_out(1,32,59);
symbol_out(35,8,74);
}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ModeExpl(unsigned char n)
{
if (n==1)
{
stroka_out(0,48,31,NOTH35);
stroka_out(4,48,13,ON_OFF_cycles);
}
if (n==2)
{
stroka_out(0,48,31,NOTH35);
stroka_out(4,48,19,Quick_ON_OFF_cycles);
}
if (n==3)
{
stroka_out(0,48,31,NOTH35);
stroka_out(4,48,20,OFF_tb_ON_OFF_cycles);
}
if (n==4)
{
stroka_out(0,48,31,NOTH35);
stroka_out(4,48,17,O_tb_BO_t_BO_t_BO);
}
if (n==5)
{}
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void	displey_mask3(unsigned char mode, unsigned int T1,unsigned int T2, unsigned int cycle1 )
{
unsigned char i;
for(i=0;i<5;i++)
{stroka_out(0,(i*8),31,NOTH35);}
//stroka_out(6,0,18,Timer_synchronizer);
//symbol_out(44,0,55);
stroka_out(25,0,5,Mode1);
stroka_out(4,8,7, Time1);
number_out(18,8,T1,2);
stroka_out(22,8,4,x100ms);
stroka_out(31,8,2,ms);
stroka_out(4,16,7, Time2);
number_out(20,16,T2,5);
stroka_out(31,16,1,sec);
stroka_out(4,24,7, Cycles);
number_out(20,24,cycle1,5);
ModeExpl(mode);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void	displey_mask4(unsigned char mode, unsigned int T1,unsigned int T2, unsigned int cycle2 )
{
unsigned char i;
for(i=0;i<5;i++)
{stroka_out(0,(i*8),31,NOTH35);}
//stroka_out(6,0,18,Timer_synchronizer);
//symbol_out(44,0,55);
stroka_out(25,0,5,Mode2);
stroka_out(4,8,7, Time1);
number_out(18,8,T1,5);
stroka_out(29,8,2,ms);
stroka_out(4,16,7, Time2);
number_out(18,16,T2,5);
stroka_out(29,16,1,sec);
stroka_out(4,24,7, Cycles);
number_out(18,24,cycle2,5);
ModeExpl(mode);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void	displey_mask5(unsigned char mode,unsigned int T1,unsigned int T2, unsigned int T3, unsigned int T4, unsigned int cycle3 )
{
unsigned char i;
for(i=0;i<5;i++)
{stroka_out(0,(i*8),30,NOTH35);}
//stroka_out(6,0,18,Timer_synchronizer);
//symbol_out(44,0,55);
stroka_out(25,0,5,Mode3);
stroka_out(4,8,7, Time1);
number_out(18,8,T1,5);
stroka_out(29,8,2,ms);
stroka_out(4,16,7, Time2);
number_out(18,16,T2,5);
stroka_out(29,16,1,sec);
stroka_out(4,24,7, Time3);
number_out(18,24,T3,5);
stroka_out(29,24,2,ms);
stroka_out(4,32,7, Time4);
number_out(18,32,T4,5);
stroka_out(29,32,1,sec);
stroka_out(38,8,7, Cycles);
number_out(52,8,cycle3,5);
ModeExpl(mode);
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void	displey_mask6(unsigned char mode, unsigned int T1,unsigned int T2, unsigned int T3 )
{
unsigned char i;
for(i=0;i<5;i++)
{stroka_out(0,(i*8),31,NOTH35);}
//stroka_out(6,0,18,Timer_synchronizer);
//symbol_out(44,0,55);
stroka_out(25,0,5,Mode4);
stroka_out(4,8,7, Time1);
number_out(18,8,T1,5);
stroka_out(29,8,2,ms);
stroka_out(4,16,7, Time2);
number_out(18,16,T2,5);
stroka_out(29,16,1,sec);
stroka_out(4,24,7, Time3);
number_out(18,24,T3,5);
stroka_out(29,24,2,ms);
ModeExpl(mode);
}


//////////////////////////////////////////////////////////////////////////

void done_cyvles(unsigned int n)
{
stroka_out(38,32,5, Done);
number_out(52,32,n,5);
}
void noth_done(void)
{
stroka_out(38,32,12,NOTH35);
}


/////////////////////////////////////////////////////////////////////////
void paus(void)
{
stroka_out(38,24,5, PAUSE);
}
void noth_paus(void)
{
stroka_out(38,24,5,NOTH35);
}