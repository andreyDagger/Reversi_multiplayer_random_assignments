#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>

#include "Console_visualiser.h"
#include "String_functions.h"
#include "String_exceptions.h"

using namespace std;

const int coeff = 2;
const int cell_size = 1; // определяет размер ячейки
const int MaxNumberLen = 6; // максимальная длина числа, которое является шириной/высотой доски

typedef string (*mult_function)(string, int);
mult_function mult = &(String_functions::mult);

void Console_visualiser::draw_field(int width, int height) {
	erase_field(width, height);

	SetConsoleCursorPos(0, 0); // уводит каретку в самое начало

	int indent = 0;
	for (int i = 0; i <= width; i++) {
		draw_vertical_line(height, coeff * indent);
		if (i != width) {
			SetConsoleCursorPos(coeff * i * (cell_size + 1) + 2, 2 * height + 1);
			cout << i + 1;
		}
		indent += cell_size + 1;
		SetConsoleCursorPos(coeff*indent, 0);
	}

	SetConsoleCursorPos(0, 0);

	for (int i = 0; i <= height; i++) {
		draw_horizontal_line(width);
		if (i != height) {
			SetConsoleCursorPos(coeff * (width * (cell_size + 1) + 1), 2 * i + 1);
			cout << i + 1;
		}
		cout << mult("\n", cell_size);
	}

	this->place_to_write = { 0, 2*height + 4 };
	//SetConsoleCursorPos(0, height + 2);
}

void Console_visualiser::draw_horizontal_line(int length) {
	cout << mult("-", coeff * (length * (cell_size + 1) + 1) - 1);
}

void Console_visualiser::draw_vertical_line(int length, int indent) {
	int x = indent, y = 0;
	for (int i = 0; i <= length * (cell_size + 1); i++) {
		cout << "|";
		if (!(i == length * (cell_size + 1))) {
			SetConsoleCursorPos(x, y + 1);
			y++;
		}

	}
}

void Console_visualiser::draw_keg(int x, int y, ConsoleColor color) {
	SetConsoleCursorPos(4 * (x - 1) + 2, 2 * y - 1);
	print_color("#", DarkGray, color);
}

int Console_visualiser::input_integer() {
	string s = input_string();
	try {
		return String_functions::str_to_int(s);
	}
	catch (Bad_transform_str_to_int e) {
		throw Bad_transform_str_to_int(string(e.what(), 1));
	}
}

void Console_visualiser::input_two_integers(int& x, int& y) {
	string s;
	char res1[MaxNumberLen], res2[MaxNumberLen];
	int i = 0;

	s = input_string();

	while (s[i] != 32) { // 32 = ' '
		if (!isdigit(s[i]) || i >= s.size() - 2)
			throw Bad_integers_input("Я не понимаю что ты написал, введи числа еще раз: ");
		else {
			res1[i++] = s[i];
		}
	}
	res1[i] = '\0';
	int l = strlen(res1);
	i++;

	while (i < s.size()) { // 32 = ' '
		if (!isdigit(s[i]))
			throw Bad_integers_input("Я не понимаю что ты написал, введи числа еще раз: ");
		else {
			res2[i++ - l - 1] = s[i];
		}
	}
	res2[i - l - 1] = '\0';

	x = atoi(res1);
	y = atoi(res2);
}

void Console_visualiser::write(string message, ConsoleColor BackColor, ConsoleColor TextColor) {
	int number_of_enters = count(message.begin(), message.end(), '\n');

	SetConsoleCursorPos(place_to_write);
	cout << mult(" ", 99) << mult("\b", 99);
	print_color(message.c_str(), BackColor, TextColor);
	place_to_write = { 0, place_to_write.y + number_of_enters };
}

void Console_visualiser::SetConsoleCursorPos(int x, int y) {
	COORD position;										// Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
	position.X = x;									// Установка координаты X
	position.Y = y;									// Установка координаты Y
	SetConsoleCursorPosition(hConsole, position);
}

void Console_visualiser::SetConsoleCursorPos(Point point) {
	COORD position;										// Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
	position.X = point.x;									// Установка координаты X
	position.Y = point.y;									// Установка координаты Y
	SetConsoleCursorPosition(hConsole, position);
}

void Console_visualiser::erase_cell(int x, int y) {
	SetConsoleCursorPos(coeff * x * (cell_size + 1) - 2, (cell_size + 1) * y - 1);
	cout << " " << "\b";
	SetConsoleCursorPos(place_to_write);
}

void Console_visualiser::erase_field(int width, int height) {
	SetConsoleCursorPos(0, 0);
	for (int y = 0; y <= (cell_size + 1) * height; y++) {
		cout << mult(" ", width * coeff * (cell_size + 1)) + mult(" ", 200) << endl;
	}
}

string Console_visualiser::input_string() {
	return String_functions::input_string();
}

void Console_visualiser::draw_symbol(int x, int y, const char ch, ConsoleColor back_col, ConsoleColor symbol_col) {
	SetConsoleCursorPos((cell_size + 1) * coeff * (x - 1) + 2, (cell_size + 1) * y - 1);
	print_color(&ch, back_col, symbol_col);
}