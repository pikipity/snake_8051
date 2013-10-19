#include "MAIN.h"
#include "Sch51.h"
#include "2_01_12g.h"

#define LEDdata P0
#define row12 P1
#define row34 P2

sbit E1=P3^0;
sbit E2=P3^1;
sbit E3=P3^2;
sbit E4=P3^3;

unsigned char LEDarray[]={//LED1
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  //LED2
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  //LED3
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  //LED4
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00,
						  0x00};

void led_init(){
	E1=0;
	E2=0;
	E3=0;
	E4=0;
	LEDdata=0;
	row12=0;
	row34=0;
}

void draw1(){
		static unsigned char i1=1;
		static unsigned char k1=0;
		E3=0;
		E4=0;
		if(i1==1){
			E2=0;
			E1=1;
			row12=k1;
			LEDdata=LEDarray[k1];
		}else{
			E1=0;
			E2=1;
			row12=k1<<3;
			LEDdata=LEDarray[k1+8];

		}
		if(7==k1++){
			k1=0;
			if(2==i1++) i1=1;
		}
}

void draw2(){
	static unsigned char i2=1;
	static unsigned char k2=0;
	E1=0;
	E2=0;
	if(i2==1){
			E4=0;
			E3=1;
			row34=k2;
			LEDdata=LEDarray[k2+16];
		}else{
			E3=0;
			E4=1;
			row34=k2<<3;
			LEDdata=LEDarray[k2+24];
		}
		if(7==k2++){
			k2=0;
			if(2==i2++) i2=1;
		}
		
}

void set_dot(unsigned char x,unsigned char y){
	unsigned char xbit,ybit,screen,arry_row,rdata,ybyte,xbyte;
	if(x<16 & y<16){
		xbyte=x/8;
		xbit=x%8;
		ybyte=y/8;
		ybit=y%8;
		//screen
		screen=ybyte*2+xbyte;
		//row
		arry_row=screen*8+ybit;
		//data
		rdata=0x01<<xbit;
		//write
		LEDarray[arry_row]|=rdata;
	}
}

void clear_dot(unsigned char x,unsigned char y){
	unsigned char xbit,ybit,screen,arry_row,rdata,ybyte,xbyte;
	if(x<16 & y<16){
		xbyte=x/8;
		xbit=x%8;
		ybyte=y/8;
		ybit=y%8;
		//screen
		screen=ybyte*2+xbyte;
		//row
		arry_row=screen*8+ybit;
		//data
		rdata=0xFE<<xbit;
		//write
		LEDarray[arry_row]&=rdata;
	}
}

void main(){
	SCH_Init_T2();
	set_dot(0,0);
	set_dot(1,0);
	set_dot(0,1);
	set_dot(0,9);
	clear_dot(0,0);
	set_dot(9,0);
	set_dot(9,9);

	led_init();

	SCH_Add_Task(draw1,0,2);
	SCH_Add_Task(draw2,1,2);

	SCH_Start();
	while(1){
		SCH_Dispatch_Tasks();	
	}
}