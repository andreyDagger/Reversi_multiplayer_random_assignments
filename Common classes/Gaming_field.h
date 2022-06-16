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
			cout << "getAntiCellState\n"; // эта запись должна идти в лог (надо переписать)
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

	typedef pair<int, int> keg; // keg - координаты бочонка

	Gaming_field(Visualiser*); // создает поле 8x8
	Gaming_field(int, int, Visualiser*); // создает поле с заданными размерами

	vector<keg> place_keg_and_revert(int x, int y, KegColor keg_type); /* ставит фишку в заданные координаты с заданным цветом (типом)
																		 и проверяет, надо ли развернуть какие-нибудь фишки.
																		 Возвращает список бочонков, которые функция перевернула*/

	Score count_score(); // подсчитывает кол-во бочонков красного и черного цветов
	int count_score(KegColor); // подсчитывает кол-во определенных бочонков (красного либо синего)
	string write_end_information(); // Выводит информацию об окончании игры, также возвращает её в виде string

	int count_kegs();
	bool is_end(); // сообщает закончилась ли игра, или нет

	void initialize(); // чистит поле и создает его заново с размерами 8x8
	void initialize(int, int); // чистит поле и создает его заново с заданными размерами

	inline int get_height() const { return height; }
	inline int get_width() const { return width; }
	inline KegColor get_cell_state(int x, int y) const { return field[y - 1][x - 1]; }
	inline Visualiser* get_visualiser() const { return vis; }

	void erase_cell(int x, int y); // стирает фишку с координатами x, y

	vector<keg> redraw_line(int x_1, int y_1, int x_2, int y_2, KegColor col, Direction dir);
	void redraw_line(vector<keg> kegs, KegColor);

	void find_empty_cell(int& x, int& y); // ищет пустую клетку и записывает её координаты в (x, y)

	// Исключения:
	class Bad_field_size : public exception {
	private:
		int width, height;
		string error_message;
	public:
		Bad_field_size(int w, int h) : width(w), height(h) {}

		const char* what() {
			error_message = "Неправильный размер поля, оба параметра (" + String_functions::int_to_str(width) + ", " + String_functions::int_to_str(height) + ") не должны быть меньше 2-ух";
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

	vector<keg> revert_kegs(int x, int y, KegColor keg_type); // когда игрок ставит фишку надо какие-то фишки перевернуть, чем эта ф-ия и занимается
	
	bool find_up_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет сверху фишку такого же цвета (типа)
	bool find_down_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет снизу фишку такого же цвета (типа)
	bool find_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет слева фишку такого же цвета (типа)
	bool find_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет справа фишку такого же цвета (типа)
	bool find_up_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет по диагонали сверху слева фишку такого же цвета (типа)
	bool find_up_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет по диагонали сверху справа фишку такого же цвета (типа)
	bool find_down_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет по диагонали снизу справа фишку такого же цвета (типа)
	bool find_down_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1); // Ищет по диагонали снизу слева фишку такого же цвета (типа)
	// КООРДИНАТЫ НАЙДЕННОЙ ФИШКИ ЗАПИСЫВАЮТСЯ В x_1 и y_1, в случае неудачи x_1 = nullptr и y_1 = nullptr
	
	void place_keg(int x, int y, KegColor keg_type); // просто ставит фишку в заданные координаты

	int count_red_score();
	int count_black_score();
};