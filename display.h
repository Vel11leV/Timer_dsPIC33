#define RD   PORTGbits.RG15
#define WR   PORTGbits.RG12
#define DC   PORTGbits.RG13
#define CS   PORTGbits.RG14
#define RES  PORTCbits.RC1 
#define data_bus PORTE
#define _NOP asm("nop")
//volatile unsigned int i;
//#define _NOP {for(i=0;i<100;i++);}
#define ISDN  PORTAbits.RA0 

void port_conf(void);
void comm_out(unsigned char); 
void data_out(unsigned char i); 
void reset (void);
void IND_Lock(void);
void IND_Unlock(void);

void Refresh_Regs (void);
void init_OLED_GS_DC (void);
void write_RAM (void);
void disp_init (void);
unsigned char	data_read(void);

void frame1_out(void);
void symbol_out(unsigned char x, unsigned char y, unsigned char N);


void stroka_out(unsigned char x,unsigned char y, unsigned char N, unsigned char a[N] );
void symbol_numb_out(unsigned char x, unsigned char y,unsigned long int N);

void	displey_mask1(void);
void	displey_mask2(unsigned char mode);
void	displey_mask3(unsigned char mode,unsigned int T1,unsigned int T2, unsigned int cycle1);
void	displey_mask4(unsigned char mode,unsigned int T1,unsigned int T2, unsigned int cycle2);
void	displey_mask5(unsigned char mode,unsigned int T1,unsigned int T2, unsigned int T3, unsigned int T4, unsigned int cycle3);
void	displey_mask6(unsigned char mode,unsigned int T1,unsigned int T2, unsigned int T3);

void number_out(unsigned char x, unsigned char y,unsigned int N, unsigned char n);


void number_p_out(unsigned char x, unsigned char y,unsigned int N);
void line2_out(void);

void Scroll(unsigned int n);
void ModeExpl(unsigned char n);

void done_cyvles(unsigned int n);
void noth_done(void);
void paus(void);
void noth_paus(void);