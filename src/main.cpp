/** 
 ******************************************************************************
 * @file	: main.cpp
 * @version	: V0.0.1
 * @date	: 2023.06.12
 * @author	: Tony Liu
 ******************************************************************************
 *
 *
 *
 ******************************************************************************
 */

/* Predefined Or Compiler Option ---------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <main.h>
#include <BleCombo.h>

/* Private Typedef -----------------------------------------------------------*/
static void mode1Action();
static void mode2Action();
static void mode3Action();

static void leftButtonMode1Action();
static void leftButtonMode2Action();
static void leftButtonMode3Action();

static void rightButtonMode1Action();
static void rightButtonMode2Action();
static void rightButtonMode3Action();

/* Private Prototype ---------------------------------------------------------*/
/* Private Define ------------------------------------------------------------*/
#define MAX_MOVE 127  // 滑鼠一次最多可以移動的距離
#define MIN_MOVE 8    // 滑鼠一次最少可以移動的距離

#define WEIGHT 1404   // 螢幕解析度寬度
#define HEIGHT 1872   // 螢幕解析度高度

#define MOUSE_ACTION_DELAY_MS 5  // 每次滑鼠動作的延遲時間

/* Private Enum --------------------------------------------------------------*/
/* Private Marco -------------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
static Button buttons[BUTTON_COUNT] = {
  {
    BUTTON_MODE_INPUT_PIN, 0, HIGH, HIGH, false, 
    {mode1Action, mode2Action, mode3Action}  
  },  // Mode button

  {
    BUTTON_LEFT_INPUT_PIN, 0, HIGH, HIGH, false, 
    {leftButtonMode1Action, leftButtonMode2Action, leftButtonMode3Action}
  },  // Left button
  
  {
    BUTTON_RIGHT_INPUT_PIN, 0, HIGH, HIGH, false, 
    {rightButtonMode1Action, rightButtonMode2Action, rightButtonMode3Action}
  }  // Right button
};

static ModeIndex currentMode = MODE1;
static const unsigned long debounceDelay = 50; // 防彈跳延遲時間
/* Public Variable -----------------------------------------------------------*/
/* Import Variable -----------------------------------------------------------*/
/* Import Function -----------------------------------------------------------*/
/* Private Function ----------------------------------------------------------*/
/**
 * @brief Blink the LED a specific number of times.
 *
 * This function will blink the LED connected to the defined pin 
 * a specific number of times with a delay in between the blinks. 
 * It will turn on the LED, wait for a specific delay, turn off the LED, 
 * and then wait for the delay again. This cycle repeats for the specified 
 * number of times.
 *
 * @param times The number of times the LED will blink.
 * @param delay_ms The delay in milliseconds between the blinks.
 */
static void blinkLed(int times, int delay_ms)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(LED_OUTPUT_PIN, HIGH);
    delay(delay_ms);
    digitalWrite(LED_OUTPUT_PIN, LOW);
    delay(delay_ms);
  }
}

/**
 * @brief Check the state of the button and perform debounce.
 * 
 * This function reads the state of the button, performs a software debounce to
 * eliminate any switch noise and updates the button state if it has been pressed.
 *
 * @param button Reference to the button object which state is to be checked.
 *
 * @note The button object should have 'pin', 'lastState', 'lastDebounceTime', 'state', and 'pressed'
 * attributes. The button pin should be set as input. The function updates the 'lastDebounceTime', 
 * 'state', 'lastState', and 'pressed' attributes of the button object. It sets 'pressed' to true if 
 * the button was pressed (i.e., state is LOW).
 */
static void checkButtonState(Button &button) {
  int reading = digitalRead(button.pin);
  if (reading != button.lastState) {
    button.lastDebounceTime = millis();
  }
  if ((millis() - button.lastDebounceTime) > debounceDelay) {
    if (reading != button.state) {
      button.state = reading;
      if (button.state == LOW) {
        button.pressed = true;
      }
    }
  }
  button.lastState = reading;
}

/**
 * @brief Moves the mouse cursor to the extreme left of the screen.
 * 
 * This function moves the mouse cursor to the extreme left of the screen in multiple steps, with 
 * each step moving by 'MAX_MOVE' units and then waiting for a delay of 'MOUSE_ACTION_DELAY_MS' milliseconds.
 * Finally, it moves the mouse cursor by the remaining distance, if any.
 *
 * @note The 'WEIGHT' parameter represents the total horizontal resolution (in pixels) of the screen. 
 * 'MAX_MOVE' is the maximum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds.
 */
static void moveMouseToExtremeLeft() {
  for (int i = 0; i < (WEIGHT / MAX_MOVE); i++) {
    Mouse.move(-MAX_MOVE, 0);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move(-(WEIGHT % MAX_MOVE), 0); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor to the extreme right of the screen.
 * 
 * This function moves the mouse cursor to the extreme right of the screen in multiple steps, with 
 * each step moving by 'MAX_MOVE' units and then waiting for a delay of 'MOUSE_ACTION_DELAY_MS' milliseconds.
 * Finally, it moves the mouse cursor by the remaining distance, if any.
 *
 * @note The 'WEIGHT' parameter represents the total horizontal resolution (in pixels) of the screen. 
 * 'MAX_MOVE' is the maximum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds.
 */
static void moveMouseToExtremeRight() {
  for (int i = 0; i < (WEIGHT / MAX_MOVE); i++) {
    Mouse.move(MAX_MOVE, 0);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move((WEIGHT % MAX_MOVE), 0); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor to the top of the screen.
 * 
 * This function moves the mouse cursor to the extreme top of the screen in multiple steps. 
 * Each step moves the cursor by 'MAX_MOVE' units upwards and then waits for a delay of 
 * 'MOUSE_ACTION_DELAY_MS' milliseconds. Finally, it moves the mouse cursor by the remaining 
 * vertical distance, if any.
 *
 * @note The 'HEIGHT' parameter represents the total vertical resolution (in pixels) of the screen. 
 * 'MAX_MOVE' is the maximum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds.
 */
static void moveMouseToExtremeTop() {
  for (int i = 0; i < (HEIGHT / MAX_MOVE); i++) {
    Mouse.move(0, -MAX_MOVE);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move(0, -(HEIGHT % MAX_MOVE)); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor to the middle of the screen in the vertical axis.
 * 
 * This function moves the mouse cursor to the middle height of the screen in multiple steps. 
 * Each step moves the cursor by 'MAX_MOVE' units downwards and then waits for a delay of 
 * 'MOUSE_ACTION_DELAY_MS' milliseconds. Finally, it moves the mouse cursor by the remaining 
 * vertical distance, if any.
 *
 * @note The 'HEIGHT' parameter represents the total vertical resolution (in pixels) of the screen. 
 * 'MAX_MOVE' is the maximum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds.
 */
static void moveMouseToMiddleHeight() {
  for (int i = 0; i < ((HEIGHT / 2) / MAX_MOVE); i++) {
    Mouse.move(0, MAX_MOVE);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move(0, ((HEIGHT / 2) % MAX_MOVE)); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor to the center of the screen in the horizontal axis.
 * 
 * This function moves the mouse cursor to the middle width of the screen in multiple steps. 
 * Each step moves the cursor by 'MAX_MOVE' units to the right and then waits for a delay of 
 * 'MOUSE_ACTION_DELAY_MS' milliseconds. Finally, it moves the mouse cursor by the remaining 
 * horizontal distance, if any.
 *
 * @note The 'WEIGHT' parameter represents the total horizontal resolution (in pixels) of the screen. 
 * 'MAX_MOVE' is the maximum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds.
 */
static void moveMouseToMiddleWidth() {
  for (int i = 0; i < (WEIGHT / 2) / MAX_MOVE; i++) {
    Mouse.move(MAX_MOVE, 0);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move((WEIGHT / 2) % MAX_MOVE, 0);
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor slowly to the extreme left of the screen.
 * 
 * This function moves the mouse cursor to the extreme left of the screen in multiple steps. 
 * Each step moves the cursor by 'MIN_MOVE' units to the left and then waits for a delay of 
 * 'MOUSE_ACTION_DELAY_MS' milliseconds. Finally, it moves the mouse cursor by the remaining 
 * horizontal distance, if any.
 *
 * @note The 'WEIGHT' parameter represents the total horizontal resolution (in pixels) of the screen. 
 * 'MIN_MOVE' is the minimum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds. This function is designed for slower cursor movement.
 */
static void slowMoveMouseToExtremeLeft() {
  for (int i = 0; i < (WEIGHT / MIN_MOVE); i++) {
    Mouse.move(-MIN_MOVE, 0);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move(-(WEIGHT % MIN_MOVE), 0); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Moves the mouse cursor slowly to the extreme right of the screen.
 * 
 * This function moves the mouse cursor to the extreme right of the screen in multiple steps. 
 * Each step moves the cursor by 'MIN_MOVE' units to the right and then waits for a delay of 
 * 'MOUSE_ACTION_DELAY_MS' milliseconds. Finally, it moves the mouse cursor by the remaining 
 * horizontal distance, if any.
 *
 * @note The 'WEIGHT' parameter represents the total horizontal resolution (in pixels) of the screen. 
 * 'MIN_MOVE' is the minimum distance the cursor can move in one step, and 'MOUSE_ACTION_DELAY_MS' 
 * is the delay between each step in milliseconds. This function is designed for slower cursor movement.
 */
static void slowMoveMouseToExtremeRight() {
  for (int i = 0; i < (WEIGHT / MIN_MOVE); i++) {
    Mouse.move(MIN_MOVE, 0);
    delay(MOUSE_ACTION_DELAY_MS);
  }
  Mouse.move((WEIGHT % MIN_MOVE), 0); // 移動剩下的距離
  delay(MOUSE_ACTION_DELAY_MS);
}

/**
 * @brief Performs the actions specific to the 1st mode.
 * 
 */
static void mode1Action(){
  Serial.println("MODE2");
  currentMode = MODE2;
  blinkLed((int)currentMode + 1, 100);
}

/**
 * @brief Performs the actions specific to the 2nd mode.
 * 
 */
static void mode2Action() {
  Serial.println("MODE3");
  currentMode = MODE3;
  blinkLed((int)currentMode + 1, 100);
}

/**
 * @brief Performs the actions specific to the 3rd mode.
 * 
 */
static void mode3Action() {
  Serial.println("MODE1");
  currentMode = MODE1;
  blinkLed((int)currentMode + 1, 100);
}

/**
 * @brief Handles the action of the left button press in Mode 1.
 *
 * This function specifies the sequence of actions to be performed when the
 * left button is pressed while the device is in Mode 1.
 * The mouse is moved to the extreme left and top positions, then to the 
 * middle of the screen height-wise. After these movements, a left click
 * is performed.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions, 
 * causing the LED to blink once with a delay of 10 milliseconds.
 * The individual movements of the mouse are performed by helper functions 
 * 'moveMouseToExtremeLeft()', 'moveMouseToExtremeTop()', and 'moveMouseToMiddleHeight()'.
 */
static void leftButtonMode1Action() {
  moveMouseToExtremeLeft();
  moveMouseToExtremeTop();
  moveMouseToMiddleHeight();
  Mouse.click(MOUSE_LEFT);
  blinkLed(1, 10);
}

/**
 * @brief Handles the action of the left button press in Mode 2.
 *
 * This function specifies the sequence of actions to be performed when the
 * left button is pressed while the device is in Mode 2.
 * It simulates the pressing of the left arrow key on a keyboard.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions, 
 * causing the LED to blink once with a delay of 10 milliseconds.
 * The key press and release actions are handled by 'Keyboard.press()' and 'Keyboard.releaseAll()' respectively.
 */
static void leftButtonMode2Action() {
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
  blinkLed(1, 10);
}

/**
 * @brief Handles the action of the left button press in Mode 3.
 *
 * This function specifies the sequence of actions to be performed when the
 * left button is pressed while the device is in Mode 3. 
 * It simulates a mouse drag from left to right across the screen.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions,
 * causing the LED to blink once with a delay of 10 milliseconds.
 * The mouse dragging actions are started and ended by 'Mouse.press()' and 'Mouse.release()' respectively.
 * The mouse is moved to extreme left, extreme top and then to the middle of height by invoking 
 * 'moveMouseToExtremeLeft()', 'moveMouseToExtremeTop()', and 'moveMouseToMiddleHeight()' functions respectively. 
 * Then 'slowMoveMouseToExtremeRight()' function is called to simulate a slow mouse move to the extreme right. 
 */
static void leftButtonMode3Action() {
  moveMouseToExtremeLeft();
  moveMouseToExtremeTop();
  moveMouseToMiddleHeight();
  Mouse.press(MOUSE_LEFT); // Start dragging
  delay(MOUSE_ACTION_DELAY_MS);
  slowMoveMouseToExtremeRight();
  Mouse.release(MOUSE_LEFT); // End dragging
  blinkLed(1, 10);
}

/**
 * @brief Handles the action of the right button press in Mode 1.
 *
 * This function specifies the sequence of actions to be performed when the
 * right button is pressed while the device is in Mode 1. 
 * It simulates a mouse click at the middle-right side of the screen.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions,
 * causing the LED to blink once with a delay of 10 milliseconds.
 * The mouse is moved to the extreme right, extreme top and then to the middle of height by invoking 
 * 'moveMouseToExtremeRight()', 'moveMouseToExtremeTop()', and 'moveMouseToMiddleHeight()' functions respectively. 
 * Then a left mouse click is simulated by 'Mouse.click()' function. 
 */
static void rightButtonMode1Action() {
  moveMouseToExtremeRight();
  moveMouseToExtremeTop();
  moveMouseToMiddleHeight();
  Mouse.click(MOUSE_LEFT);
  blinkLed(1, 10);
}

/**
 * @brief Handles the action of the right button press in Mode 2.
 *
 * This function specifies the action to be performed when the right button 
 * is pressed while the device is in Mode 2.
 * It simulates the pressing of the right arrow key on the keyboard.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions,
 * causing the LED to blink once with a delay of 10 milliseconds.
 * 'Keyboard.press()' function is used to simulate the pressing of the right arrow key.
 * All the pressed keys are released by 'Keyboard.releaseAll()' function.
 */
static void rightButtonMode2Action() {
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.releaseAll();
  blinkLed(1, 10);
}

/**
 * @brief Handles the action of the right button press in Mode 3.
 *
 * This function specifies the sequence of actions to be performed when the
 * right button is pressed while the device is in Mode 3. 
 * It simulates a mouse drag from right to left across the screen.
 *
 * @note The 'blinkLed()' function is invoked at the end of these actions,
 * causing the LED to blink once with a delay of 10 milliseconds.
 * The mouse dragging actions are started and ended by 'Mouse.press()' and 'Mouse.release()' respectively.
 * The mouse is moved to extreme right, extreme top and then to the middle of height by invoking 
 * 'moveMouseToExtremeRight()', 'moveMouseToExtremeTop()', and 'moveMouseToMiddleHeight()' functions respectively. 
 * Then 'slowMoveMouseToExtremeLeft()' function is called to simulate a slow mouse move to the extreme left. 
 */
static void rightButtonMode3Action() {
  moveMouseToExtremeRight();
  moveMouseToExtremeTop();
  moveMouseToMiddleHeight();
  Mouse.press(MOUSE_LEFT); // Start dragging
  delay(MOUSE_ACTION_DELAY_MS);
  slowMoveMouseToExtremeLeft();
  Mouse.release(MOUSE_LEFT); // End dragging
  blinkLed(1, 10);
}
/* Public Function -----------------------------------------------------------*/
void setup() {
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(921600);

  pinMode(LED_OUTPUT_PIN, OUTPUT);

  for (int button = 0; button < BUTTON_COUNT; button++) {
    pinMode(buttons[button].pin, INPUT_PULLUP);
  }
}

void loop() {
  if(!Keyboard.isConnected())
    return;

  for (int i = 0; i < BUTTON_COUNT; i++) {
    checkButtonState(buttons[i]);
    if (buttons[i].pressed) {
      buttons[i].pressed = false;
      buttons[i].buttonAction[currentMode]();
    }
  }
}
