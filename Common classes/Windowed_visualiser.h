#pragma once

#include <iostream>

#include "Visualiser.h"

class Windowed_visualiser : public Visualiser {
public:
	void draw_field(int, int);

	void input_coordinates(int& x, int& y); // осуществляет ввод координат
};