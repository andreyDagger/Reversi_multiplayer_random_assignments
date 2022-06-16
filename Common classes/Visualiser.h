#pragma once

#include <iostream>

#include "service.h"

using namespace std;

class Visualiser {
protected:

	typedef struct Point {
		int x;
		int y;
	};
	Point place_to_write;

public:
	virtual void draw_field(int width, int height) = 0; // ������ ���� � ��������� ���������
	virtual void draw_keg(int x, int y, ConsoleColor) = 0; // ������ ������� � �������� �����������
	virtual void draw_symbol(int x, int y, char ch, ConsoleColor back_col = Black, ConsoleColor symbol_col = White) = 0; // ������ ������ � �������� �����������

	virtual int input_integer() = 0; // ������������ ���� ���������������� �����
	virtual void input_two_integers(int& x, int& y) = 0; // ������������ ���� ���� ��������������� �����
	virtual string input_string() = 0; // ������������ ���� ������

	virtual void write(string message, ConsoleColor BackColor = Black, ConsoleColor TextColor = White) = 0; // ������� ��������� �� ����� ��������� ����� � �������� �����

	virtual void erase_field(int width, int height) = 0; // ������� ����
	virtual void erase_cell(int x, int y) = 0; // ������� ������� � ��������� ������������

	// ����������:
	class Bad_integers_input : public exception {
	private:
		string error_message;
	public:
		Bad_integers_input(string s) : error_message(s) {}
		const char* what() { return error_message.c_str(); }
	};
};