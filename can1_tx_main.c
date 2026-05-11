#include<lpc21xx.h>
#include"header2.h"
CAN1 v1,v2,v3;
u8 tx_flagH=0;
u8 tx_flagL=0;
u8 tx_flagR=0;

int main()
{
u8 H_flag=0,L_flag=0,R_flag=0;
  can1_init();
  uart0_init(9600);
  config_vic_for_tx_eint0();
  config_vic_for_tx_eint1();
  config_vic_for_tx_eint2();
//-----------------------
	v1.id=0x501;
	v1.dlc=1;
	v1.rtr=0;     //data-frame
	v1.byteA=0x0;
	v1.byteB=0x0;
	v1.ff=0;
//-----------------------	
	v2.id=0x502;
	v2.dlc=1;
	v2.rtr=0;     //data-frame
	v2.byteA=0x0;
	v2.byteB=0x0;
	v2.ff=0;
//-----------------------	1
	v3.id=0x503;
	v3.dlc=1;
	v3.rtr=0;     //data-frame
	v3.byteA=0x0;
	v3.byteB=0x0;
	v3.ff=0;
 while(1)
 {	 
   if(tx_flagH==1)
   {
     tx_flagH=0;
	 H_flag ^=1;
	 if(H_flag)
	  {
	    v1.byteA=0x10;
	    uart0_tx_string("H ON\r\n");
	  }
	 else
	  {
	  v1.byteA=0x11;
	 uart0_tx_string("H OFF\r\n");
	  }
	 can1_tx(v1);
   }
 //------------------------------
  else if(tx_flagL==1)
  {
      tx_flagL=0;
	   L_flag^=1;
	  if(L_flag)
	   {
	    v2.byteA=0x12;
	    uart0_tx_string("L ON\r\n");
	   }
	  else
	  {
	    v2.byteA=0x13;
	    uart0_tx_string("L OFF\r\n");
	  }
	 can1_tx(v2);
  } 
 //------------------------------------
  else if(tx_flagR==1)
  {
       tx_flagR=0;
     	R_flag^=1;
	   if(R_flag)
	    {
	      v3.byteA=0x14;
	      uart0_tx_string("R ON\r\n");	
	    }
	   else
	    {
	     v3.byteA=0x15;
	     uart0_tx_string("R OFF\r\n");
	    }
	 can1_tx(v3);
  }
 }
}
