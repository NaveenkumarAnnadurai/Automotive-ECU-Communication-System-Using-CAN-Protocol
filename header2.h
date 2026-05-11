#include <LPC21xx.H>

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned char u8;
typedef signed char s8;

typedef struct CAN1_MSG{
	u32 id;
	u32 byteA;
	u32 byteB;
	u8 rtr;
	u8 dlc;
    u8 ff;	
}CAN1;

void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_tx_string(char *ptr);
void uart0_integer(int num);
void uart0_rx_string(unsigned char *ptr,int len);
void uart0_tx_float(double f);

void can1_init(void);
void can1_tx(CAN1 v);
void can1_rx(CAN1 *ptr);

void config_vic_for_tx_eint0(void);
void config_vic_for_tx_eint1(void);
void config_vic_for_tx_eint2(void);
void config_eint0(void);
void config_eint1(void);
void config_eint2(void);
void config_vic_for_CAN1(void);

void delay_sec(unsigned int sec);
void delay_ms(unsigned int ms);

