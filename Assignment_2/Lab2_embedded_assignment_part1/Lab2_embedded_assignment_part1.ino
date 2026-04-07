#define RS 23
#define E  22
#define D4 21
#define D5 19
#define D6 18
#define D7 5

void LCD_pulseEnable() {
  digitalWrite(E, HIGH);
  delayMicroseconds(1);
  digitalWrite(E, LOW);
  delayMicroseconds(100);
}
void LCD_send4Bits(uint8_t data) {
  digitalWrite(D4, (data >> 0) & 1);
  digitalWrite(D5, (data >> 1) & 1);
  digitalWrite(D6, (data >> 2) & 1);
  digitalWrite(D7, (data >> 3) & 1);

  LCD_pulseEnable();
}
void LCD_command(uint8_t cmd) {
  digitalWrite(RS, LOW);

  LCD_send4Bits(cmd >> 4);   // High nibble
  LCD_send4Bits(cmd & 0x0F); // Low nibble
}
void LCD_writeChar(char data) {
  digitalWrite(RS, HIGH);

  LCD_send4Bits(data >> 4);
  LCD_send4Bits(data & 0x0F);
}
void LCD_write(char *str) {
  while(*str) {
    LCD_writeChar(*str++);
  }
}
void LCD_clear() {
  LCD_command(0x01);
  delayMicroseconds(2000);
}
void LCD_setCursor(uint8_t col, uint8_t row) {
  uint8_t address;

  if(row == 0)
    address = 0x80 + col;
  else
    address = 0xC0 + col;

  LCD_command(address);
}
void LCD_init() {
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  delayMicroseconds(50000);

  digitalWrite(RS, LOW);

  LCD_send4Bits(0x03);
  delayMicroseconds(4500);

  LCD_send4Bits(0x03);
  delayMicroseconds(4500);

  LCD_send4Bits(0x03);
  delayMicroseconds(150);

  LCD_send4Bits(0x02); // 4-bit mode

  LCD_command(0x28); // 2 lines
  LCD_command(0x0C); // display ON
  LCD_command(0x06); // entry mode
  LCD_clear();
}
void setup() {
  LCD_init();

  LCD_setCursor(0,0);
  LCD_write("Wake up to");

  LCD_setCursor(0,1);
  LCD_write("reality_Madara");
}

void loop() {

}
