#include <stdlib.h>
#include "Main.h"
#include "2_01_12g.H"
#include "lcd12864.h"
#include "game.h"

unsigned int count=0;

void main(void) {
  // Set up the scheduler 
  SCH_Init_T2();

  //init lcd
  lcd_init();
  draw();
  
  //add task
  SCH_Add_Task(button,0,20);
  //SCH_Add_Task(rungame,0,1000);


  //start task
  SCH_Start();

  while(1) {	   ;
		SCH_Dispatch_Tasks();
		//button();
		if(count++==200){
			rungame();
			count=0;
		}
  }
}