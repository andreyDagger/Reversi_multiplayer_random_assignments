#include <iostream>
#include <cassert>

#include "Gaming_field.h"
#include "Visualiser.h"
#include "Console_visualiser.h"
#include "service.h"

using namespace std;

Gaming_field::Gaming_field(int width, int height, Visualiser* v) : width(width), height(height) {
	if (width < 2 || height < 2)
		throw Gaming_field::Bad_field_size(width, height);
	field = new KegColor * [height];
	for (int i = 0; i < height; i++) {
		field[i] = new KegColor[width];
		for (int j = 0; j < width; j++)
			field[i][j] = Empty;
	}

	field[height / 2 - 1][width / 2 - 1] = Black;
	field[height / 2][width / 2] = Black;
	field[height / 2][width / 2 - 1] = Red;
	field[height / 2 - 1][width / 2] = Red;

	vis = v;
	vis->draw_field(width, height);
	vis->draw_keg(width / 2, height / 2, ConsoleColor::Black);
	vis->draw_keg(width / 2 + 1, height / 2 + 1, ConsoleColor::Black);
	vis->draw_keg(width / 2, height / 2 + 1, ConsoleColor::Red);
	vis->draw_keg(width / 2 + 1, height / 2, ConsoleColor::Red);
}

Gaming_field::Gaming_field(Visualiser* v) : Gaming_field(CLASSIC_FIELD_SIZE, CLASSIC_FIELD_SIZE, v) {}

Gaming_field::Score Gaming_field::count_score() {
	Score score;
	score.black_player = 0;
	score.red_player = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == KegColor::Black)
				score.black_player++;
			else if (field[i][j] == KegColor::Red)
				score.red_player++;
		}
	}

	return score;
}

void Gaming_field::find_empty_cell(int& x, int& y) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == Empty) {
				x = j + 1;
				y = i + 1;
				return;
			}
		}
	}
	vis->write("Function Gaming_field::find_empty_cell() couldn't find empty_cell");
	assert(0);
}

int Gaming_field::count_score(KegColor type) {
	if (type == Black)
		return count_black_score();
	else if (type == Red)
		return count_red_score();
	else {
		vis->write("Type of Player is not defined in function Gaming_field::count_score\n", ConsoleColor::Black, ConsoleColor::Red);
		assert(0);
	}
}

int Gaming_field::count_red_score() {
	return count_score().red_player;
}

int Gaming_field::count_black_score() {
	return count_score().black_player;
}

string Gaming_field::write_end_information() {
	Score score = count_score();

	if (score.black_player > score.red_player) {
		vis->write("Black player wins\n", ConsoleColor::Black, ConsoleColor::Green);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Black player wins\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n";
	}
	else if (score.black_player < score.red_player) {
		vis->write("Red player wins\n", ConsoleColor::Black, ConsoleColor::Green);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Red player wins\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed_player: " + String_functions::int_to_str(score.red_player) + "\n";
	}
	else {
		vis->write("Draw\n", ConsoleColor::Black, ConsoleColor::Yellow);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Draw\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n";
	}
}

int Gaming_field::count_kegs() {
	int res = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] != KegColor::Empty)
				res++;
		}
	}
	return res;
}

bool Gaming_field::is_end() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == KegColor::Empty)
				return false;
		}
	}
	return true;
}

vector<Gaming_field::keg> Gaming_field::place_keg_and_revert(int x, int y, KegColor keg_type) {

	if (x <= 0 || x > width || y <= 0 || y > height)								//----
		throw Bad_turn("“ак нельз€ ходить, вы вышли за рамки пол€");			//   |---> Ёто проверка на правильность хода
	if (field[y - 1][x - 1] != Empty)											  	//   |
		throw Bad_turn("“ак нельз€ ходить, в этой клетке уже стоит фишка"); 	//----																																	  

	if (keg_type != KegColor::Black && keg_type != KegColor::Red) {
		vis->write("Unknown color (type) of keg in function place_keg()\n", ConsoleColor::Black, ConsoleColor::Red);
		assert(0);
	}
	else
		place_keg(x, y, keg_type);
	
	return revert_kegs(x, y, keg_type);
}

void Gaming_field::place_keg(int x, int y, KegColor keg_type) {
	field[y - 1][x - 1] = keg_type;
	vis->draw_keg(x, y, getConsoleColor(keg_type));
}

vector<Gaming_field::keg> Gaming_field::redraw_line(int x1, int y1, int x2, int y2, KegColor keg_type, Direction dir) {
	vector<Gaming_field::keg> res;

	switch (dir) {
	case Up: case Down:
		arrange(y1, y2);
		for (int i = y1 - 1; i < y2; i++) {
			place_keg(x1, i + 1, keg_type);
			if (i != y1 - 1 && i != y2 - 1)
				res.push_back({x1, i + 1});
		}
		break;
	case Left: case Right:
		arrange(x1, x2);
		for (int i = x1 - 1; i < x2; i++) {
			place_keg(i + 1, y1, keg_type);
			if (i != x1 - 1 && i != x2 - 1)
				res.push_back({ i + 1, y1 });
		}
		break;
	case Up_left: case Down_right:
		arrange(x1, x2);
		arrange(y1, y2);
		for (int i = x1 - 1, j = y1 - 1; i < x2 && j < y2; i++, j++) {
			place_keg(i + 1, j + 1, keg_type);
			if (i != x1 - 1 && i != x2 - 1)
				res.push_back({ i + 1, j + 1 });
		}
		break;
	case Up_right: case Down_left:
		arrange(x1, x2);
		arrange(y1, y2);
		for (int i = x1 - 1, j = y2 - 1; i <= x2 && j >= y1; i++, j--) {
			place_keg(i + 1, j + 1, keg_type);
			if (i != x1 - 1 && i != x2)
				res.push_back({ i + 1, j + 1 });
		}
		break;
	default:
		vis->write("Unknown \"Direction\" in function \"Gaming_field::redraw_line()\"\n", ConsoleColor::Black, ConsoleColor::Red);
		assert(0);
	}

	return res;
}

void Gaming_field::redraw_line(vector<keg> kegs, KegColor keg_type) {
	for (int i = 0; i < kegs.size(); i++) {
		place_keg(kegs[i].first, kegs[i].second, keg_type);
	}
}

void Gaming_field::erase_cell(int x, int y) {
	field[y - 1][x - 1] = Empty;
	vis->erase_cell(x, y);
}