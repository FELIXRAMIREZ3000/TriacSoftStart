#include <TriacSoftStart.h>

TriacSoftStart bomba(2, 5, 4, 13);

void setup() {
  bomba.begin();
  attachInterrupt(digitalPinToInterrupt(2), zeroCrossISR, CHANGE);
}

void loop() {
  bomba.update();
}

void zeroCrossISR() {
  bomba.onZeroCross();
}