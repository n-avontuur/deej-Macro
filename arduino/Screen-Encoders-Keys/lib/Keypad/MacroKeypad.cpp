#include "MacroKeypad.h"

MacroKeypad::MacroKeypad() {
    resetState();
}

void MacroKeypad::setup() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            resetKey(j, i);
        }
    }

    for (int i = 0; i < COLS; i++) {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], HIGH);
    }

    for (int i = 0; i < ROWS; i++) {
        pinMode(inputs[i], INPUT_PULLUP);
    }

    Serial.begin(9600);
}

void MacroKeypad::loop() {
    currentTime = millis();
    pressedKey = "0";

    for (int i = 0; i < COLS; i++) {
        digitalWrite(outputs[i], LOW);
        delayMicroseconds(electroSettleDownTime);

        for (int j = 0; j < ROWS; j++) {
            if (digitalRead(inputs[j]) == LOW) {
                delay(debounceDelay);
                if (digitalRead(inputs[j]) == LOW) {
                    pressedKey = keyPressed(j, i);
                }
            } else {
                resetKey(j, i);
            }
        }
        digitalWrite(outputs[i], HIGH);
        delayMicroseconds(waitNextCycle);
    }

    // Reset the state if the same key has not been pressed for 1.5 seconds
    if (currentTime - LastTimePressed > 1500) {
        resetState();
    }
}


String MacroKeypad::getKey() {
    return pressedKey;
}

String MacroKeypad::keyPressed(int row, int col) {
    String message = " ";
    String layoutValue = String(layout[row][col]);
    LastTimePressed = currentTime;
    currentTime = millis();

    // if (LastLayoutValue != layoutValue) {
    //     FirstTimePressed = currentTime;
    //     FirstPress = true;
    //     pressWait = 0;
    // } else {
    //     pressWait = currentTime - LastTimePressed;
    // }

    // LastLayoutValue = layoutValue;
    
    //pressDuration = currentTime - FirstTimePressed;
    // if (pressWait > 100){
    //     FirstTimePressed = currentTime;
    //     FirstPress = true;
    // }
    // if (pressDuration > SPAM_PRESS) {
    //     //if (currentTime - LastSpamPressTime >= SPAM_PRESS_DELAY) {
    //         LastSpamPressTime = currentTime;
    //         message = layoutValue;
    //     //}
    // } else if (pressDuration > LONG_PRESS) {
    //     //if (currentTime - LastLongPressTime >= LONG_PRESS_DELAY) {
    //         LastLongPressTime = currentTime;
    //         message =  layoutValue;
    //     //}
    // } else if (FirstPress) {
    //     //if (currentTime - LastLongPressTime >= NORMAL_PRESS_DELAY){
    //         message = layoutValue;
    //     // } 
    // }
    message = layoutValue;
    return message;
}

void MacroKeypad::resetKey(int row, int col) {
    keyDown[row][col] = 0;
    keyLong[row][col] = false;
}

void MacroKeypad::resetState() {
    FirstTimePressed = 0;
    LastTimePressed = 0;
    LastSpamPressTime = 0;
    LastLongPressTime = 0;
    pressWait = 0;
    pressedKey = "0";
    LastLayoutValue = " ";
}
