#include <hidef.h>         /* common defines and macros */
#include "derivative.h"    /* derivative-specific definitions */

#define BIT_0 0x01         // bit 0 (0000 0001)
#define BIT_1 0x02         // bit 1 (0000 0010)
#define BIT_2 0x04         // bit 2 (0000 0100)
#define BIT_3 0x08         // bit 3 (0000 1000)
#define BIT_4 0x10         // bit 4 (0001 0000)
#define BIT_5 0x20         // bit 5 (0010 0000)
#define BIT_6 0x40         // bit 6 (0100 0000)
#define BIT_7 0x80         // bit 7 (1000 0000)

#define WAKE_UP 0x30       // wake command
#define LCD_MODE 0x38      // set LCD to 8-bit/2-line
#define CLEAR 0x01         // clears the display
#define CURSOR_BLNK 0x0F   // set cursor mode to blink
#define ENTRY_MODE 0x06    // set entry mode

#define PORT_BIT_HI(L,n) PORT##L |= BIT_##n    // set bit @ port
#define PORT_BIT_LO(L,n) PORT##L &= ~(BIT_##n) // clear bit @ port
  





// Initialize control registers and set required bits as output
void Initialize(void)
{
   /*
      EN: 1 -> 0 Latch command/data to clock
      R_W: (1 = read status, 0 = write to LCD)
      SEL: (1 = write char, 0 = write command)
   */
   DDRD |= (BIT_7|BIT_6|BIT_5); // EN|R_W|SEL
   DDRK = 0xFF; // set all bits as output
}



// Halts program execution until loop end
void Delay(unsigned long period)
{
   int count = 0;
   while(count < period) // repeat until period equals count
   {
      count++;  
   }
}



// Latch/Sync data to clock signal falling edge
void Latch(void) 
{
   PORT_BIT_HI(D,7);
   Delay(1);
   PORT_BIT_LO(D,7);  
}



// Writes command to LCD
void CommandWrite(unsigned char command) 
{
   PORTK = command;
   PORT_BIT_LO(D,6); // R_W write mode
   PORT_BIT_LO(D,5); // SEL command mode
   
   Latch();  
}



// Initialize display and send startup commands
void DisplayInit(void)
{
   PORT_BIT_LO(D,7); // Reset R_W line

   // startup sequence
   CommandWrite(WAKE_UP);
   Delay(100);
   CommandWrite(WAKE_UP);
   Delay(100);
   CommandWrite(WAKE_UP);
   Delay(100);
   CommandWrite(LCD_MODE);
   Delay(100);
   CommandWrite(CURSOR_BLNK);
   Delay(100);
   CommandWrite(CLEAR);
   Delay(100);
   CommandWrite(ENTRY_MODE);
   Delay(100); 
}


// Write single character to display
void CharWrite(char charData)
{
   Delay(2000);
   PORTK = charData;  // write char to port
   PORT_BIT_HI(D,5);   // SEL line low
   PORT_BIT_LO(D,6);   // write mode
   
   Latch();
}



// Write character string to display
void StringWrite(char *stringData)
{
   while(*stringData)
   {
      CharWrite(*stringData++);   // send next character
      
   }
}