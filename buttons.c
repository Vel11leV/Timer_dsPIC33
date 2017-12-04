#include "p33Fxxxx.h"
#include "words.h"
#include "initports.h"

//////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////////

void numb_ch(unsigned char x, unsigned char y,unsigned int *n_umb,unsigned int n,unsigned int Numbmax,unsigned int Numbmin)
{

if(SW19)
{
delay(20);
//if(*n_umb<60000)
if((*n_umb+1)<=Numbmax)
{*n_umb=*n_umb+1;}
number_out(x,y,*n_umb,n);
delay(100);
}

if(SW15)
{
delay(20);
//if(*n_umb>0)
if(*n_umb>=(Numbmin+1))
{*n_umb=*n_umb-1;};
number_out(x,y,*n_umb,n);
delay(100);
}
/////////////////////////

if(SW4)
{
delay(20);
//if(*n_umb<59991)
if((*n_umb+10)<=Numbmax)
{*n_umb=*n_umb+10;}
number_out(x,y,*n_umb,n);
delay(100);
}

if(SW12)
{
delay(20);
//if(*n_umb>9)
if(*n_umb>=(Numbmin+10))
{*n_umb=*n_umb-10;}
number_out(x,y,*n_umb,n);
delay(100);
}
////////////////////////
if(SW3)
{
delay(20);
//if(*n_umb<59901)
if((*n_umb+100)<=Numbmax)
{*n_umb=*n_umb+100;}
number_out(x,y,*n_umb,n);
delay(100);
}

if(SW11)
{
delay(20);
//if(*n_umb>99)
if(*n_umb>=(Numbmin+100))
{*n_umb=*n_umb-100;}
number_out(x,y,*n_umb,n);
delay(100);
}
}


////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////

void numb_ch_p(unsigned char x, unsigned char y,unsigned int *n_umb)
{

if(SW19)
{
delay(20);
if(*n_umb<255)
{*n_umb=*n_umb+1;}
number_p_out(x,y,*n_umb,3);
delay(100);
}

if(SW15)
{
delay(20);
if(*n_umb>0)
{*n_umb=*n_umb-1;};
number_p_out(x,y,*n_umb,3);
delay(100);
}
/////////////////////////

if(SW4)
{
delay(20);
if(*n_umb<246)
{*n_umb=*n_umb+10;}
number_p_out(x,y,*n_umb,3);
delay(100);
}

if(SW12)
{
delay(20);
if(*n_umb>9)
{*n_umb=*n_umb-10;}
number_p_out(x,y,*n_umb,3);
delay(100);
}
////////////////////////
if(SW3)
{
delay(20);
if(*n_umb<156)
{*n_umb=*n_umb+100;}
number_p_out(x,y,*n_umb,3);
delay(100);
}

if(SW11)
{
delay(20);
if(*n_umb>99)
{*n_umb=*n_umb-100;}
number_p_out(x,y,*n_umb,3);
delay(100);
}	
}
