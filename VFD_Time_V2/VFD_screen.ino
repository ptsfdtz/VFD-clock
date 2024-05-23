#define din    5 // DA
#define clk    6 // CK
#define cs     7 // CS
#define Reset  8 // RS
#define en     9 // EN

void write_6302(uint8_t w_data) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(clk, LOW);
    digitalWrite(din, (w_data & 0x01) ? HIGH : LOW);
    w_data >>= 1;
    digitalWrite(clk, HIGH);
  }
}

void VFD_cmd(uint8_t command) {
  digitalWrite(cs, LOW);
  write_6302(command);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
}

void S1201_show() {
  digitalWrite(cs, LOW);
  write_6302(0xE8);
  digitalWrite(cs, HIGH);
}

void Set_brightness(uint8_t level) {
  digitalWrite(cs, LOW);
  write_6302(0xE4);
  delayMicroseconds(5);
  write_6302(level);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
  digitalWrite(en, (level == 0) ? LOW : HIGH);
}

void VFD_init() {
  pinMode(en, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(din, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(Reset, OUTPUT);
  
  digitalWrite(en, HIGH);
  digitalWrite(Reset, LOW);
  delayMicroseconds(5);
  digitalWrite(Reset, HIGH);
  delay(1000);
  
  digitalWrite(cs, LOW);
  write_6302(0xE0);
  delayMicroseconds(5);
  write_6302(0x07);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);

  Set_brightness(100);
  delay(100);
  VFD_cmd(0xE9);
  delay(100);
}

void S1201_WriteOneChar(uint8_t x, uint8_t chr) {
  digitalWrite(cs, LOW);
  write_6302(0x20 + x);
  write_6302(chr + 0x30);
  digitalWrite(cs, HIGH);
  S1201_show();
}

void S1201_WriteStr(uint8_t x, const char *str) {
  digitalWrite(cs, LOW);
  write_6302(0x20 + x);
  while (*str) {
    write_6302(*str++);
  }
  digitalWrite(cs, HIGH);
  S1201_show();
}
