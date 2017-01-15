#include<Servo.h>
//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
int thPin = 0;
int led;
int speed;
Servo throttle;
int ledbar1[9] = {B00000000,
                  B00000001,
                  B00000011,
                  B00000111,
                  B00001111,
                  B00011111,
                  B00111111,
                  B01111111,
                  B11111111
                 };//all mode:1,3,7,15,31,63,127,255,511,1023,2047,4095
int ledbar2[5] = {B00000000,
                  B00000001,
                  B00000011,
                  B00000111,
                  B00001111,
                 };
void display(int i) {
  if (i <= 7) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ledbar2[0]);
    shiftOut(dataPin, clockPin, MSBFIRST, ledbar1[i]);

    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);

  }
  else if (i >= 8) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ledbar2[i- 7]);
    shiftOut(dataPin, clockPin, MSBFIRST, ledbar1[8]);

    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
  }
};
void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(thPin, INPUT);
  pinMode(9, OUTPUT);
  throttle.attach(9);
}

void loop() {
  speed = map(analogRead(thPin), 0, 1024, 0, 180);
  led = map(speed, 0, 180, 0, 12);
  throttle.write(speed);
  //ground latchPin and hold low for as long as you are transmitting
  display(led);
}
