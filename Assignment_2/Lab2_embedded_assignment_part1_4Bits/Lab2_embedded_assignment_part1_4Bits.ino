 #define RS 23
#define E  22
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

void send4Bits(uint8_t data) {
  digitalWrite(D4, (data >> 0) & 1);
  digitalWrite(D5, (data >> 1) & 1);
  digitalWrite(D6, (data >> 2) & 1);
  digitalWrite(D7, (data >> 3) & 1);
  pulseEnable();
}

void LCD_command(uint8_t cmd) {
  digitalWrite(RS, LOW);
  send4Bits(cmd >> 4);   // High nibble
  send4Bits(cmd & 0x0F); // Low nibble
}

void LCD_writeChar(char data) {
  digitalWrite(RS, HIGH);
  send4Bits(data >> 4);
  send4Bits(data & 0x0F);
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
  uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;
  LCD_command(address);
}

void LCD_init() {
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  delay(50); 

  // 4-bit init sequence
  send4Bits(0x03);
  delay(5);
  send4Bits(0x03);
  delayMicroseconds(150);
  send4Bits(0x03);
  delayMicroseconds(150);
  send4Bits(0x02); // 4-bit mode

  LCD_command(0x28); // 2 lines, 5x8 dots
  LCD_command(0x0C); // display ON, cursor OFF
  LCD_command(0x06); // entry mode
  LCD_clear();
}

void setup() {
  LCD_init();
  
  LCD_write_offset("Wake up to", 0, 0);
  LCD_write_offset("reality_Madara", 0, 1);

}

void LCD_write_offset(char *txt, uint8_t x, uint8_t y) {
  LCD_setCursor(x, y);
  LCD_write(txt);
}


void loop() {
}
