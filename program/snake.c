#include <stdlib.h>
#include "Main.h"
#include "2_01_12g.H"
#include "lcd12864.h"
#include "game.h"

void main(void) {
  // Set up the scheduler 
  SCH_Init_T2();

  //init lcd
  lcd_init();
  game_init();
  
  //add task
  //SCH_Add_Task(draw, 0, 20);
  SCH_Add_Task(move, 0, 500);
  SCH_Add_Task(draw,0,20);


  //start task
  SCH_Start();

  while(1) {
		SCH_Dispatch_Tasks();
		button();
  }
}