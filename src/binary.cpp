#include "binary.h"

void fi_BinaryClass::set(uint8_t _value){
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t _mask = 1 << (bitmask);
    if (_value & _mask) {
      fi_Interface.set(0, 1);
    }else{
      fi_Interface.set(1, 0);
    }
    bitmask--;
    delay(200);
    fi_Interface.set(0, 0);
    delay(200);
  }
}


fi_BinaryClass fi_Binary;
