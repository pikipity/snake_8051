#ifndef _LEDARRAY_H
#define _LEDARRAY_H

#define LEDdata P0
#define row12 P1
#define row34 P2

sbit E1=P3^0;
sbit E2=P3^1;
sbit E3=P3^2;
sbit E4=P3^3;

extern void led_init(void);
extern void draw1(void);
extern void draw2(void);
extern void set_dot(unsigned char x,unsigned char y);
extern bit read_dot(unsigned char x,unsigned char y);
extern void first_page(void);

#endif