#ifndef ENCODERCONTROLLER_H
#define ENCODERCONTROLLER_H

#include <Encoder.h>

class EncoderController {
public:
    EncoderController(int encoderPin1, int encoderPin2, int buttonPin);
    void setup();
    void loop();
    int getEncoderValue();
    int getButtonState();

private:
    void checkEncoder();
    void checkButton();
    
    Encoder encoderObject;
    int sliderValue = 0;
    int muteState = 0;
    int buttonState = 0;
    int buttonPin = 0;

    int LastEncoderButtonPress;
};

#endif // ENCODERCONTROLLER_H
