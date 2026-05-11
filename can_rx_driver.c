#include <LPC21xx.H>
#include "header2.h"
#define TCS ((C2GSR>>3)&1)
#define RBS (C2GSR&1)
extern u8 flag;
extern CAN1 m1;

void CAN1_RX_Handler(void) __irq  
{
    m1.id  = C2RID;                             
    m1.dlc = (C2RFS >> 16) & 0xF;                 
    m1.rtr = (C2RFS >> 30) & 1;      
    if (m1.rtr == 0)
    {
        m1.byteA = C2RDA;              
        m1.byteB = C2RDB;               
    }
    C2CMR = (1 << 2);                  
    flag = 1;                          
    VICVectAddr = 0;                   
}

void config_vic_for_CAN1(void)
{
    VICIntSelect = 0;                       
    VICVectCntl3 = 27 | (1 << 5);          
    VICVectAddr3 = (u32)CAN1_RX_Handler;   
    VICIntEnable = (1 << 27); 
    C2IER = 1;             
}

void can1_init(void)
{		 
	VPBDIV=1;
	PINSEL1|=0x00014000;      //P0.25-> RD1
	C2MOD=1;                  //select reset mode
	C2BTR=0x001C001D;         //Set 125Kbps baudrate
	AFMR=2;                   //accept all incoming messages
	C2MOD=0;                  //cancel reset mode
}
/*
void can1_rx(CAN1 *ptr)
{
	while(RBS==0);            //waiting for CAN msg to receive
  	ptr->id=C2RID;            //get id
  	ptr->rtr=(C2RFS>>30)&1;   //extract RTR
  	ptr->dlc=(C2RFS>>16)&0xF; //extract DLC
    ptr->ff=(C2RFS>>31)&1;    //extract ff
	if(ptr->rtr==0)
	{                         //if data-frame
		ptr->byteA=C2RDA;     //lower 4 byte data
		ptr->byteB=C2RDB;     //higher 4 byte data
	}
	C2CMR=0x4;                //release rxbuf		
}
  */
