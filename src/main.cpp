#include <Arduino.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <TinyRTClib.h>

#include "definition.h"
#include "io.h"
#include "button.h"
#include "interface.h"
#include "binary.h"

RTC_DS1307 rtc;                      // Set up real time clock

unsigned long FI_G_MILLIS = 0;
uint8_t FI_G_MENU = 0;
uint8_t FI_G_MENU_STATE = 0;
uint8_t FI_G_MENU_CHILD = 0;

uint8_t FI_G_SETTING_HOUR = 0;
uint8_t FI_G_SETTING_MINUTE = 0;

void setup() {

  TinyWireM.begin();            // Begin I2C
  rtc.begin();                  // Begin DS1307 real time clock

  if (! rtc.isrunning()) {      // Uncomment lines below first use of clock to set time
    //Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
    //rtc.adjust(DateTime(2014, 1, 21, 7, 0, 0));

  }
    // put your setup code here, to run once:
  fi_IO.init();
  fi_IO.input();

  FI_G_MILLIS = millis();
  while (1) {
    if(millis() - FI_G_MILLIS < 100){
      fi_Interface.set(1, 1);
    }else if(millis() - FI_G_MILLIS < 100*2){
      fi_Interface.set(0, 0);
    }else if(millis() - FI_G_MILLIS < 100*3){
      fi_Interface.set(1, 1);
    }else if(millis() - FI_G_MILLIS < 100*13){
      fi_Interface.set(0, 0);
    }else if(millis() - FI_G_MILLIS < 100*14){
      fi_Interface.set(1, 1);
      FI_G_MILLIS = millis();
    }

    if(FI_NAV_R){
      fi_Interface.set(1, 1);
      fi_IO.safe(FI_D_RIGHT);
      fi_Interface.set(0, 0);

      break;
    }
  }

  fi_IO.safe(FI_D_RIGHT);
  fi_IO.output();
}

uint8_t hourvalue, minutevalue, precisionvalue;
void loop() {
  if(FI_G_MENU == FI_D_MENU_HOME){
    if(FI_G_MENU_STATE == 0){
      fi_IO.input();

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
        if(FI_NAV_R){
          fi_Interface.set(0, 1);
          fi_IO.safe(FI_D_RIGHT);
          fi_Interface.set(0, 0);
          delay(1000);

          FI_G_MENU_STATE = 0;
          FI_G_MENU = FI_D_MENU_HOUR;
        }
        if(FI_NAV_L){
          fi_Interface.set(1, 0);
          fi_IO.safe(FI_D_LEFT);
          fi_Interface.set(0, 0);
          delay(1000);

          FI_G_MENU_STATE = 0;
          FI_G_MENU = FI_D_MENU_MINUTE;
        }
        // if(FI_NAV_L){
        //   fi_Interface.set(1, 0);
        //   fi_IO.safe(FI_D_LEFT);
        //   fi_IO.output();
        //   rtc.adjust(DateTime(2014, 1, 21, 7, 0, 0));
        //   fi_Interface.set(0, 0);
        //   FI_G_MENU_STATE = 0;
        //   FI_G_MENU = FI_D_MENU_HOME;
        // }
    }
  }else if(FI_G_MENU == FI_D_MENU_HOUR){
    if(FI_G_MENU_STATE == 0){
      fi_IO.output();
      DateTime now = rtc.now();           // Get the RTC info

      hourvalue = now.hour();             // Get the hour
      if(hourvalue > 12) hourvalue -= 12; // This clock is 12 hour, is 13-24, convert to 1-12
      minutevalue = now.minute() / 5;

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      fi_Binary.set(hourvalue);
      fi_Binary.set(minutevalue);

      FI_G_MENU_STATE = 0;
      FI_G_MENU = FI_D_MENU_HOME;
    }
  }else if(FI_G_MENU == FI_D_MENU_MINUTE){
    if(FI_G_MENU_STATE == 0){
      fi_IO.output();
      DateTime now = rtc.now();           // Get the RTC info
      fi_IO.input();

      minutevalue = now.minute() / 5;
      precisionvalue = now.minute() % 5;

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      fi_Binary.set(minutevalue);
      fi_Binary.precision(precisionvalue);

      FI_G_MENU_STATE = 0;
      if(FI_NAV_R){
        fi_Interface.set(1, 1);
        fi_IO.safe(FI_D_RIGHT);
        delay(1000);
        fi_Interface.set(0, 0);
        FI_G_MENU = FI_D_MENU_MENU;
      }else{
        FI_G_MENU = FI_D_MENU_HOME;
      }
    }
  }else if(FI_G_MENU == FI_D_MENU_MENU){
    if(FI_G_MENU_STATE == 0){
      fi_IO.input();
      FI_G_MILLIS = millis();

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      switch (FI_G_MENU_CHILD) {
        case 0:
          fi_Interface.set(1, 1);
        break;
        case 1: // FLIP FLOP
          if(millis() - FI_G_MILLIS < 500){
            fi_Interface.set(1, 0);
          }else if(millis() - FI_G_MILLIS < 500*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 500*3){
            fi_Interface.set(0, 1);
          }else if(millis() - FI_G_MILLIS < 500*4){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 500*5){
            fi_Interface.set(1, 0);
            FI_G_MILLIS = millis();
          }
        break;
        case 2: // blink 1 second
          if(millis() - FI_G_MILLIS < 1000){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 1000*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 1000*3){
            fi_Interface.set(1, 1);
            FI_G_MILLIS = millis();
          }
        break;
        case 3: // blink 200ms
          if(millis() - FI_G_MILLIS < 200){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 200*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 200*3){
            fi_Interface.set(1, 1);
            FI_G_MILLIS = millis();
          }
        break;
        case 4: // blink 100ms
          if(millis() - FI_G_MILLIS < 100){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 100*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 100*3){
            fi_Interface.set(1, 1);
            FI_G_MILLIS = millis();
          }
        break;
        case 5:  // blink special
          if(millis() - FI_G_MILLIS < 200){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 200*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 200*3){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 200*8){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 200*9){
            fi_Interface.set(1, 1);
            FI_G_MILLIS = millis();
          }
        break;
        case 6: // SOS
          if(millis() - FI_G_MILLIS < 150){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*2){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*3){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*4){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*5){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*7){
            fi_Interface.set(0, 0); // end s
          }else if(millis() - FI_G_MILLIS < 150*10){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*11){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*14){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*15){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*18){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*20){
            fi_Interface.set(0, 0); // end o
          }else if(millis() - FI_G_MILLIS < 150*21){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*22){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*23){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*24){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*25){
            fi_Interface.set(1, 1);
          }else if(millis() - FI_G_MILLIS < 150*29){
            fi_Interface.set(0, 0);
          }else if(millis() - FI_G_MILLIS < 150*30){
            fi_Interface.set(1, 1);
            FI_G_MILLIS = millis();
          }
        break;
      }
      if(FI_NAV_L){
        fi_Interface.set(0, 0);
        fi_IO.safe(FI_D_LEFT);
        if(FI_G_MENU_CHILD < 6){
          FI_G_MENU_CHILD++;
        }else{
          FI_G_MENU_CHILD = 0;
        }
        delay(1000);
        FI_G_MILLIS = millis();
      }
      if(FI_NAV_R){
        fi_Interface.set(0, 0);
        fi_IO.safe(FI_D_RIGHT);
        FI_G_MENU_STATE = 0;
        if(FI_G_MENU_CHILD == 5){
          FI_G_MENU = FI_D_MENU_SETTING;
        }else{
          FI_G_MENU = FI_D_MENU_HOME;
        }
        delay(1000);
      }
    }
  }else if(FI_G_MENU == FI_D_MENU_SETTING){
    if(FI_G_MENU_STATE == 0){
      fi_IO.input();
      FI_G_MILLIS = millis();

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      if(millis() - FI_G_MILLIS < 500){
        fi_Interface.set(1, 0);
      }else if(millis() - FI_G_MILLIS < 500*2){
        fi_Interface.set(0, 0);
      }else if(millis() - FI_G_MILLIS < 500*3){
        fi_Interface.set(0, 1);
      }else if(millis() - FI_G_MILLIS < 500*4){
        fi_Interface.set(0, 0);
      }else if(millis() - FI_G_MILLIS < 500*5){
        fi_Interface.set(1, 0);
        FI_G_MILLIS = millis();
      }
      if(FI_NAV_R){
        fi_Interface.set(0, 1);
        fi_IO.safe(FI_D_RIGHT);
        fi_Interface.set(0, 0);
        delay(1000);

        fi_IO.output();
        DateTime now = rtc.now();           // Get the RTC info
        fi_IO.input();

        FI_G_SETTING_HOUR = now.hour();             // Get the hour
        if(FI_G_SETTING_HOUR > 12) FI_G_SETTING_HOUR -= 12; // This clock is 12 hour, is 13-24, convert to 1-12
        fi_Binary.set(FI_G_SETTING_HOUR);
        fi_Interface.set(1, 0);

        FI_G_MENU_STATE = 2;
      }
      if(FI_NAV_L){
        fi_Interface.set(1, 0);
        fi_IO.safe(FI_D_LEFT);
        fi_Interface.set(0, 0);
        delay(1000);

        FI_G_MENU_STATE = 3;
      }
    }
    if(FI_G_MENU_STATE == 2){
      if(FI_NAV_R){
        fi_Interface.set(1, 1);
        fi_IO.safe(FI_D_RIGHT);
        fi_Interface.set(1, 0);
        if(FI_G_SETTING_HOUR < 12){
          FI_G_SETTING_HOUR++;
        }else{
          FI_G_SETTING_HOUR = 0;
        }
        delay(200);
      }
      if(FI_NAV_L){
        fi_Interface.set(0, 0);
        fi_IO.safe(FI_D_LEFT);
        delay(1000);
        fi_Binary.set(FI_G_SETTING_HOUR);
        delay(1000);
        FI_G_MILLIS = millis();
        FI_G_MENU_STATE = 4;
      }
    }
    if(FI_G_MENU_STATE == 3){

    }
    if(FI_G_MENU_STATE == 4){
      if(millis() - FI_G_MILLIS < 200){
        fi_Interface.set(1, 0);
      }else if(millis() - FI_G_MILLIS < 200*2){
        fi_Interface.set(0, 0);
      }else if(millis() - FI_G_MILLIS < 200*3){
        fi_Interface.set(0, 1);
      }else if(millis() - FI_G_MILLIS < 200*4){
        fi_Interface.set(0, 0);
      }else if(millis() - FI_G_MILLIS < 200*5){
        fi_Interface.set(1, 0);
        FI_G_MILLIS = millis();
      }
      if(FI_NAV_R){
        fi_Interface.set(0, 1);
        fi_IO.safe(FI_D_RIGHT);
        fi_Interface.set(1, 1);
        delay(200);
        fi_Interface.set(0, 0);
        delay(200);
        fi_Interface.set(1, 1);
        //adjust here!
        FI_G_MENU_STATE = 0;
        FI_G_MENU = FI_D_MENU_MENU;
        delay(200);
      }
      if(FI_NAV_L){
        fi_IO.safe(FI_D_LEFT);
        FI_G_MENU_STATE = 0;
        FI_G_MENU = FI_D_MENU_MENU;
        delay(200);
      }
    }
  }
    // put your main code here, to run repeatedly:




}
