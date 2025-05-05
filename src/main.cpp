#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA);

void setup()
{
  u8g2.begin();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  u8g2.drawCircle(64, 32, 8, U8G2_DRAW_ALL);
  u8g2.sendBuffer();
}

void loop()
{
}
