#include "page_controller.h"

#include <oled.h>
#include <keyboard.h>
#include <Arduino.h>
#include <qwitch_bitmap.h>

void keyboard_test_page_initialize(void)
{
}

void keyboard_test_page_function(void)
{

	bool UP = digitalRead(KEY_UP) == KEY_PRESSED;
	bool DOWN = digitalRead(KEY_DOWN) == KEY_PRESSED;
	bool LEFT = digitalRead(KEY_LEFT) == KEY_PRESSED;
	bool RIGHT = digitalRead(KEY_RIGHT) == KEY_PRESSED;
	bool A = digitalRead(KEY_A) == KEY_PRESSED;
	bool B = digitalRead(KEY_B) == KEY_PRESSED;

	oled.clearBuffer();
	oled.drawBitmap(0, 0, 16, 16, kbd_test_bitmap);

	// 画圆表示按键状态
	// Up Down Left Right
	if (UP)
	{
		oled.drawDisc(31, 23, 8);
	}
	else
	{
		oled.drawCircle(31, 23, 8);
	}

	if (DOWN)
	{
		oled.drawDisc(31, 55, 8);
	}
	else
	{
		oled.drawCircle(31, 55, 8);
	}

	if (LEFT)
	{
		oled.drawDisc(15, 39, 8);
	}
	else
	{
		oled.drawCircle(15, 39, 8);
	}

	if (RIGHT)
	{
		oled.drawDisc(47, 39, 8);
	}
	else
	{
		oled.drawCircle(47, 39, 8);
	}

	// A B
	if (A)
	{
		oled.drawDisc(87, 23, 8);
	}
	else
	{
		oled.drawCircle(87, 23, 8);
	}

	if (B)
	{
		oled.drawDisc(111, 39, 8);
	}
	else
	{
		oled.drawCircle(111, 39, 8);
	}

	oled.sendBuffer();
}