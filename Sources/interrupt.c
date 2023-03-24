#include <hidef.h>            /* common defines and macros */
#include "derivative.h"       /* derivative-specific definitions */
#include "defs.h"

#define ENABLE_INT asm cli
#define RTI_CONFIG 0x20

extern unsigned int keypadReadFlg;

// initialize the RTI
void Initialize_RTI(void)
{
   CRGINT_RTIE = 1; // set interrupt flag
   RTICTL = RTI_CONFIG; // configure RTI period   
   ENABLE_INT; // enable interrupts globlly   
}


// interupt handler subroutine
void interrupt InterruptHandler(void)
{
   CRGFLG_RTIF = 1; // set interrupt flag
   keypadReadFlg = 1; // set flag to trigger read
}