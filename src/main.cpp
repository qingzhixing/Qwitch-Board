#include <Arduino.h>
#include <U8g2lib.h>

#include "qwitch_bitmap.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA);

const long bitmap_move_interval_ms = 100;
int move_direction_x = -1; // 1 for right, -1 for left
long last_move_time_ms = 0;
long current_bitmap_x = 32;

void setup()
{

  u8g2.begin();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  u8g2.clearBuffer();
  u8g2.drawBitmap(0, 0, 16, 16, qwitch_bitmap);
  u8g2.drawBitmap(current_bitmap_x, 16, 12, 32, qzx_bitmap);
  u8g2.drawBitmap(0, 48, 14, 16, board_bitmap);

  u8g2.sendBuffer();

  last_move_time_ms = millis();
}

void loop()
{
  long current_time_ms = millis();
  if (current_time_ms - last_move_time_ms >= bitmap_move_interval_ms)
  {
    last_move_time_ms = current_time_ms;
    current_bitmap_x += move_direction_x;
    if (current_bitmap_x > 32)
    {
      current_bitmap_x = 32;
      move_direction_x = -move_direction_x;
    }
    else if (current_bitmap_x < 0)
    {
      current_bitmap_x = 0;
      move_direction_x = -move_direction_x;
    }
    u8g2.setDrawColor(0);
    u8g2.drawBox(current_bitmap_x, 16, 12 * 8, 32);
    u8g2.setDrawColor(1);
    u8g2.drawBitmap(current_bitmap_x, 16, 12, 32, qzx_bitmap);
    u8g2.sendBuffer();
  }
}
