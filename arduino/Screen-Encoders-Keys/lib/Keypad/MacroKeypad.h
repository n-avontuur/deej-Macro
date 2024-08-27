#ifndef MACRO_KEYPAD_H
#define MACRO_KEYPAD_H
#include <Arduino.h>

class MacroKeypad {
  public:
    MacroKeypad();
    void setup();
    void loop();
    String getKey();
    
  private:
    String keyPressed(int row, int col);
    void resetKey(int row, int col);
    void resetState();
    
    int waitNextCycle;
    int electroSettleDownTime ;
    int debounceDelay;
    
    const unsigned long NORMAL_PRESS_DELAY  = 500; // 0. seconds
    const unsigned long LONG_PRESS_DELAY    = 250; // 0.5 second
    const unsigned long SPAM_PRESS_DELAY    = 100; // 0.25 seconds

    const unsigned long LONG_PRESS = 500; // 0.1 second
    const unsigned long SPAM_PRESS = 3000; // 0.2 seconds

    unsigned long currentTime = millis();
    unsigned long pressDuration = 0;
    unsigned long LastSpamPressTime = 0;
    unsigned long LastLongPressTime = 0;
    unsigned long LastNormalPressTime = 0;
    unsigned long FirstTimePressed = 0;
    unsigned long LastTimePressed = 0;
    unsigned long pressWait = 0;

    bool FirstPress = false;

    static const byte ROWS = 3;
    static const byte COLS = 4;
    
    const byte inputs[ROWS] = {10, 16, 14};
    const byte outputs[COLS] = {18, 19, 15, 20};
    
    String pressedKey = "";
  
    
    String LayoutValue = " ";
    String LastLayoutValue = " ";

    char layout[ROWS][COLS] = {
      {'1','2','3','4'},
      {'5','6','7','8'},
      {'9','/','=','*'}
    };
    
    int keyDown[COLS][ROWS];
    bool keyLong[COLS][ROWS];
};

#endif
