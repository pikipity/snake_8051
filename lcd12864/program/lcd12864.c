#include <reg52.h>
#include <string.h>
#include <intrins.h>
#include "lcd12864.h"

void delay(){
	_nop_();
}

void choose_screen(unsigned char screen){
	if(screen==0){//all screen
		CS1=0;
		CS2=0;
	}else if(screen==1){//left screen
		CS1=0;
		CS2=1;
	}else if(screen==2){//right screen
		CS1=1;
		CS2=0;
	}
}

void check_busy(){
	unsigned char count;
	RW=1;
	RS=0;
	EN=0;
	while(1){
		EN=1;
		if(!(lcddata&0x80)){
			break;
		}
		EN=0;
		if(count++>10){
			break;
		}
	}
	EN=0;
}

void lcd_write_command(unsigned char command){
	check_busy();
	RS=0;
	RW=0;
	EN=0;
	lcddata=command;
	EN=1;
	delay();
	EN=0;
}

void lcd_write_data(unsigned char rdata){
	check_busy();
	RS=1;
	RW=0;
	EN=0;
	lcddata=rdata;
	EN=1;
	delay();
	EN=0;
}

void lcd_init(void){
	lcd_write_command(0x3f);
	lcd_write_command(0xc0);
	lcd_write_command(0xb8);
	lcd_write_command(0x40);
}

void first_page(void){
	unsigned char x,y;
	choose_screen(0);
	for(x=0xb8;x<0xc0;x++){
		lcd_write_command(x);
		lcd_write_command(0x40);
		for(y=0;y<64;y++){
			lcd_write_data(0);
		}
	}
}

unsigned char lcd_read_data(){
	unsigned char rdata;
	check_busy();
	RS=1;
	RW=1;
	lcddata=0xFF;
	EN=1;
	rdata=lcddata;
	EN=0;
	check_busy();
	RS=1;
	RW=1;
	lcddata=0xFF;
	EN=1;
	rdata=lcddata;
	EN=0;
	return rdata;
}

void set_dot(unsigned char x,unsigned char y){
	unsigned char ybyte,rdata,xbit,ybit;
	if(x<128 && y<64){
	//choose screen
	choose_screen(x/64+1);
	//adjust x
	xbit=x%64;
	//choose row
	ybyte=y/8;
	//choose bit
	ybit=y%8;
	//read data and get rdata
	lcd_write_command(0xb8|ybyte);
	lcd_write_command(0x40|xbit);
	rdata=lcd_read_data();
	rdata=rdata|(0x01<<ybit);
	//write data
	lcd_write_command(0xb8|ybyte);
	lcd_write_command(0x40|xbit);
	lcd_write_data(rdata);
	}
}