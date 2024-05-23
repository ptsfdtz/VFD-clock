#define right_signal   2
#define left_signal    11
#define power_signal   4

#define Key_Release    0
#define Key_Press      1
#define Key_Long_Press 2

void Switch_init() {
   pinMode(left_signal, INPUT_PULLUP);
   pinMode(right_signal, INPUT_PULLUP);
   pinMode(power_signal, INPUT_PULLUP);
}

void left_right_signal() {
  static bool key_flag = false;

  if (digitalRead(left_signal) == LOW && !key_flag) {
    num--;
    key_flag = true;
    if (num < 0) num = 0;
  } else if (digitalRead(right_signal) == LOW && !key_flag) {
    num++;
    key_flag = true;
    if (num > 5) num = 5;
  } else if (digitalRead(left_signal) == HIGH && digitalRead(right_signal) == HIGH) {
    key_flag = false;
  }
}

uint8_t Get_Key_Status() {
  static uint16_t key_num = 0;

  if (digitalRead(power_signal) == HIGH) {
    if (key_num < 1200 && key_num > 16) {
      key_num = 0;
      return Key_Press;
    }
    key_num = 0;
  } else {
    key_num++;
    if (key_num > 1200) {
      key_num = 2000;
      return Key_Long_Press;
    }
  }
  return Key_Release;
}
