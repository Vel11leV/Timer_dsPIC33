

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

// unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));

/*-------------------------------*/

void dma_conf(void);
void bit_timing(void);
void ECAN_trans(void);
void ecan_init(void);

void transmition_modes(unsigned int modeident,unsigned char T1 , unsigned char T2, unsigned char T3, unsigned char T4, unsigned int cycles );
void transmition_command(unsigned char comm);
void conreceiveinit(void);
void can_read(unsigned int *ident,unsigned int *ms0,unsigned int *ms1,unsigned int *ms2,unsigned int *ms3,unsigned int *ms4,unsigned int *ms5,unsigned int *ms6,unsigned int *ms7);