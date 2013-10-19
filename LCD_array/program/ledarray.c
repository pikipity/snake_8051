#include <reg52.h>
#include "ledarray.h"

unsigned char LEDarraydata[]={//LED1
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
			LEDdata=LEDarraydata[k1];
		}else{
			E1=0;
			E2=1;
			row12=k1<<3;
			LEDdata=LEDarraydata[k1+8];

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
			LEDdata=LEDarraydata[k2+16];
		}else{
			E3=0;
			E4=1;
			row34=k2<<3;
			LEDdata=LEDarraydata[k2+24];
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
		LEDarraydata[arry_row]|=rdata;
	}
}

bit read_dot(unsigned char x,unsigned char y){
	unsigned char xbit,ybit,screen,arry_row,ybyte,xbyte;
	unsigned char rdata;
	if(x<16 & y<16){
		xbyte=x/8;
		xbit=x%8;
		ybyte=y/8;
		ybit=y%8;
		//screen
		screen=ybyte*2+xbyte;
		//row
		arry_row=screen*8+ybit;
		//read
		rdata=LEDarraydata[arry_row]>>xbit;
		return rdata&0x01;
	}
}

void first_page(){
	unsigned char i;
	for(i=0;i<32;i++){
	LEDarraydata[i]=0x00;
	}
}