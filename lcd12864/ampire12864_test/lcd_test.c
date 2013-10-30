#include <reg52.h>
#include <intrins.h>
#define lcddata P0
sbit EN=P2^0;
sbit RW=P2^1;
sbit RS=P2^2;
sbit CS2=P2^3;
sbit CS1=P2^4;

void delay(){
	_nop_();
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

void write_command(unsigned char command){
	check_busy();
	RS=0;
	RW=0;
	EN=0;
	lcddata=command;
	EN=1;
	delay();
	EN=0;
}

void write_data(unsigned char rdata){
	check_busy();
	RS=1;
	RW=0;
	EN=0;
	lcddata=rdata;
	EN=1;
	delay();
	EN=0;
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

void clear_screen(){
	unsigned char x,y;
	choose_screen(0);
	for(x=0xb8;x<0xc0;x++){
		write_command(x);
		write_command(0x40);
		for(y=0;y<64;y++){
			write_data(0);
		}
	}
}

void init_lcd(){
	write_command(0x3f);
	write_command(0xc0);
	write_command(0xb8);
	write_command(0x40);
} 

unsigned char read_data(){
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

unsigned char x=0xb8;
unsigned char y=0x40;
unsigned char rdata;

void main(){
	init_lcd();
	clear_screen();
	choose_screen(1);
	write_command(x|0);
	write_command(y|0);
	write_data(0x01<<0);
	while(1);
}