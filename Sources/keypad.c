#include <hidef.h>         /* common defines and macros */
#include "derivative.h"    /* derivative-specific definitions */


// Declare and initialize variables
extern char keyPress;

const unsigned char detectedKey[16] = {0xd7, 0xee, 0xde, 0xbe, 
                                       0xed, 0xdd, 0xbd, 0xeb, 
                                       0xdb, 0xbb, 0x7e, 0x7d, 
                                       0x7b, 0x77, 0xe7, 0xb7};                                     
const unsigned char charAscii[16] = {'0', '1', '2', '3', 
                                    '4', '5', '6', '7', 
                                    '8', '9', 'A', 'B', 
                                    'C', 'D', '*', '#'};                                                                        
const unsigned char keypadRows[4] = {0x0e,0x0d, 0x0b, 0x07};
const unsigned int numRows = 4; // number of rows

// configure I/O ports
void KeypadInitialize(void)
{ 
   DDRA = 0x0F; // assign lower nibble as output
   PUCR_PUPAE=1; // enable pull-up resistors
}


// returns corresponding keypress ascii value
volatile char Ascii(unsigned char key)
{
   int i;
   for (i = 0; i < 16; i++) 
   {
      if(key == detectedKey[i])
      {
         return charAscii[i];
      }
   }
   
   return 0xff; // return 0xff if key missing
}

// reads key off PORTA and updates Keypress
void KeyRead(void)
{
   int i;
   for(i = 0; i < numRows; i++)
   {
      PORTA =  keypadRows[i]; // write row bits to keypad port 
      
      // read the upper bits to find letter
      keyPress =  Ascii(PORTA);
      keyPress =  Ascii(PORTA);
   }  
}