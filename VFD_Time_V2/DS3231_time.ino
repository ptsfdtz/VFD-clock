// Function to print time to PC via Serial
void Printf_time_to_PC() {
  Serial.print("20");
  Serial.print(Clock.getYear(), DEC);
  Serial.print("-");
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print("-");
  Serial.print(Clock.getDate(), DEC);
  Serial.print(" ");
  Serial.print(Clock.getDoW(), DEC);
  Serial.print(" ");
  Serial.print(Clock.getHour(h12, PM), DEC);
  Serial.print(":");
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(":");
  Serial.println(Clock.getSecond(), DEC);
}

void Get_time_by_uart(byte& Year, byte& Month, byte& Day, byte& Week, byte& Hour, byte& Minute, byte& Second) {
  boolean GetString = false;
  char InChar;
  byte Temp1, Temp2;
  char InString[20];
  byte j = 0;

  while (!GetString) {
    if (Serial.available()) {
      InChar = Serial.read();
      InString[j++] = InChar;
      if (InChar == 'x') {
        GetString = true;
      }
    }
  }

  Serial.println(InString);

  Year = (InString[0] - '0') * 10 + (InString[1] - '0');
  Month = (InString[2] - '0') * 10 + (InString[3] - '0');
  Day = (InString[4] - '0') * 10 + (InString[5] - '0');
  Week = InString[6] - '0';
  Hour = (InString[7] - '0') * 10 + (InString[8] - '0');
  Minute = (InString[9] - '0') * 10 + (InString[10] - '0');
  Second = (InString[11] - '0') * 10 + (InString[12] - '0');
}

void Set_time_by_uart() {
  if (Serial.available()) {
    Get_time_by_uart(Year, Month, Date, Week, Hour, Minute, Second);
    Clock.setClockMode(false);
    Clock.setSecond(Second);
    Clock.setMinute(Minute);
    Clock.setHour(Hour);
    Clock.setDate(Date);
    Clock.setMonth(Month);
    Clock.setYear(Year);
    Clock.setDoW(Week);
  }
}

void VFD_display_time() {
  uint8_t temp = Clock.getHour(h12, PM);
  uint8_t a = temp / 10;
  uint8_t b = temp % 10;
  temp = Clock.getMinute();
  uint8_t d = temp / 10;
  uint8_t e = temp % 10;
  temp = Clock.getSecond();
  uint8_t g = temp / 10;
  uint8_t h = temp % 10;

  S1201_WriteOneChar(0, a);
  S1201_WriteOneChar(1, b);
  S1201_WriteOneChar(2, ':' - 0x30);
  S1201_WriteOneChar(3, d);
  S1201_WriteOneChar(4, e);
  S1201_WriteOneChar(5, ':' - 0x30);
  S1201_WriteOneChar(6, g);
  S1201_WriteOneChar(7, h);
}

void VFD_display_year() {
  uint8_t c = 2;
  uint8_t d = 0;
  uint8_t temp = Clock.getYear();
  uint8_t e = temp / 10;
  uint8_t f = temp % 10;

  S1201_WriteOneChar(0, ' ' - 0x30);
  S1201_WriteOneChar(1, ' ' - 0x30);
  S1201_WriteOneChar(2, c);
  S1201_WriteOneChar(3, d);
  S1201_WriteOneChar(4, e);
  S1201_WriteOneChar(5, f);
  S1201_WriteOneChar(6, ' ' - 0x30);
  S1201_WriteOneChar(7, ' ' - 0x30);

  if (Key_status == Key_Long_Press) {
  }
}

void setAlarmTime(byte hour, byte minute) {
  alarmHour = hour;
  alarmMinute = minute;
  alarmSet = true;
}
