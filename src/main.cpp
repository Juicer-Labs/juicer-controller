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
    } else {
        Serial.println((String)"Joystick X: " + (joyX - 507) + ", Y: " + (joyY - 491) + ", Throttle: " + throttle);
    }

    // delay(5);
    
    // radio.stopListening();

    // int potValue = analogRead(A0);
    // int angleValue = map(potValue, 0, 1023, 0, 180);
    
    // radio.write(&angleValue, sizeof(angleValue));

    // delay(5);

    // radio.startListening();

    // while (!radio.available());

    // radio.read(&buttonState, sizeof(buttonState));

    // if (buttonState == HIGH) {
    //     digitalWrite(LED, HIGH);
    // }
    // else {
    //     digitalWrite(LED, LOW);
    // }
}