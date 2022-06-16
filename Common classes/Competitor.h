// Модуль описывает поведение играющей сущности, вне зависимости это компьютер или живой человек

#pragma once

#include <iostream>
#include <fstream>

#include "Gaming_field.h"
#include "Visualiser.h"
#include "Inputer.h"

using namespace std;

class Competitor {
public:
	enum Type_of_turn {
		ByArrows,
		ByCoordinates,
		None
	};

	Type_of_turn type_of_turn = Type_of_turn::None;
	Gaming_field::KegColor color = Gaming_field::KegColor::Empty;
	
	Competitor() {}
	Competitor(Gaming_field::KegColor Color, Type_of_turn t) : color(Color), type_of_turn(t) {}

	virtual ~Competitor() {}

	virtual pair<int, int> make_turn(Gaming_field*) = 0; // Возвращает координаты фишки, которую поставил игрок

	void write_player_color_message(Visualiser*&);

	static inline Gaming_field::KegColor get_opposite_color(Gaming_field::KegColor c) {
		return Gaming_field::getOppositeCellState(c);
	}
};

class Computer : public Competitor {
private:
	void get_coordinates(Gaming_field*, int& x, int& y); // анализирует игровое поле и в x, y записывает координаты наилучшего хода
public:
	Computer() {}
	Computer(Gaming_field::KegColor color) : Competitor(color, Competitor::Type_of_turn::None) {}

	pair<int, int> make_turn(Gaming_field*);
};

class Player : public Competitor {
protected:
	Inputer* inputer;
public:
	Player() {}
	Player(Gaming_field::KegColor color, Type_of_turn turn) : Competitor(color, turn) {
		if (turn == ByArrows)
			inputer = new Input_ByArrows();
		else if (turn == ByCoordinates)
			inputer = new Input_ByCoordinates();
		else
			assert(0);
	}
	Player(Type_of_turn turn) : Player(Gaming_field::KegColor::Empty, turn) {}

	~Player() {}

	pair<int, int> make_turn(Gaming_field*);

	static inline Type_of_turn get_type_of_turn(string s) {
		if (s == "a")
			return ByArrows;
		else if (s == "b")
			return ByCoordinates;
		else
			throw Bad_turn_type_input();
	}
	static Type_of_turn input_type_of_turn(Visualiser*&, string message);

	class Bad_turn_type_input : public exception {
	public:
		const char* what() {
			return "Неправильный формат ввода";
		}
	};
};