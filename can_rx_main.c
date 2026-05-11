#include <LPC21xx.H>
#include "header2.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
CAN1 m1;
u8 flag;
						  
int main()
{
 	u8 f1=0,f2=0;
	can1_init();
	uart0_init(9600);
	config_vic_for_CAN1();
	IODIR0|=7<<17;       
	IOSET0|=7<<17;       
while(1)
{	
if(flag)
{
	  flag=0;
	 if(m1.id == 0x501)
      {
         if ((m1.byteA & 0xFF) == 0x10)     
         {  
		    IOCLR0 = LED1;
		    uart0_tx_string("HEAD LIGHT ON \n\r");
		 }                     
         else if ((m1.byteA & 0xFF) == 0x11)  
         {
		    IOSET0 = LED1;
		    uart0_tx_string("HEAD LIGHT OFF \n\r"); 
		 }                     
      }
     else if (m1.id == 0x502)
     { 	
         if ((m1.byteA & 0xFF) == 0x12)           
         {   
		     f2 = 1;
			 f1=0;
		     uart0_tx_string("LEFT INDICATOR ON\n\r");
		 }            
         else if ((m1.byteA & 0xFF) == 0x13) 
         {
		  	 uart0_tx_string("LEFT INDICATOR OFF\n\r");
             f2 = 0;             
             IOSET0 = LED2;      					                
	     }
     }         
	 else if (m1.id == 0x503)
	 {
         if ((m1.byteA & 0xFF) == 0x14)     
         {
		     f1 = 1;
			 f2=0; 
		     uart0_tx_string("RIGHT INDICATOR ON\n\r");   
		 }           
         else if((m1.byteA & 0xFF) == 0x15) 
		 {
		      uart0_tx_string("RIGHT INDICATOR OFF\n\r");
              f1 = 0;            
              IOSET0 = LED3;     
         }
     }
} 
       if(f2)              
       {
	   	uart0_tx_string("BLINKING\r\n");	
        IOCLR0 = LED2;              
        delay_ms(50);             
        IOSET0 = LED2;             
        delay_ms(50);			
       }
       if(f1)
       {
	    uart0_tx_string("BLINKING\r\n");
        IOCLR0 =LED3;              
        delay_ms(50);
        IOSET0 = LED3;
        delay_ms(50);																
       }       	
   }			
}  
