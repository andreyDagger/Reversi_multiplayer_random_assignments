#pragma once

#include <iostream>

#include "Visualiser.h"
#include "service.h"

class Console_visualiser : public Visualiser {
private:

	void draw_horizontal_line(int length);
	void draw_vertical_line(int length, int indent); // indent - ������ ����� �� ��� OY (����� ������� �������)

	static void SetConsoleCursorPos(int x, int y); // ������������� ������ � �������� �����
	static void SetConsoleCursorPos(Point point);

public:
	Console_visualiser() {
		place_to_write = { 0, 0 };
	}

	void draw_field(int width, int height); // ������ ���� � ��������� ���������
	void draw_keg(int x, int y, ConsoleColor); // ������ ������� � �������� ������
	void draw_symbol(int x, int y, char ch, ConsoleColor back_col = Black, ConsoleColor symbol_col = White); // ������ ������ � �������� �����������

	int input_integer();
	void input_two_integers(int& x, int& y); // ������������ ���� ���������
	string input_string(); // ������������ ���� ������

	void write(string message, ConsoleColor BackColor = Black, ConsoleColor TextColor = White); // ������� ��������� �� �����

	void erase_field(int width, int height); // ������� ����
	void erase_cell(int x, int y); // ������� ������� � ������������ (x, y)

	void clear() { system("cls"); }
};