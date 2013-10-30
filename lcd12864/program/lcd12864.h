#ifndef __REG51_H__
#define __REG51_H__

#define lcddata P0

sbit EN=P2^0;
sbit RW=P2^1;
sbit RS=P2^2;
sbit CS2=P2^3;
sbit CS1=P2^4;

//Basic functions
extern void lcd_write_command(unsigned char command);//write command to LCD
extern void lcd_write_data(unsigned char RWdata);//write data to LCD
extern unsigned char lcd_read_data(void);
extern void lcd_init(void);//LCD initialization
extern void first_page(void);//clear screen
//figure functions
extern void set_dot(unsigned char x,unsigned char y);

#endif