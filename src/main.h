/** 
 ******************************************************************************
 * @file	: main.h
 * @version	: V0.0.1
 * @date	: 2023.06.12
 * @author	: Tony Liu
 ******************************************************************************
 *
 *
 *
 ****************************************************************************** 
 */
 
 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MAIN_H_
#define _MAIN_H_

/* Predefined Or Compiler Option ---------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Hardware Configuration ----------------------------------------------------*/
#define LED_OUTPUT_PIN 2
#define BUTTON_MODE_INPUT_PIN 5
#define BUTTON_LEFT_INPUT_PIN 18
#define BUTTON_RIGHT_INPUT_PIN 19

/* Define --------------------------------------------------------------------*/
/* Enum ----------------------------------------------------------------------*/
typedef enum {
  BUTTON_MODE,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_COUNT
}ButtonIndex;

typedef enum {
  MODE1,
  MODE2,
  MODE3,
  MODE_COUNT
}ModeIndex;
/* Marco ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
typedef struct {
  const int pin;
  unsigned long lastDebounceTime;
  int state;
  int lastState;
  bool pressed;
  void (*buttonAction[MODE_COUNT])();
}Button;

/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/


#endif
