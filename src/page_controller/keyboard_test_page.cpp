#include "page_controller/keyboard_test_page.hpp"

#include <oled.hpp>
#include <keyboard.hpp>
#include <Arduino.h>
#include <bitmaps.hpp>

void keyboard_test_page_initialize(void)
{
}

void keyboard_test_page_function(void)
{

	bool UP = digitalRead(KEY_UP) == KEY_PRESSING;
	bool DOWN = digitalRead(KEY_DOWN) == KEY_PRESSING;
	bool LEFT = digitalRead(KEY_LEFT) == KEY_PRESSING;
	bool RIGHT = digitalRead(KEY_RIGHT) == KEY_PRESSING;
	bool A = digitalRead(KEY_A) == KEY_PRESSING;
	bool B = digitalRead(KEY_B) == KEY_PRESSING;

	oled.clearBuffer();
	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(20, 12, "Keyboard Test");
	oled.setDrawColor(1);

	// 画圆表示按键状态
	// Up Down Left Right
	if (UP)
	{
		oled.drawDisc(31, 28, 5);
	}
	else
	{
		oled.drawCircle(31, 28, 5);
	}

	if (DOWN)
	{
		oled.drawDisc(31, 50, 5);
	}
	else
	{
		oled.drawCircle(31, 50, 5);
	}

	if (LEFT)
	{
		oled.drawDisc(20, 39, 5);
	}
	else
	{
		oled.drawCircle(20, 39, 5);
	}

	if (RIGHT)
	{
		oled.drawDisc(42, 39, 5);
	}
	else
	{
		oled.drawCircle(42, 39, 5);
	}

	// A B
	if (A)
	{
		oled.drawDisc(90, 30, 5);
	}
	else
	{
		oled.drawCircle(90, 30, 5);
	}

	if (B)
	{
		oled.drawDisc(105, 42, 5);
	}
	else
	{
		oled.drawCircle(105, 42, 5);
	}

	oled.sendBuffer();
}