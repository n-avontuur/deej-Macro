#include <Arduino.h>
#include "EncoderController.h"
#include "MacroKeypad.h"
#include "I2Cscreen.h"

enc1 = EncoderController(8, 9, 7);
enc1 = EncoderController(5, 6, 4);
MacroKeys = MacroKeypad();

void setup() {
    Serial.begin(9600);
    enc1.setup();
    enc2.setup();
    MacroKeys.setup();
}


void loop() {
    int enc1Value = enc1.getEncoderValue();
    int enc2Value = enc2.getEncoderValue();
    int enc1ButtonStatus = enc1.getButtonState();
    int enc2ButtonStatus = enc2.getButtonState();
    MacroKeys.loop();
    String activeKey = Macrokeys.getKey();

    Serial.print(enc1Value);
    Serial.print("||");
    Serial.print(enc1ButtonStatus);
    Serial.print("||");
    Serial.print(enc2Value);
    Serial.print("||");
    Serial.print(enc2ButtonStatus);
    Serial.print("||");
    Serial.print(activeKey);
    
   
}