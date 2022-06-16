#include "Gaming_field.h"
#include "service.h"

using namespace std;

typedef Gaming_field::keg keg;

vector<keg> Gaming_field::revert_kegs(int x, int y, KegColor keg_type) {
	int x_1, y_1; // координаты фишки, стоящей напротив нашей
	vector<keg> res, temp;

	if (find_up_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Up);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_down_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Down);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_right_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Right);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_left_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Left);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_up_left_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Up_left);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_up_right_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Up_right);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_down_left_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Down_left);
		concatenate<vector<keg>>(res, temp);
	}
	if (find_down_right_same_color(x, y, keg_type, &x_1, &y_1)) {
		temp = redraw_line(x, y, x_1, y_1, keg_type, Down_right);
		concatenate<vector<keg>>(res, temp);
	}

	return res;
}

bool Gaming_field::find_up_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = y - 1; i > 0; i--) {
		if (field[i - 1][x - 1] == Empty)
			return false;
		if (field[i - 1][x - 1] == keg_type) {
			*x_1 = x;
			*y_1 = i;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_down_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = y + 1; i <= height; i++) {
		if (field[i - 1][x - 1] == Empty)
			return false;
		if (field[i - 1][x - 1] == keg_type) {
			*x_1 = x;
			*y_1 = i;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x + 1; i <= width; i++) {
		if (field[y - 1][i - 1] == Empty)
			return false;
		if (field[y - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = y;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x - 1; i > 0; i--) {
		if (field[y - 1][i - 1] == Empty)
			return false;
		if (field[y - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = y;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_up_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x + 1, j = y - 1; i <= width && j > 0; i++, j--) {
		if (field[j - 1][i - 1] == Empty)
			return false;
		if (field[j - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = j;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_up_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x - 1, j = y - 1; i > 0 && j > 0; i--, j--) {
		if (field[j - 1][i - 1] == Empty)
			return false;
		if (field[j - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = j;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_down_right_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x + 1, j = y + 1; i <= width && j <= height; i++, j++) {
		if (field[j - 1][i - 1] == Empty)
			return false;
		if (field[j - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = j;
			return true;
		}
	}
	return false;
}

bool Gaming_field::find_down_left_same_color(int x, int y, KegColor keg_type, int* x_1, int* y_1) {
	for (int i = x - 1, j = y + 1; i > 0 && j <= height; i--, j++) {
		if (field[j - 1][i - 1] == Empty)
			return false;
		if (field[j - 1][i - 1] == keg_type) {
			*x_1 = i;
			*y_1 = j;
			return true;
		}
	}
	return false;
}