#include <Arduino.h>

#define JOY_BUT 9
#define JOY_Y A1
#define JOY_X A0

void setup() {

    Serial.begin(9600);

    pinMode(JOY_BUT, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(JOY_X, INPUT);
}

void loop() {
    int joyY = analogRead(JOY_Y);
    int joyX = analogRead(JOY_X);

    Serial.println((String)"Joystick X: " + (joyX - 506) + ", Y: " + (joyY - 491));

    if (digitalRead(JOY_BUT) == HIGH) {
        Serial.println("button");
    }
}