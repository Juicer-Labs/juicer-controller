#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_1 7
#define RADIO_2 8
#define JOY_BUT 9
#define LED 12
#define JOY_X A0
#define JOY_Y A1
#define THROTTLE A2

RF24 radio(RADIO_1, RADIO_2); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

float ratio = 0.4255;

void setup() {
    Serial.begin(9600);

    pinMode(JOY_BUT, INPUT_PULLUP);
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(THROTTLE, INPUT);
    pinMode(LED, OUTPUT);

    //radio.begin();
    //radio.openWritingPipe(addresses[1]); // 00002
    //radio.openReadingPipe(1, addresses[0]); // 00001
    //radio.setPALevel(RF24_PA_MIN);

    //digitalWrite(LED, HIGH);
}

void loop() {
    int joyX = analogRead(JOY_X);
    int joyY = analogRead(JOY_Y);

    int throttle = analogRead(THROTTLE);

    if (digitalRead(JOY_BUT) == LOW) {
        Serial.println("button");
        digitalWrite(LED, HIGH);
    } else {
        Serial.println((String)"Joystick X: " + (joyX - 507) + ", Y: " + (joyY - 491) + ", Throttle: " + throttle);
        digitalWrite(LED, LOW);
    }

    delay(5);
    
    radio.stopListening();
    
    int turning = 0;

    if (joyX < 1023/3) {
        turning = -1;
    } else if (joyX > 1023*2/3) {
        turning = 1;
    }

    // Map the throttle and turning angle.
    int angleValue = map(joyX, 0, 1023, 0, 0.2);
    int throttleValue = map(throttle, 0, 1023, 0, 255);

    // Reset to avoid interference.
    if (throttleValue < 8) {
        throttleValue = 0;
    }

    // Motor speed set by throttle
    int leftSpeed = throttleValue, rightSpeed = throttleValue;

    // Handle turning.
    if (turning == -1) {
        leftSpeed *= ratio;
    } else if (turning == 1) {
        rightSpeed *= ratio;
    }

    // Send the throttle and turning angle.
    radio.write(&leftSpeed, sizeof(leftSpeed));
    radio.write(&rightSpeed, sizeof(rightSpeed));

    delay(5);

    radio.startListening();

    while (!radio.available());

    radio.read(&buttonState, sizeof(buttonState));

    if (buttonState == HIGH) {
        digitalWrite(LED, HIGH);
    }
    else {
        digitalWrite(LED, LOW);
    }
}


int calulateOuterWheelSpeed(int v1, int v2) {
    return 0;
}