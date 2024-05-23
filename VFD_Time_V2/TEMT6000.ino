int16_t brightness_value = 0;

uint8_t light_sensor_value() {
  brightness_value = analogRead(pin_light_sensor);

  if (brightness_value >= 900) {  // 最暗
    return 10;
  } else if (brightness_value >= 600) {  // 晚上室内开灯亮度
    return 40;
  } else if (brightness_value >= 400) {  // 白天
    return 100;
  } else {
    return 255;  // 非常明亮的情况
  }
}
