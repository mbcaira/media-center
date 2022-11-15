#define osObjectsPublic
#include "osObjects.h"
#include "cmsis_os.h"
#include "Board_Joystick.h"
#include "GLCD.h"


extern const unsigned char FI;
extern const int debug;

void Menu (void const *argument);
void Gallery (void const *argument);
osThreadId menu_id, gallery_id;
osThreadDef (Menu, osPriorityNormal, 1, 0);
osThreadDef(Gallery, osPriorityBelowNormal, 1, 0);

int Menu_Start (void) {
  menu_id = osThreadCreate (osThread(Menu), NULL);
  if (!menu_id) return(-1);
  
  return(0);
}

void Menu (void const *argument) {
  int position = 0;
  while (1) {
	if (!debug) {
	  GLCD_SetBackColor(White);
	  GLCD_SetTextColor(Blue);
	  GLCD_DisplayString(4,3,FI, (unsigned char*)"Gallery");
	  GLCD_DisplayString(4,15,FI, (unsigned char*)"MP3");
	  GLCD_DisplayString(7,3,FI, (unsigned char*)"Games");
	  // State machine for joystick menu option selection
	  uint32_t stick_state = Joystick_GetState();
	  switch (position) {
		case 0: {
		  GLCD_SetBackColor(Blue);
		  GLCD_SetTextColor(White);
		  GLCD_DisplayString(4, 3, FI, (unsigned char *)"Gallery");
		  while (stick_state == Joystick_GetState()) {
			uint32_t old_state = stick_state;
			stick_state = Joystick_GetState();
			switch (stick_state) {
			  case JOYSTICK_RIGHT: position = 1;
				break;
			  case JOYSTICK_DOWN: position = 2;
				break;
			  default: stick_state = old_state;
			}
		  }
		  break;
		}
		case 1: {
		  GLCD_SetBackColor(Blue);
		  GLCD_SetTextColor(White);
		  GLCD_DisplayString(4, 15, FI, (unsigned char *)"MP3");
		  while (stick_state == Joystick_GetState()) {
			uint32_t old_state = stick_state;
			stick_state = Joystick_GetState();
			switch (stick_state) {
			  case JOYSTICK_LEFT: position = 0;
				break;
			  case JOYSTICK_DOWN: position = 2;
				break;
			  default: stick_state = old_state;
			}
		  }
		  break;
		}
		case 2: {
		  GLCD_SetBackColor(Blue);
		  GLCD_SetTextColor(White);
		  GLCD_DisplayString(7, 3, FI, (unsigned char *)"Games");
		  while (stick_state == Joystick_GetState()) {
			uint32_t old_state = stick_state;
			stick_state = Joystick_GetState();
			switch (stick_state) {
			  case JOYSTICK_UP: position = 0;
				break;
			  case JOYSTICK_RIGHT: position = 1;
				break;
			  default: stick_state = old_state;
			}
		  }
		  break;
		}
		default: break;
	  }
	}
  }
}
	

void Gallery(void const *argument) {
}
