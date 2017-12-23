#include "io.h"

void fi_IOClass::init(){
  pinMode(PIN_BIN_0, OUTPUT); digitalWrite(PIN_BIN_0, LOW);
  pinMode(PIN_BIN_1, OUTPUT); digitalWrite(PIN_BIN_1, LOW);
  pinMode(PIN_NAV_R, INPUT_PULLUP);
  pinMode(PIN_NAV_L, INPUT_PULLUP);

  // Disable what we don't need to save power
  ADCSRA &= ~(1<<ADEN); // Disable ADC
}

fi_IOClass fi_IO;
