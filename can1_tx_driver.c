#include<lpc21xx.h>
#include"header2.h"
extern u8 tx_flagL;
extern u8 tx_flagR;
extern u8 tx_flagH;
#define TCS ((C1GSR>>3)&1)

void can1_init(void)
{
	VPBDIV=1;            //60 Mhz
	PINSEL1|=0x00014000; //P0.25-> RD1
	C2MOD=1;             //select reset mode
	C2BTR=0x001C001D;    //Set 125Kbps baudrate
	AFMR=2;              //accept all incoming messages
	C2MOD=0;             //cancel reset mode
}

void can1_tx(CAN1 v)
{
	C2TID1=v.id;         //init id=0x123
	C2TFI1=(v.dlc<<16);  //init dlc=8, rtr=0, ff=0
	if(v.rtr==0){
	    C2TDA1=v.byteA;  //init data
		C2TDB1=v.byteB;  //init data
      }
	else
	C1TFI1|=(1<<30);     //rtr=1
	C2CMR=0x21;          //Select Txbuf1 & start xmission
	while(TCS==0);       //Monitor Txflag
}

void CAN1_TX_HANDLER1(void)__irq
{
 tx_flagL=1;
 EXTINT=1;
 VICVectAddr=0;
}

void CAN1_TX_HANDLER2(void)__irq
{
 tx_flagR=1;
 EXTINT=2;
 VICVectAddr=0;
}

void CAN1_TX_HANDLER3(void)__irq
{
 tx_flagH=1;
 EXTINT=4;
 VICVectAddr=0;
}

void config_vic_for_tx_eint0(void)
{
  PINSEL1|=1;              //P1.16
  EXTMODE|=1;
  EXTPOLAR=0;
  VICIntSelect=0;
  VICVectAddr0=(u32)CAN1_TX_HANDLER1;
  VICVectCntl0=14|(1<<5);
  VICIntEnable|=(1<<14);
}

void config_vic_for_tx_eint1(void)
{
  PINSEL0|=0x20000000;      //P0.14
  EXTMODE|=2;
  EXTPOLAR=0;
  VICIntSelect=0;
  VICVectAddr1= (u32)CAN1_TX_HANDLER2;
  VICVectCntl1=	15|(1<<5);
  VICIntEnable|=(1<<15);
}

void config_vic_for_tx_eint2(void)
{
  PINSEL0|=0x80000000;		//P0.15
  EXTMODE|=4;
  EXTPOLAR=0;
  VICIntSelect=0;
  VICVectAddr2= (u32)CAN1_TX_HANDLER3;
  VICVectCntl2=	16|(1<<5);
  VICIntEnable|=(1<<16);
}
