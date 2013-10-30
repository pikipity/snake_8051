#include <reg52.h>
#include "game.h"
#include "lcd12864.h"

unsigned char direct[]={2,2,2,2,2};//1:left  2:right  3:up  4:down
unsigned char snakex[]={60,61,62,63,64};
unsigned char snakey[]={32,32,32,32,32};
unsigned int snakelen=5;
unsigned char situation=0;//0: move  1: edge  2:eat
sbit leftb=P3^0;
sbit rightb=P3^1;
sbit upb=P3^2;
sbit downb=P3^3;

//unsigned char code finish_string[]={"×²Ç½¶øËÀ"};

void draw(void){
	unsigned char dotnum=0;
	first_page();
	if(situation==0){
		while(dotnum<snakelen){
			dotnum++;
			set_dot(snakex[dotnum],snakey[dotnum]);
		}
	}else if(situation==1){
		//display_string(2,2,finish_string);
		while(1);
	}
	
}

void button(void){
	if(!leftb){
		if(direct[snakelen-2]!=2){
			direct[snakelen-1]=1;
		}
	}else if(!rightb){
		if(direct[snakelen-2]!=1){
			direct[snakelen-1]=2;
		}
	}else if(!upb){
		if(direct[snakelen-2]!=4){
			direct[snakelen-1]=3;
		}
	}else if(!downb){
		if(direct[snakelen-2]!=3){
			direct[snakelen-1]=4;
		}
	}
}

void move(void){
	unsigned char i;
	//determien situation
	i=snakelen;
	switch(direct[i-1]){
		case 1: 
			if(snakex[i-1]==0){
				situation=1;
			} 
			break;
		case 2: 
			if(snakex[i-1]==127){
				situation=1;
			} 
			break;
		case 3: 
			if(snakey[i-1]==0){
				situation=1;
			} 
			break;
		case 4: 
			if(snakey[i-1]==63){
				situation=1;
			} 
			break;
		default: break;		
	}
	//move
	if(situation==0){
		for(i=0;i<snakelen;i++){
			switch(direct[i]){
				case 1: snakex[i]-=1;break;
				case 2: snakex[i]+=1;break;
				case 3: snakey[i]-=1;break;
				case 4: snakey[i]+=1;break;
				default: break;
			}
			if(i!=snakelen-1){
				direct[i]=direct[i+1];
			}
		}
	}
}

void rungame(){
	P1=~P1;
	move();
	draw();
}