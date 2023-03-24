#include <hidef.h>         /* common defines and macros */
#include "derivative.h"    /* derivative-specific definitions */
#include "protos.h"


void main(void) 
{
   KeypadInitialize();
   Initialize_RTI();  

   for(;;) 
   {
      Scheduler();
      
      _FEED_COP(); /* feeds the dog */
   } /* loop forever */
   /* please make sure that you never leave main */
}
