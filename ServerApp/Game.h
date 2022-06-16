#pragma once

#include "Client.h"
#include "C:\Users\Andrey\source\repos\Reversi_multiplayer_random_assignments\Common classes\Null_visualiser.h"
#include "../Common classes/Gaming_field.h"

class Game {
private:
	int id;
public:
	Gaming_field* field;
	Client* client1;
	Client* client2;
	int turn_counter = 0;

	int get_id() const { return id; }

	Game(int ID, Client* c1, Client* c2, int h, int w) : id(ID), client1(c1), client2(c2) {
		Visualiser* vis = new Null_visualiser();
		field = new Gaming_field(h, w, vis);
	}
};