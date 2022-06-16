#include <iostream>
#include <Windows.h>

#include "Competitor.h"

using namespace std;

void Competitor::write_player_color_message(Visualiser*& vis) {
	if (color == Gaming_field::KegColor::Red)
		vis->write("Вы играете за красных!\n");
	else if (color == Gaming_field::KegColor::Black)
		vis->write("Вы играете за чёрных!\n");
	else {
		vis->write("Player color is not defiend in function Competitor::write_player_color_message()\n", Black, Red);
		assert(0);
	}
}

pair<int, int> Player::make_turn(Gaming_field* field) {
	int x = 0, y = 0;
	Visualiser* vis = field->get_visualiser();

	this->inputer->input_coordinates(x, y, vis, field, this->color);
	field->place_keg_and_revert(x, y, color);
	return make_pair(x, y);
}

Player::Type_of_turn Player::input_type_of_turn(Visualiser*& vis, string message) {
	bool is_mode_defined = false;
	string mode;
	Player::Type_of_turn type;

	vis->write(message);
	while (1) {
		mode = vis->input_string();

		try {
			type = Player::get_type_of_turn(mode);
			return type;
		}
		catch (Bad_turn_type_input e) {
			vis->write(e.what(), Black, Red);
		}

	}
}

pair<int, int> Computer::make_turn(Gaming_field* field) {
	Sleep(100);
	int x = 0, y = 0;
	Visualiser* vis = field->get_visualiser();

	if (color == Gaming_field::KegColor::Empty) {
		vis->write("Color of player is not defined in function \"Computer::make_turn\"\n", Black, Red);
		assert(0);
	}

	get_coordinates(field, x, y);
	field->place_keg_and_revert(x, y, color);
	return make_pair(x, y);
}

void Computer::get_coordinates(Gaming_field* field, int& x, int& y) {
	int max_score = field->count_score(color);
	vector<Gaming_field::keg> reverted_kegs;

	for (int i = 1; i <= field->get_height(); i++) {
		for (int j = 1; j <= field->get_width(); j++) {
			if (field->get_cell_state(j, i) == Gaming_field::KegColor::Empty) {
				reverted_kegs = field->place_keg_and_revert(j, i, color);

				int current_score = field->count_score(color);
				if (max_score <= current_score) {
					max_score = current_score;
					x = j, y = i;
				}

				field->redraw_line(reverted_kegs, Gaming_field::getOppositeCellState(color));
				field->erase_cell(j, i);
			}
		}
	}
}