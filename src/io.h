#ifndef FI_IO_H
#define FI_IO_H

#include <Arduino.h>

#define PIN_BIN_0 4
#define PIN_BIN_1 3
#define PIN_NAV_R 0
#define PIN_NAV_L 2


class fi_IOClass{
  private:
  public:

    void init();
};

extern fi_IOClass fi_IO;

#endif
