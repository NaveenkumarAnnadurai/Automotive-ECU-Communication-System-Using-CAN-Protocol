#include<lpc21xx.h>
#include"header2.h"
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(unsigned int baud)
{
int pclk,result=0;
int a[]={15,60,30,15,30};
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);

PINSEL0|=0X05;
U0LCR=0X83;
U0DLL=result&0xFF;
U0DLM=(result>>8)&0xFF;
U0LCR=0x03;
}

void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

unsigned char uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}

void uart0_tx_string(char *ptr)
{
while(*ptr!=0)
{
uart0_tx(*ptr);
ptr++;
}
}

void uart0_integer(int num)
{
int a[10],i=0;
if(num==0)
{
 uart0_tx('0');
 return;
 }
 if(num<0)
 {
 num=-num;
 uart0_tx('-');
 }
 while(num>0)
 {
 a[i++]=num%10+48;
 num=num/10;
 }
 for(i=i-1;i>=0;i--)
 {
 uart0_tx(a[i]);
 }
}

void uart0_rx_string(unsigned char *ptr,int len)
{
		int i;
		for(i=0;i<len;i++)
		{
		while(RDR==0);
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')
		break;
		}
		ptr[i]='\0';
}
		
void uart0_tx_float(double f)
{
   int num;
   if(f==0)
   {
   uart0_tx_string("0.0");
	 }
	 if(f<0)
	 {

	  uart0_tx('-');
	  f=-f;
	 }
	 num=f;
	 uart0_integer(num);
	 uart0_tx('.');
	 num=(f-num)*100;
	 uart0_integer(num);
}
