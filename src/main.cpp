#include <Arduino.h>
#include <U8g2lib.h>
#include <keyboard.h>
#include <oled.h>
#include <display_page.h>
#include <led.h>

static long last_released_AB_time_ms = 0;
static long switch_page_interval_ms = 3000;

static bool is_in_home_page = true;

void setup()
{
  oled_init();
  keyboard_init();
  led_init();
  Serial.begin(115200);

  led_on();

  set_display_function(home_page_function, home_page_initialize);

  last_released_AB_time_ms = millis();
}

void loop()
{
  if ((digitalRead(KEY_A) == KEY_PRESSED) && (digitalRead(KEY_A) == KEY_PRESSED))
  {
    long current_time_ms = millis();
    if (current_time_ms - last_released_AB_time_ms >= switch_page_interval_ms)
    {
      last_released_AB_time_ms = millis();
      if (is_in_home_page)
      {
        is_in_home_page = false;
        set_display_function(keyboard_test_page_function, keyboard_test_page_initialize);
      }
      else
      {
        is_in_home_page = true;
        set_display_function(home_page_function, home_page_initialize);
      }
    }
  }
  else
  {
    last_released_AB_time_ms = millis();
  }
  display_one_frame();
}