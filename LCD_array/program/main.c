#include "MAIN.h"
#include "Sch51.h"
#include "2_01_12g.h"
#include "ledarray.h"
#include "game.h"

unsigned int count=0;

void main(){
	SCH_Init_T2();

	led_init();

	SCH_Add_Task(draw1,0,2);
	SCH_Add_Task(draw2,1,2);
	SCH_Add_Task(draw,0,34);

	SCH_Start();
	while(1){
		SCH_Dispatch_Tasks();
		button();
		if(350==count++){
			count=0;
			move();
		}	
	}
}