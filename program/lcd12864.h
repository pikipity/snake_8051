#ifndef __REG51_H__
#define __REG51_H__

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;

#define LCDb_BASCMD   0x30     // 基本指令集
#define LCDb_CLS   0x01     // 清屏
#define LCDb_HOME   0x02     // 地址返回原点，不改变DDRAM内容
#define LCDb_ENTRY   0x06     // 设定输入模式，光标加，屏幕不移动
#define CurserRight 0x04

#define LCDb_CURON     0x0E     // 显示光标
#define LCDb_CURFLA   0x0F     // 打开光标闪烁
#define LCDb_C2L   0x10     // 光标左移
#define LCDb_C2R   0x14     // 光标右移
#define LCDb_D2L   0x18     // 屏幕左移
#define LCDb_D2R   0x1C     // 屏幕又移
#define LCDb_ON     0x0C     // 打开显示
#define LCDb_OFF   0x08         // 关闭显示

#define LCDb_EXTCMD1   0x34     // 扩充指令集，关闭绘图显示
#define LCDb_EXTCMD2   0x36     // 扩充指令集，打开绘图显示
#define LCDb_EXTCLS   0x01     // 清屏
#define LCDb_REVL1   0x04     // 反显第1行
#define LCDb_REVL2   0x05     // 反显第2行
#define LCDb_REVL3   0x06     // 反显第3行
#define LCDb_REVL4   0x07     // 反显第4行
#define sleep   0x08     // 睡眠模式
#define Dissleep   0x0C     // 脱离睡眠模式

//Basic functions
extern void delayus(unsigned int t);
extern void lcd_write_command(unsigned char command);//write command to LCD
extern void lcd_write_data(unsigned char RWdata);//write data to LCD
extern unsigned char lcd_read_data(void);//read data from LCD
extern void lcd_init(void);//LCD initialization
extern void first_page(void);//clear screen

//string functions
extern void display_string(unsigned char line,unsigned char space,unsigned char *string);//display string (default string function.)
extern void display_string_58(unsigned char x,unsigned char y,unsigned char *string,unsigned int drgree);//display ASCII for 5*8 size

//figure functions
extern void set_dot(unsigned char x,unsigned char y);
extern void clear_dot(unsigned char x,unsigned char y);
//basic shapes
extern void draw_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//draw a line
extern void draw_box(unsigned char x,unsigned char y,unsigned char num_x,unsigned char num_y,bit fill);//draw a box
extern void draw_frame(void);//draw the frame
extern void draw_circle(unsigned char x,unsigned char y,unsigned char r,bit fill);//draw circle
//draw picture
//one line picture
extern void draw_8bits(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis
extern void draw_8bits90(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis	but in 90 degree change system
extern void draw_8bits180(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis but in 180 degree change system
extern void draw_8bits270(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis but in 270 degree change system
//mutiple line s picture
extern void draw_picture(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture
extern void draw_picture90(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 90 degree
extern void draw_picture180(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 180 degree
extern void draw_picture270(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 270 degree
#endif