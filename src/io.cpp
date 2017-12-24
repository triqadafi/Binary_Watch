#include "io.h"

void fi_IOClass::init(){
  pinMode(PIN_BIN_0, OUTPUT); digitalWrite(PIN_BIN_0, LOW);
  pinMode(PIN_BIN_1, OUTPUT); digitalWrite(PIN_BIN_1, LOW);
  pinMode(PIN_NAV_R, INPUT_PULLUP);
  pinMode(PIN_NAV_L, INPUT_PULLUP);

  // Disable what we don't need to save power
  ADCSRA &= ~(1<<ADEN); // Disable ADC
}
void fi_IOClass::output(){
  is_input = false;
  is_output = true;;
  pinMode(PIN_NAV_R, OUTPUT);
  pinMode(PIN_NAV_L, OUTPUT);
  //pinMode(PIN_BIN_0, OUTPUT); digitalWrite(PIN_BIN_0, LOW);
  //pinMode(PIN_BIN_1, OUTPUT); digitalWrite(PIN_BIN_1, LOW);
}
void fi_IOClass::input(){
  is_input = true;
  is_output = false;
  pinMode(PIN_NAV_R, INPUT_PULLUP);
  pinMode(PIN_NAV_L, INPUT_PULLUP);

}

void fi_IOClass::safe(uint8_t _option){
  uint16_t _pass = 0;
  switch (_option) {
    case FI_D_RIGHT:
      while(1){
        if(FI_NAV_R){
          _pass = 0;
        }else{
          _pass++; delay(1);
          if(_pass > 250){
            break;
          }
        }
      }
    break;
    case FI_D_LEFT:
      while(1){
        if(FI_NAV_L){
          _pass = 0;
        }else{
          _pass++; delay(1);
          if(_pass > 250){
            break;
          }
        }
      }
    break;
  }
}

fi_IOClass fi_IO;
