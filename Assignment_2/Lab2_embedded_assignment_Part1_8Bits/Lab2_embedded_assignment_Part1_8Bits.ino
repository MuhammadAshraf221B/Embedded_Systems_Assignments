#define RS 23
#define E  22

#define D0 25
#define D1 26
#define D2 27
#define D3 14
#define D4 21
#define D5 19
#define D6 18
#define D7 5

void pulseEnable() {
  digitalWrite(E, HIGH);
  delayMicroseconds(1);
  digitalWrite(E, LOW);
  delayMicroseconds(50);
}

void send8Bits(uint8_t data) {
  digitalWrite(D0, (data >> 0) & 1);
  digitalWrite(D1, (data >> 1) & 1);
  digitalWrite(D2, (data >> 2) & 1);
  digitalWrite(D3, (data >> 3) & 1);
  digitalWrite(D4, (data >> 4) & 1);
  digitalWrite(D5, (data >> 5) & 1);
  digitalWrite(D6, (data >> 6) & 1);
  digitalWrite(D7, (data >> 7) & 1);
  pulseEnable();
}

void LCD_command(uint8_t cmd) {
  digitalWrite(RS, LOW);
  send8Bits(cmd);
}

void LCD_writeChar(char data) {
  digitalWrite(RS, HIGH);
  send8Bits(data);
}

void LCD_write(char *str) {
  while(*str) {
    LCD_writeChar(*str++);
  }
}

void LCD_clear() {
  LCD_command(0x01);
  delay(2);
}

void LCD_setCursor(uint8_t col, uint8_t row) {
  uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
  LCD_command(address);
}

void LCD_write_offset(char *txt, uint8_t x, uint8_t y) {
  LCD_setCursor(x, y);
  LCD_write(txt);
}

void LCD_init() {
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  delay(50);

  digitalWrite(RS, LOW);

  send8Bits(0x30);
  delay(5);

  send8Bits(0x30);
  delayMicroseconds(150);

  send8Bits(0x30);
  delayMicroseconds(150);

  send8Bits(0x38); // 8-bit, 2 lines

  LCD_command(0x0C); // display ON
  LCD_command(0x06); // entry mode
  LCD_clear();
}

void setup() {
  LCD_init();

  LCD_write_offset("Wake up to", 0, 0);
  LCD_write_offset("reality_Madara", 0, 1);
}

void loop() {
}
