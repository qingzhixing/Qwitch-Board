#include <Arduino.h>
#include <U8g2lib.h>
#include <keyboard.h>
#include <oled.h>
#include <page_controller.h>
#include <led.h>

void setup()
{
  oled_init();
  keyboard_init();
  led_init();
  Serial.begin(115200);

  led_on();

  page_controller_init();
}

void loop()
{
  page_controller_loop();
}