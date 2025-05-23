#include "TriacSoftStart.h"

TriacSoftStart::TriacSoftStart(uint8_t pinEntrada, uint8_t pinSalida, uint8_t pinControl, uint8_t pinLed)
  : entrada(pinEntrada), salida(pinSalida), control(pinControl), led(pinLed) {}

void TriacSoftStart::begin() {
  pinMode(entrada, INPUT);
  pinMode(salida, OUTPUT);
  pinMode(control, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  digitalWrite(salida, LOW);
  digitalWrite(led, LOW);

  retardo = 7850;
  retardoMin = 550;
  paso = 5;
  pulso = 400;

  rampaLista = false;
  salidaActiva = false;
  estadoLed = false;
  estadoPrevioControl = HIGH;
  ultimoParpadeo = millis();
}

void TriacSoftStart::update() {
  bool estadoActualControl = digitalRead(control);

  if (estadoActualControl == LOW) {
    rampaLista = false;
    salidaActiva = false;
    retardo = 7850;
    digitalWrite(salida, LOW);
    digitalWrite(led, LOW);
    return;
  }

  if (estadoPrevioControl == LOW && estadoActualControl == HIGH) {
    rampaLista = false;
    salidaActiva = false;
    retardo = 7850;
  }

  estadoPrevioControl = estadoActualControl;

  unsigned long intervalo = rampaLista ? 500 : 100;
  if (millis() - ultimoParpadeo >= intervalo) {
    ultimoParpadeo = millis();
    estadoLed = !estadoLed;
    digitalWrite(led, estadoLed);
  }
}

void TriacSoftStart::onZeroCross() {
  if (digitalRead(control) == LOW) return;

  if (!rampaLista) {
    unsigned int cuentas = retardo * 2;
    cli(); TCNT1 = 0; OCR1A = cuentas; TIFR1 |= (1 << OCF1A); TIMSK1 |= (1 << OCIE1A); sei();
    if (retardo > retardoMin + paso) retardo -= paso;
    else { retardo = retardoMin; rampaLista = true; salidaActiva = true; }
  } else if (salidaActiva) {
    unsigned int cuentas = retardoMin * 2;
    cli(); TCNT1 = 0; OCR1A = cuentas; TIFR1 |= (1 << OCF1A); TIMSK1 |= (1 << OCIE1A); sei();
  }
}

void TriacSoftStart::setPulseWidth(unsigned int us) { pulso = us; }
void TriacSoftStart::setInitialDelay(unsigned int us) { retardo = us; }
void TriacSoftStart::setFinalDelay(unsigned int us) { retardoMin = us; }
void TriacSoftStart::setRampStep(unsigned int us) { paso = us; }

ISR(TIMER1_COMPA_vect) {
  static bool estado = false;
  if (!estado) {
    digitalWrite(5, HIGH);
    OCR1A = TCNT1 + 400 * 2;
    estado = true;
  } else {
    digitalWrite(5, LOW);
    TIMSK1 &= ~(1 << OCIE1A);
    estado = false;
  }
}