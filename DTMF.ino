#include <avr/interrupt.h>

int sensePin = 2;
int inputPin[] = {6, 7, 8, 9};
int outputPin = 13;
volatile int input = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(inputPin[i], INPUT);
  }
  attachInterrupt(digitalPinToInterrupt(sensePin), readData, RISING);
}

// Need to implement a circular queue to write input to from the interrupt handler.
void readData() {
  input = 0;
  for (int i = 0; i < 4; i++) {
    input |= digitalRead(inputPin[i]) << i;    
  }
}

// Need to implement a for loop to read from the queue and output to the serial port.
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(outputPin, input);
  Serial.println(input);
  delay(1);
}
