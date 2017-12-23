#ifndef FI_INTERFACE_H
#define FI_INTERFACE_H

#include <Arduino.h>

class fi_InterfaceClass{
  private:
  public:

    void set(uint8_t _option, uint8_t _left, uint8_t _right);
};

extern fi_InterfaceClass fi_Interface;

#endif
