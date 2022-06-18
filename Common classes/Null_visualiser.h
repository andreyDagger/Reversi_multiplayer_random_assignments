// Этот Visualiser ничего не выводит

#pragma once

#include <iostream>
#include <cassert>

#include "Visualiser.h"
#include "service.h"

class Null_visualiser : public Visualiser {
private:

	void draw_horizontal_line(int length) {}
	void draw_vertical_line(int length, int indent) {} // indent - отступ линии от оси OY (левая граница консоли)

	static void SetConsoleCursorPos(int x, int y) {} // устанавливает курсор в заданное место
	static void SetConsoleCursorPos(Point point) {}

public:
	Null_visualiser() {}

	void draw_field(int width, int height) {} // рисует поле с заданными размерами
	void draw_keg(int x, int y, ConsoleColor) {} // рисует бочонок с заданным цветом
	void draw_symbol(int x, int y, char ch, ConsoleColor back_col = Black, ConsoleColor symbol_col = White) {} // ричует символ в заданных координатах

	int input_integer() { assert(0); return 0; }
	void input_two_integers(int& x, int& y) {} // осуществляет ввод координат
	string input_string() { assert(0); return "NULL"; } // осуществляет ввод строки

	void write(string message, ConsoleColor BackColor = Black, ConsoleColor TextColor = White) {} // выводит сообщение на экран

	void erase_field(int width, int height) {} // стирает поле
	void erase_cell(int x, int y) {} // стирает бочонок с координатами (x, y)

	void clear() {}
};