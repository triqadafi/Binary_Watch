#ifndef FI_BINARY_H
#define FI_BINARY_H

#include <Arduino.h>
#include "interface.h"

class fi_BinaryClass{
  private:
    uint8_t number = 0;
  public:

    void set(uint8_t _value);
    void precision(uint8_t _value);
    void display();
};

extern fi_BinaryClass fi_Binary;

#endif
