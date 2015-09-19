#include <QueueArray.h>

#include <avr/interrupt.h>

const int sensePin = 2;
const int inputPin[] = {6, 7, 8, 9};
const int outputPin = 13;
QueueArray<int> queue;

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
  int input = 0;
  for (int i = 0; i < 4; i++) {
    input |= digitalRead(inputPin[i]) << i;    
  }
  queue.enqueue(input);
}

// Need to implement a for loop to read from the queue and output to the serial port.
void loop() {
  // put your main code here, to run repeatedly:
  if (!queue.isEmpty()) {
    int input = queue.pop();
    digitalWrite(outputPin, input);
    Serial.println(input);
  }
  delay(1);
}
