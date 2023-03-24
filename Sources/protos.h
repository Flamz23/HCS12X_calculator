/***************************
*
*  Prototype Definitions
*
****************************/

// keypad

void KeypadInitialize(void);

char Ascii(unsigned char);

void KeyRead(void);

// Interrupts

void Initialize_RTI(void);

void interrupt InterruptHandler(void);

// Scheduler

void Scheduler(void);