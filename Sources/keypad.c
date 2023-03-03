#include <hidef.h>         /* common defines and macros */
#include "derivative.h"    /* derivative-specific definitions */


// Declare and initialize variables
const unsigned char detectedKey[16] = {0xd7, 0xee, 0xde, 0xbe, 
                                       0xed, 0xdd, 0xbd, 0xeb, 
                                       0xdb, 0xbb, 0x7e, 0x7d, 
                                       0x7b, 0x77, 0xe7, 0xb7};
                                      
const unsigned char charAscii[16] = {'0', '1', '2', '3', 
                                    '4', '5', '6', '7', 
                                    '8', '9', 'A', 'B', 
                                    'C', 'D', '*', '#'};
                                                                        
const unsigned char keypadRows[4] = {0x0e,0x0d, 0x0b, 0x07};



// configure I/O ports
void KeypadInitialize(void)
{ 
   DDRA = 0x0F;   // assign lower nibble as output
   PUCR_PUPAE=1;  // enable pull-up resistors
}


// returns corresponding keypress ascii value
volatile char getKeypadAscii(unsigned char key)
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

// halts program thread for a few cyles
void delay(unsigned int millis)
{
   int index = 0;
   while (index <= millis)
   {
      index++;
   }
}

//  halts program thread until key is released
void KeyRelease(unsigned char previousRead)
{
   while (PORTA == previousRead)
   {
      // do nothing  
   }
}


// constantly polls keypad rows to detect key press
char GetKeyPress(void) 
{
   int i;
   char asciiValue;
   unsigned char readKey;
   
   for(i = 0; i < 4; i++)
   {
      PORTA =  keypadRows[i]; // write row bits to keypad port
      
      readKey = PORTA;
      readKey = PORTA;
      
      asciiValue =  getKeypadAscii(readKey);
      
      if (asciiValue != 0xff)
      {
         return 0xff;
      }
      return asciiValue;  
   }
}