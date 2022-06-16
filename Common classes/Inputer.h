#pragma once

#include "Visualiser.h"
#include "Gaming_field.h"

class Inputer {
public:
	virtual void input_coordinates(int& x, int& y, Visualiser*, Gaming_field*, Gaming_field::KegColor) = 0;
};

class Input_ByArrows : public Inputer {
private:
	enum Move_direction {
		Enter,
		Right,
		Down,
		Left,
		Up
	};

	bool make_move(int& x, int& y, Move_direction, Gaming_field*, Visualiser*); /* јнализирует Move_direction и измен€ет координаты (x, y)
																							(x1, y1) - начальные координаты. ¬озвращает true, если человек нажал enter*/
	static Move_direction get_move();
public:
	virtual void input_coordinates(int& x, int& y, Visualiser*, Gaming_field*, Gaming_field::KegColor);
};

class Input_ByCoordinates : public Inputer {
public:
	virtual void input_coordinates(int& x, int& y, Visualiser*, Gaming_field*, Gaming_field::KegColor);
};