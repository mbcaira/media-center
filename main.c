/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "GLCD.h"
#include "Board_LED.h"
#include "Board_Joystick.h"
#include "Board_ADC.h"

const int debug = 0;
const unsigned short FI = 1;

extern int Menu_Start(void);

/*
 * main: initialize and start the system
 */
int main(void) {
  osKernelInitialize();                    // initialize CMSIS-RTOS
  
  // initialize peripherals here
  if (!debug) {
	GLCD_Init();
	GLCD_Clear(White);                         /* Clear graphical LCD display   */
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0, 0, FI, (unsigned char *)"     COE718 Project     ");

	LED_Initialize();
	Joystick_Initialize();
  }

  Menu_Start();

  osKernelStart();
}
