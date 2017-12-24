#ifndef FI_IO_H
#define FI_IO_H

#include <Arduino.h>
#include "button.h"
#include "definition.h"

#define PIN_BIN_0 4
#define PIN_BIN_1 3
#define PIN_NAV_R 0
#define PIN_NAV_L 2


class fi_IOClass{
  private:
  public:
    bool is_input;
    bool is_output;
    void init();
    void input();
    void output();
    void safe(uint8_t _option);
};

extern fi_IOClass fi_IO;

#endif
