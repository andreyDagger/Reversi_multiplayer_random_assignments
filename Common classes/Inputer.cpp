#include <conio.h>

#include "Inputer.h"

void Input_ByArrows::input_coordinates(int& x, int& y, Visualiser* vis, Gaming_field* field, Gaming_field::KegColor color) {
	/*if (color == Gaming_field::KegColor::Black)
		vis->write("Ход черного игрока...");
	else if (color == Gaming_field::KegColor::Red)
		vis->write("Ход красного игрока...");
	else {
		vis->write("Color of player is not defined in function \"Competitor::write_who_make_turn\"\n", Black, Red);
		abort();
	}*/

	int x1 = 1, y1 = 1, x_prev, y_prev;
	field->find_empty_cell(x1, y1);
	Gaming_field::KegColor prev_keg;

	while (1) {
		prev_keg = field->get_cell_state(x1, y1);
		vis->draw_keg(x1, y1, Gaming_field::getConsoleColor(color));
		x_prev = x1, y_prev = y1;

		Move_direction dir = get_move();
		if (make_move(x1, y1, dir, field, vis)) {
			if (field->get_cell_state(x1, y1) != Gaming_field::Empty) {
				vis->draw_keg(x1, y1, Gaming_field::getConsoleColor(prev_keg));
			}
			break;
		}
		
		if (prev_keg == Gaming_field::Empty)
			vis->erase_cell(x_prev, y_prev);
		else
			vis->draw_keg(x_prev, y_prev, Gaming_field::getConsoleColor(prev_keg));
	}
	x = x1, y = y1;
}

Input_ByArrows::Move_direction Input_ByArrows::get_move() {
	while (1) {
		int move1 = _getch();
		if (move1 == 13)
			return Enter;
		if (move1 == 224) {
			int move2 = _getch();
			if (move2 == 75)
				return Left;
			else if (move2 == 72)
				return Up;
			else if (move2 == 80)
				return Down;
			else if (move2 == 77)
				return Right;
		}
	}
}

bool Input_ByArrows::make_move(int& x, int& y, Move_direction dir, Gaming_field* field, Visualiser* vis) {
	if (dir == Enter) {
		return true;
	}
	else if (dir == Up) {
		if (y > 1)
			--y;
	}
	else if (dir == Down) {
		if (y < field->get_height())
			++y;
	}
	else if (dir == Left) {
		if (x > 1)
			--x;
	}
	else if (dir == Right) {
		if (x < field->get_width())
			++x;
	}
	else {
		vis->write("Undefined direction in function Player_ByArrows::get_coordinates()", Black, Red);
		abort();
	}
	return false;
}

void Input_ByCoordinates::input_coordinates(int& x, int& y, Visualiser* vis, Gaming_field* field, Gaming_field::KegColor color) {
	if (color == Gaming_field::KegColor::Black)
		vis->write("Ход черного игрока, введите координаты фишки через пробел: ");
	else if (color == Gaming_field::KegColor::Red)
		vis->write("Ход красного игрока, введите координаты фишки через пробел: ");
	else {
		vis->write("Color of player is not defined in function \"Player::make_turn\"\n", Black, Red);
		abort();
	}

	vis->input_two_integers(x, y);
}