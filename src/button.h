#ifndef FI_BUTTON_H
#define FI_BUTTON_H

#include "io.h"

#define FI_NAV_R (digitalRead(PIN_NAV_R) == LOW && !FI_G_INPUT)
#define FI_NAV_L (digitalRead(PIN_NAV_L) == LOW && !FI_G_INPUT)

#endif