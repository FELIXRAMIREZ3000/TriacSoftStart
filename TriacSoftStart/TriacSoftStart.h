#ifndef TRIAC_SOFT_START_H
#define TRIAC_SOFT_START_H

#include <Arduino.h>

class TriacSoftStart {
public:
  TriacSoftStart(uint8_t pinEntrada, uint8_t pinSalida, uint8_t pinControl, uint8_t pinLed);
  void begin();
  void update();
  void onZeroCross();
  void setPulseWidth(unsigned int us);
  void setInitialDelay(unsigned int us);
  void setFinalDelay(unsigned int us);
  void setRampStep(unsigned int us);

private:
  uint8_t entrada, salida, control, led;
  unsigned long retardo, retardoMin, paso;
  unsigned int pulso;
  bool rampaLista, salidaActiva, estadoLed, estadoPrevioControl;
  unsigned long ultimoParpadeo;
};

#endif