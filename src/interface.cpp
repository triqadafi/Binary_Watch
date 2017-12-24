#include "interface.h"

void fi_InterfaceClass::set(uint8_t _left, uint8_t _right){
  digitalWrite(PIN_BIN_0, _left);
  digitalWrite(PIN_BIN_1, _right);
}

fi_InterfaceClass fi_Interface;
