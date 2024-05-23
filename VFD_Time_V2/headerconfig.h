#define pinDHT22         10
#define pin_buzzer       3
#define pin_light_sensor A0

#define pin_pwr_hold     12
#define right_signal     2
#define left_signal      11
#define power_signal     4

#define Key_Release      0
#define Key_Press        1
#define Key_Long_Press   2

extern bool alarmSet;
extern byte alarmHour;
extern byte alarmMinute;

void setAlarmTime(byte hour, byte minute);
void checkAlarm();
