#include <reg52.h>
#include "game.h"
#include "ledarray.h"

static unsigned char direct[]={2,2,0,0,0,0,0,0};//1:left  2:right  3:up  4:down
static unsigned char snakex[]={0,1,17,17,17,17,17,17};
static unsigned char snakey[]={0,0,0,0,0,0,0,0};
static unsigned int snakelen=2;
static unsigned char situation=0;//0: move  1: edge  2:eat  4:win

unsigned char code die[]={//D
						  0x1E,0x32,0x62,0x42,0x42,0x62,0x32,0x1E,
						  //I
						  0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,
						  //E
						  0x7E,0x06,0x06,0x7E,0x7E,0x06,0x06,0x7E,
						  //!
						  0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x18
						  };

unsigned char code win[]={//W
						  0x81,0x81,0x99,0x99,0x99,0x99,0x99,0x66,
						  //I
						  0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,
						  //N
						  0xC7,0xCF,0xCB,0xDB,0xD3,0xF3,0xE3,0xE3,
						  //!
						  0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x18
						  };

unsigned char code foodx[]={0,8,10,5,4,15};
unsigned char code foody[]={8,8,0,0,5,12};
unsigned char food[]={1,1,1,1,1,1};

extern unsigned char LEDarraydata[];

sbit leftb=P3^4;
sbit rightb=P3^5;
sbit upb=P3^6;
sbit downb=P3^7;

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
	bit error=1;
	unsigned char j;
	bit havefood=0;
	//determien situation
	i=snakelen;
	switch(direct[i-1]){
		case 1: 
			if(snakex[i-1]==0){
				situation=1;
			}else if(read_dot(snakex[i-1]-1,snakey[i-1])){
				for(j=0;j<6;j++){
					if(snakex[i-1]-1==foodx[j] && snakey[i-1]==foody[j]){
						food[j]=0;
						snakex[snakelen]=snakex[i-1]-1;
						snakey[snakelen]=snakey[i-1];
						direct[snakelen]=direct[snakelen-1];
						snakelen++;
						error=0;
						situation=2;
						break;
					}
				}
				if (error){
					situation=1;
				}
			} 
			break;
		case 2: 
			if(snakex[i-1]==15){
				situation=1;
			}else if(read_dot(snakex[i-1]+1,snakey[i-1])){
				for(j=0;j<6;j++){
					if(snakex[i-1]+1==foodx[j] && snakey[i-1]==foody[j]){
						food[j]=0;
						snakex[snakelen]=snakex[i-1]+1;
						snakey[snakelen]=snakey[i-1];
						direct[snakelen]=direct[snakelen-1];
						snakelen++;
						error=0;
						situation=2;
						break;
					}
				}
				if (error){
					situation=1;
				}
			} 
			break;
		case 3: 
			if(snakey[i-1]==0){
				situation=1;
			}else if(read_dot(snakex[i-1],snakey[i-1]-1)){
				for(j=0;j<6;j++){
					if(snakex[i-1]==foodx[j] && snakey[i-1]-1==foody[j]){
						food[j]=0;
						snakex[snakelen]=snakex[i-1];
						snakey[snakelen]=snakey[i-1]-1;
						direct[snakelen]=direct[snakelen-1];
						snakelen++;
						error=0;
						situation=2;
						break;
					}
				}
				if (error){
					situation=1;
				}
			} 
			break;
		case 4: 
			if(snakey[i-1]==15){
				situation=1;
			}else if(read_dot(snakex[i-1],snakey[i-1]+1)){
				for(j=0;j<6;j++){
					if(snakex[i-1]==foodx[j] && snakey[i-1]+1==foody[j]){
						food[j]=0;
						snakex[snakelen]=snakex[i-1];
						snakey[snakelen]=snakey[i-1]+1;
						direct[snakelen]=direct[snakelen-1];
						snakelen++;
						error=0;
						situation=2;
						break;
					}
				}
				if (error){
					situation=1;
				}
			} 
			break;
		default: break;		
	}
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
	}else if(situation==2){
		for(i=0;i<6;i++){
			if(food[i]==1){
				havefood=1;
				situation=0;
				break;
			}
		}
		if(~havefood){
			situation=3;
		}
	}
}

void draw(void){
	unsigned char i;
	first_page();
	if(situation==0){
		for(i=0;i<snakelen;i++){
			set_dot(snakex[i],snakey[i]);
		}
		for(i=0;i<6;i++){
			if(food[i]){
				set_dot(foodx[i],foody[i]);
			}
		}
	}else if(situation==1){
		for(i=0;i<32;i++){
			LEDarraydata[i]=die[i];
		}
	}else if(situation==3){
		for(i=0;i<32;i++){
			LEDarraydata[i]=win[i];
		}
	}
}