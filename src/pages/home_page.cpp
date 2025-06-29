#include "pages/home_page.hpp"
#include <oled.hpp>
#include "bitmaps.hpp"

NewPageDisplay* home_page = new HomePage();

static constexpr long bitmap_move_interval_ms = 100;
static int move_direction_x = -1; // 1 for right, -1 for left
static long last_move_time_ms = 0;
static long current_bitmap_x = 32;

void home_page_initialize() { last_move_time_ms = static_cast<long>(millis()); }

void home_page_update()
{
    long current_time_ms = static_cast<long>(millis());
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
        oled.clearBuffer();
        oled.drawBitmap(0, 0, 16, 16, qwitch_bitmap);
        oled.drawBitmap(current_bitmap_x, 16, 12, 32, qzx_bitmap);
        oled.drawBitmap(0, 48, 14, 16, board_bitmap);

        oled.sendBuffer();
    }
}

void HomePage::update() const { home_page_update(); }
void HomePage::initialize() const { home_page_initialize(); }
std::string HomePage::get_name() const { return "Home Page"; }
const unsigned char* HomePage::get_icon() const { return icon_home_bits; }
