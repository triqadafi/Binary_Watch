#include <Arduino.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <TinyRTClib.h>

#include "definition.h"
#include "io.h"
#include "button.h"
#include "interface.h"
#include "binary.h"

RTC_DS1307 rtc;                      // Set up real time clock


uint8_t FI_G_MENU = 0;
uint8_t FI_G_MENU_STATE = 0;


void setup() {
    // put your setup code here, to run once:
  fi_IO.init();


  TinyWireM.begin();            // Begin I2C
  rtc.begin();                  // Begin DS1307 real time clock

  fi_Interface.set(1, 1);
  delay(1000);
  fi_Interface.set(0, 0);

  if (! rtc.isrunning()) {      // Uncomment lines below first use of clock to set time
    //Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

uint8_t hourvalue, minutevalue;
void loop() {
  if(FI_G_MENU == FI_D_MENU_HOME){
    if(FI_G_MENU_STATE == 0){

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
        if(FI_NAV_R){
          fi_Interface.set(1, 1);
          delay(1000);
          fi_Interface.set(0, 0);
        }
    }
  }else if(FI_G_MENU == FI_D_MENU_HOUR){
    if(FI_G_MENU_STATE == 0){
      DateTime now = rtc.now();           // Get the RTC info
      hourvalue = now.hour();             // Get the hour
      if(hourvalue > 12) hourvalue -= 12; // This clock is 12 hour, is 13-24, convert to 1-12
      minutevalue = now.minute();         // Get the minutes

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      fi_Binary.set(hourvalue);
      FI_G_MENU = FI_D_MENU_HOME;
    }

  }
    // put your main code here, to run repeatedly:




}
