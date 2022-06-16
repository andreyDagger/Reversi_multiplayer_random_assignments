#pragma once

#include <iostream>
#include <cassert>

#include "service.h"
#include "Visualiser.h"
#include "String_functions.h"

using namespace std;

class Gaming_field {
public:

	static const int KEGS_QUANTITY_ON_START = 4;
	static const int CLASSIC_FIELD_SIZE = 4;

	enum KegColor {
		Empty,
		Black,
		Red
	};

	static inline KegColor get_color(int is_first) {
		if (is_first)
			return Red;
		else
			return Black;
	}

	static inline ConsoleColor getConsoleColor(KegColor keg_type) {
		if (keg_type == Black)
			return ConsoleColor::Black;
		else if (keg_type == Red)
			return ConsoleColor::Red;
		else
			throw;
	}

	static inline KegColor getOppositeCellState(KegColor keg_type) {
		if (keg_type == KegColor::Black)
			return KegColor::Red;
		else if (keg_type == KegColor::Red)
			return KegColor::Black;
		else {
			cout << "getAntiCellState\n"; // ��� ������ ������ ���� � ��� (���� ����������)
			assert(0);
		}
	}

	enum Direction {
		Up,
		Down,
		Right,
		Left,
		Up_left,
		Up_right,
		Down_left,
		Down_right
	};

	struct Score {
		int red_player;
		int black_player;
	};

	typedef pair<int, int> keg; // keg - ���������� �������

	Gaming_field(Visualiser*); // ������� ���� 8x8
	Gaming_field(int, int, Visualiser*); // ������� ���� � ��������� ���������

	vector<keg> place_keg_and_revert(int x, int y, KegColor keg_type); /* ������ ����� � �������� ���������� � �������� ������ (�����)
																		 � ���������, ���� �� ���������� �����-������ �����.
																		 ���������� ������ ��������, ������� ������� �����������*/

	Score count_score(); // ������������ ���-�� �������� �������� � ������� ������
	int count_score(KegColor); // ������������ ���-�� ������������ �������� (�������� ���� ������)
	string write_end_information(); // ������� ���������� �� ��������� ����, ����� ���������� � � ���� string

	int count_kegs();
	bool is_end(); // �������� ����������� �� ����, ��� ���

	void initialize(); // ������ ���� � ������� ��� ������ � ��������� 8x8
	void initialize(int, int); // ������ ���� � ������� ��� ������ � ��������� ���������

	inline int get_height() const { return height; }
	inline int get_width() const { return width; }
	inline KegColor get_cell_state(int x, int y) const { return field[y - 1][x - 1]; }
	inline Visualiser* get_visualiser() const { return vis; }

	void erase_cell(int x, int y); // ������� ����� � ������������ x, y

	vector<keg> redraw_line(int x_1, int y_1, int x_2, int y_2, KegColor col, Direction dir);
	void redraw_line(vector<keg> kegs, KegColor);

	void find_empty_cell(int& x, int& y); // ���� ������ ������ � ���������� � ���������� � (x, y)

	// ����������:
	class Bad_field_size : public exception {
	private:
		int width, height;
		string error_message;
	public:
		Bad_field_size(int w, int h) : width(w), height(h) {}

		const char* what() {
			error_message = "������������ ������ ����, ��� ��������� (" + String_functions::int_to_str(width) + ", " + String_functions::int_to_str(height) + ") �� ������ ���� ������ 2-��";
			return error_message.c_str();
		}
	};

	class Bad_turn : public exception {
	private:
		string error_message;
	public:
		Bad_turn(string s) : error_message(s) {}

		const char* what() {
			return error_message.c_str();
		}
	};

private:
	KegColor** field;
	int width, height;

	Visualiser* vis;

	vector<keg> revert_kegs(int x, int y, KegColor keg_type); // ����� ����� ������ ����� ���� �����-�� ����� �����������, ��� ��� �-�� � ����������
	
	bool find_up_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� ������ ����� ������ �� ����� (����)
	bool find_down_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� ����� ����� ������ �� ����� (����)
	bool find_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� ����� ����� ������ �� ����� (����)
	bool find_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� ������ ����� ������ �� ����� (����)
	bool find_up_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� �� ��������� ������ ����� ����� ������ �� ����� (����)
	bool find_up_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� �� ��������� ������ ������ ����� ������ �� ����� (����)
	bool find_down_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� �� ��������� ����� ������ ����� ������ �� ����� (����)
	bool find_down_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // ���� �� ��������� ����� ����� ����� ������ �� ����� (����)
	// ���������� ��������� ����� ������������ � x_1 � y_1, � ������ ������� x_1 = nullptr � y_1 = nullptr
	
	void place_keg(int x, int y, KegColor keg_type); // ������ ������ ����� � �������� ����������

	int count_red_score();
	int count_black_score();
};