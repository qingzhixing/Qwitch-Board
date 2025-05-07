#include <Arduino.h>
#include <U8g2lib.h>
#include <keyboard.h>
#include <oled.h>
#include <display_page.h>
#include <led.h>

void setup()
{
  oled_init();
  keyboard_init();
  led_init();
  Serial.begin(115200);

  led_on();
  set_display_function(home_page_function, home_page_initialize);
}

void loop()
{
  Serial.println(digitalRead(KEY_A) == HIGH ? "HIGH" : "LOW");
  display_one_frame();
}