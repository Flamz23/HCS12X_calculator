/***************************
*
*  Main Scheduler
*
****************************/
#include <hidef.h>         /* common defines and macros */
#include "derivative.h"    /* derivative-specific definitions */

extern unsigned int keypadReadFlg;

void Scheduler(void) 
{
   if (keypadReadFlg)
   {
      KeyRead(); // run keypad read function
      keypadReadFlg = 0; // reset flag
   }
}