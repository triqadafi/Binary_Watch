#include "binary.h"

#define FI_DELAY 250

void fi_BinaryClass::set(uint8_t _value){
  uint8_t bitmask = 3;
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t _mask = 1 << (bitmask);
    if (_value & _mask) {
      fi_Interface.set(0, 1);
    }else{
      fi_Interface.set(1, 0);
    }
    bitmask--;
    delay(FI_DELAY);
    fi_Interface.set(0, 0);
    delay(FI_DELAY);
  }
  fi_Interface.set(1, 1);
  delay(200);
  fi_Interface.set(0, 0);
  delay(FI_DELAY);
}
void fi_BinaryClass::precision(uint8_t _value){
  if(_value != 0){
    fi_Interface.set(1, 0);
    delay(250);
    for (uint8_t i = 0; i < _value; i++) {
      fi_Interface.set(1, 1);
      delay(150);
      fi_Interface.set(1, 0);
      delay(150);
    }
    fi_Interface.set(0, 0);
    delay(FI_DELAY);
  }
}

fi_BinaryClass fi_Binary;
