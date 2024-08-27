#include "EncoderController.h"
#include <Arduino.h>

// EncoderController class implementation
EncoderController::EncoderController(int encoderPin1, int encoderPin2, int buttonPin)
    : encoderObject(encoderPin1, encoderPin2),
      sliderValue(512),
      muteState(0),
      buttonState(0),
      buttonPin(buttonPin) {}

void EncoderController::setup() {
    pinMode(buttonPin, INPUT_PULLUP);
}

void EncoderController::loop() {
    checkEncoder();
    checkButton();
}

void EncoderController::checkButton() {
    if (digitalRead(buttonPin) != LastEncoderButtonPress)
    {
        if ( digitalRead(buttonPin) == HIGH && buttonState == 0) {
            buttonState = 1;
            
        }
        else if ( digitalRead(buttonPin) == HIGH && buttonState == 1) {
            buttonState = 0;
        }
        LastEncoderButtonPress = digitalRead(buttonPin) ;
    }  
}

void EncoderController::checkEncoder() {
    long value = encoderObject.read(); // Adjust scale as needed

        if (0 < value && 102 > value) {
            sliderValue = value * 10;
        }
        else if (value <= 0){
            sliderValue = 0;
            encoderObject.write(0);
        }
        else if (value >= 102) {
            sliderValue = 1020; // Max slider value
            encoderObject.write(102);
        }

}

int EncoderController::getEncoderValue() {
    return sliderValue;
}

int EncoderController::getButtonState() {
    return buttonState;
}
