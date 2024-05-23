#include <Wire.h>
#include <DS3231.h>
#include <SimpleDHT.h>
#include <MsTimer2.h>
#include "headerconfig.h"
DS3231 Clock;
SimpleDHT22 dht22(pinDHT22);
uint8_t Key_status = Key_Release;

int16_t num = 0;
unsigned long t = 0;
uint8_t Choose_num = 0;

uint8_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
uint16_t temp = 0;

byte Year, Month, Date, Week, Hour, Minute, Second;

bool Century = false;
bool h12;
bool PM;

volatile uint16_t Loop_time0 = 0, Loop_time1 = 0, Loop_time2 = 0, Loop_time3 = 0, Loop_time4 = 0, Loop_time5 = 0, Loop_time7 = 0;

void Time2_interrupt() {
  Loop_time0++, Loop_time1++, Loop_time2++, Loop_time3++, Loop_time4++, Loop_time5++, Loop_time7++;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin_pwr_hold, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_light_sensor, INPUT_PULLUP);
  Switch_init();
  MsTimer2::set(1, Time2_interrupt);
  MsTimer2::start();
  VFD_init();
  digitalWrite(pin_pwr_hold, HIGH);
  beep_once();
  Serial.println("ON");
}

bool flag1 = 0, flag2 = 0;

void loop() {
  if (Loop_time0 >= 1000) {
    Loop_time0 = 0;
    Set_time_by_uart();
    Printf_time_to_PC();
    Printf_DHT22_to_PC();
  }

  if (Loop_time7 >= 100) {
    Loop_time7 = 0;
    switch (num) {
      case 0:
        VFD_display_year();
        break;
      case 1:
        if (Loop_time1 >= 500) {
          Loop_time1 = 0;
          VFD_display_month_date();
        }
        break;
      case 2:
        VFD_display_time();
        break;
      case 3:
        if (Loop_time2 >= 250) {
          Loop_time2 = 0;
          VFD_display_temperature();
        }
        break;
      case 4:
        VFD_display_humidity();
        break;
      case 5:
        break;
    }
  }

  if (Loop_time3 >= 500) {
    Loop_time3 = 0;
    flag1 = !flag1;
    digitalWrite(LED_BUILTIN, flag1);
  }

  if (Loop_time4 >= 1000) {
    Loop_time4 = 0;
    Set_brightness(light_sensor_value());
  }

  if (Loop_time5 >= 1) {
    Loop_time5 = 0;
    left_right_signal();
    Key_status = Get_Key_Status();
    if (Key_status == Key_Long_Press) {
      Serial.println("OFF");
      beep_once();
      digitalWrite(pin_pwr_hold, LOW);
      while (!digitalRead(power_signal))
        ;
    } else {
      digitalWrite(pin_pwr_hold, HIGH);
    }
  }
}
