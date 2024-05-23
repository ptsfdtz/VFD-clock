void beep_once()  //蜂鸣器响一次
{
  digitalWrite(pin_buzzer, HIGH);  //蜂鸣器响一下
  delay(100);
  digitalWrite(pin_buzzer, LOW);  //蜂鸣器响一下
}
