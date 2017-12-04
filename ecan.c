#include "p33Fxxxx.h"
#include "ecan.h"
unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));
/* ECAN message buffer length */


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void dma_conf(void)
{
/*---------------------------DMA0 initialisation---------------------------*/

/* Initialize the DMA channel 0 for ECAN TX and clear the colission flags */
DMACS0 = 0;
/* Set up Channel 0 for peripheral indirect addressing mode normal operation, word operation */
/* and select TX to peripheral */
DMA0CON = 0x2020;
/* Set up the address of the peripheral ECAN1 (C1TXD) */
DMA0PAD = 0x0442;
/* Set the data block transfer size of 8 */
DMA0CNT = 7;
/* Automatic DMA TX initiation by DMA request */
DMA0REQ = 0x0046;
/* DPSRAM atart address offset value */
DMA0STA = __builtin_dmaoffset(&ecan1MsgBuf);
/* Enable the channel */
DMA0CONbits.CHEN = 1;
/* Initialize DMA Channel 2 for ECAN RX and clear the collision flags */
DMACS0 = 0;
/* Set up Channel 2 for Peripheral Indirect addressing mode (normal operation, word operation */
/* and select as RX to peripheral */
DMA2CON = 0x0020;
/* Set up the address of the peripheral ECAN1 (C1RXD) */
DMA2PAD = 0x0440;
/* Set the data block transfer size of 8 */
DMA2CNT = 7;
/* Automatic DMA Rx initiation by DMA request */
DMA2REQ = 0x0022;
/* DPSRAM atart address offset value */
DMA2STA = __builtin_dmaoffset(&ecan1MsgBuf);
/* Enable the channel */
DMA2CONbits.CHEN = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void bit_timing(void)
{
/* Set the Operating Frequency of the device to be 8MHz */
#define FCY 8000000
/* Set the ECAN module for Configuration Mode before writing into the Baud
Rate Control Registers*/
C1CTRL1bits.REQOP =4;
/* Wait for the ECAN module to enter into Configuration Mode */
while(C1CTRL1bits.OPMODE!= 4);
/* FCAN is selected to be Fosc by setting the CANCKS bit
 FCAN  = 8MHz */
C1CTRL1bits.CANCKS =0b0;

/* Baud Rate Prescaler bits set to 1:1, i.e., TQ = (2*2*1)/ FCAN */
C1CFG1bits.BRP =0b0001;

/* Phase Segment 2 time is set to be programmable */
C1CFG2bits.SEG2PHTS = 0b1;

/* Phase Segment 1 time is 7 TQ8 */
C1CFG2bits.SEG1PH =0b111;



/* Phase Segment 2 time is 6 TQ7 */
C1CFG2bits.SEG2PH = 0b110;

/* Propagation Segment time is 2 TQ */
C1CFG2bits.PRSEG = 0b01;

/* Bus line is sampled 1 time at the sample point */
C1CFG2bits.SAM = 0;

/* Synchronization Jump Width set to 1 TQ */
C1CFG1bits.SJW = 0;



/* Put the ECAN Module into Normal Mode Operating Mode*/
C1CTRL1bits.REQOP = 0b000;

/* Wait for the ECAN module to enter into Normal Operating Mode */
while(C1CTRL1bits.OPMODE!=0b000);
}


///////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////

void ecan_init(void)
{
TRISFbits.TRISF1=0;
TRISFbits.TRISF0=1;
dma_conf();
bit_timing();
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


///-------------------------------------------------------------------------------------
/*void __attribute__(( interrupt, auto_psv )) _C1Interrupt( void ) // CAN1 Event Interrupt 
{
	//Повторная инициализация CAN в случае ошибки
	if(C1INTFbits.ERRIF == 1)
	{
		ecan_init();
		C1INTFbits.ERRIF = 0;
	}

	IFS2bits.C1IF = 0;
}
*/

//-------------------------------------------------------------------------------------
/// 							ECAN (DMA2) Transmiter Interrupt
//-------------------------------------------------------------------------------------
/*void __attribute__(( interrupt, auto_psv )) _DMA2Interrupt( void ) //DMA2 Transmiter Interrupt 
{
	IFS1bits.DMA2IF = 0;
}*/


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------transmiting of initial settings on ECAN bus --------------------------------*/

void transmition_modes(unsigned int modeident,unsigned char T1 , unsigned char T2, unsigned char T3, unsigned char T4, unsigned int cycles ) 
{
unsigned int T1T2, T3T4, cycles1; //для преобразования типов

T1T2=T2;
T3T4=T4;

T1T2=(T1T2<<8);
T3T4=(T3T4<<8);

T1T2=T1T2+T1;
T3T4=T3T4+T3;

cycles1=cycles;

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

//unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));
DMA1STA= __builtin_dmaoffset(ecan1MsgBuf);

/* Configure Message Buffer 0 for Transmission and assign priority*/

C1TR01CONbits.TXEN0 = 0x1;				//Buffer 0 is a transmit buffer
C1TR01CONbits.TX0PRI = 0x3; 			//priority is intermidiate

/* WRITE TO MESSAGE BUFFER 0 */
/*CiTRBnSID = 0bxxx1 0010 0011 1100
IDE = 0b0
SRR = 0b0
SID<10:0>= 0b00011011000*/

ecan1MsgBuf[0][0] =modeident ;

/* CiTRBnEID = 0bxxxx 0000 0000 0000
EID<17:6> = 0b0000 0000 0000 */

ecan1MsgBuf[0][1] = 0b0;

/*CiTRBnDLC = 0b0000 0000 xxx0 0110
EID<17:6> = 0b000000;
RTR = 0b0;
RB1 = 0b0;
RB0 = 0b0;
DLC = 0b101 ;*/

ecan1MsgBuf[0][2] = 8;

/* WRITE MESSAGE DATA BYTES */
ecan1MsgBuf[0][3] = T1T2;
ecan1MsgBuf[0][4] = T3T4;
ecan1MsgBuf[0][5] = cycles1;
ecan1MsgBuf[0][6] = 0;



/* REQUEST MESSAGE BUFFER 0 TRANSMISSION */
C1TR01CONbits.TXREQ0 = 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------transmiting of commands data on ECAN bus --------------------------------*/

void transmition_command(unsigned char comm) 
{

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

//unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));r
DMA1STA= __builtin_dmaoffset(ecan1MsgBuf);

/* Configure Message Buffer 0 for Transmission and assign priority*/

C1TR01CONbits.TXEN0 = 0x1;				//Buffer 0 is a transmit buffer
C1TR01CONbits.TX0PRI = 0x3; 			//priority is intermidiate

/* WRITE TO MESSAGE BUFFER 0 */
/*CiTRBnSID = 0bxxx1 0010 0011 1100
IDE = 0b0
SRR = 0b0
SID<10:0>= 0b00000011000*/

ecan1MsgBuf[0][0] = 0b11100;

/* CiTRBnEID = 0bxxxx 0000 0000 0000
EID<17:6> = 0b0000 0000 0000 */

ecan1MsgBuf[0][1] = 0b0;

/*CiTRBnDLC = 0b0000 0000 xxx0 0001
EID<17:6> = 0b000000;
RTR = 0b0;
RB1 = 0b0;
RB0 = 0b0;
DLC = 0b1111 ;*/

ecan1MsgBuf[0][2] = 0b0000000000001000;

/* WRITE MESSAGE DATA BYTES */
ecan1MsgBuf[0][3] = comm;

/* REQUEST MESSAGE BUFFER 0 TRANSMISSION */
C1TR01CONbits.TXREQ0 = 1;

}




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



void conreceiveinit(void)
{
C1CTRL1bits.WIN =0x1;

C1FMSKSEL1bits.F0MSK=0x00;

C1RXM0SIDbits.SID=0b00001111000;

C1RXF0SIDbits.SID=0b00000000000;

C1RXM0SIDbits.MIDE=0x1;

C1RXF0SIDbits.EXIDE=0x0;

C1BUFPNT1bits.F0BP=0xA;

C1FEN1bits.FLTEN0=0x1;

C1CTRL1bits.WIN = 0x0;

/*
C1CTRL1bits.WIN =0x1;


C1FEN1bits.FLTEN0=1;
C1FEN1bits.FLTEN1=1;
C1FEN1bits.FLTEN2=1;
C1FEN1bits.FLTEN3=1;
C1FEN1bits.FLTEN4=1;
C1FEN1bits.FLTEN5=0;

C1RXF0SIDbits.SID=0b00000000000;
C1RXF1SIDbits.SID=0b01110000000;
C1RXF2SIDbits.SID=0b10110000000;
C1RXF3SIDbits.SID=0b11010000000;
C1RXF4SIDbits.SID=0b11100000000;

C1RXF0SIDbits.EXIDE=0;
C1RXF1SIDbits.EXIDE=0;
C1RXF2SIDbits.EXIDE=0;
C1RXF3SIDbits.EXIDE=0;
C1RXF4SIDbits.EXIDE=0;

C1RXM0SIDbits.MIDE=0b1;
C1RXM1SIDbits.MIDE=0b1;
C1RXM2SIDbits.MIDE=0b1;

C1RXM0SIDbits.SID=0b01110000000;
C1RXM1SIDbits.SID=0b11110000000;
C1RXM2SIDbits.SID=0b11110000000;




C1FMSKSEL1bits.F0MSK=0b00;
C1FMSKSEL1bits.F1MSK=0b00;
C1FMSKSEL1bits.F2MSK=0b00;
C1FMSKSEL1bits.F3MSK=0b00;
C1FMSKSEL1bits.F4MSK=0b00;

C1BUFPNT1bits.F0BP=0b0001;
C1BUFPNT1bits.F1BP=0b0010;
C1BUFPNT1bits.F2BP=0b0011;
C1BUFPNT1bits.F3BP=0b0011;
C1BUFPNT2bits.F4BP=0b0100;


C1CTRL1bits.WIN = 0;

C1TR01CONbits.TXEN0=0b0;
C1TR01CONbits.TXEN1=0b1;
C1TR23CONbits.TXEN2=0b1;
C1TR23CONbits.TXEN3=0b1;
C1TR45CONbits.TXEN4=0b1;
C1TR45CONbits.TXEN5=0b1;
*/
}

void can_read(unsigned int *ident,unsigned int *ms0,unsigned int *ms1,unsigned int *ms2,unsigned int *ms3,unsigned int *ms4,unsigned int *ms5,unsigned int *ms6,unsigned int *ms7)
{
if(C1RXFUL1bits.RXFUL10)
{
unsigned int iden=0, m0=0, m1=0, m2=0, m3=0, m4=0, m5=0, m6=0, m7=0;

iden=ecan1MsgBuf[10][0];
iden=(iden>>2);

m0=ecan1MsgBuf[10][3];
m0=(m0&0x00ff);
m1=ecan1MsgBuf[10][3];
m1=(m1>>8);

m2=ecan1MsgBuf[10][4];
m2=(m2&0x00ff);
m3=ecan1MsgBuf[10][4];
m3=(m3>>8);

m4=ecan1MsgBuf[10][5];
m4=(m4&0x00ff);
m5=ecan1MsgBuf[10][5];
m5=(m5>>8);

m6=ecan1MsgBuf[10][6];
m6=(m6&0x00ff);
m7=ecan1MsgBuf[10][6];
m7=(m7>>8);

C1RXFUL1bits.RXFUL10=0;


*ident=iden;
*ms0=m0;
*ms1=m1;
*ms2=m2;
*ms3=m3;
*ms4=m4;
*ms5=m5;
*ms6=m6;
*ms7=m7;

}
}