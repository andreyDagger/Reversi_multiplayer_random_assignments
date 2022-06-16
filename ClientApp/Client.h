#pragma once

#include "C:/Users/Andrey/source/repos/Reversi_multiplayer_random_assignments/Common classes/File.h"
#include "C:/Users/Andrey/source/repos/Reversi_multiplayer_random_assignments/Common classes/Competitor.h"
#include "C:/Users/Andrey/source/repos/Reversi_multiplayer_random_assignments/Common classes/Gaming_field.h"
#include "C:/Users/Andrey/source/repos/Reversi_multiplayer_random_assignments/Common classes/String_functions.h"

class Client {
public:
	int connect_to_server(); // возвращает id игры, к которому подключилс€ клиент
	void play_game(int game_id); // играет игру

	Client(string linker_filename, Visualiser* Vis, Competitor* comp) : vis(Vis), competitor(comp) {
		linker = new File(linker_filename, fstream::in | fstream::ate, fstream::app | fstream::ate);
	}
private:
	Competitor* competitor;
	Gaming_field* field;
	Visualiser* vis;

	bool is_first = false;
	int id;

	File* linker;

	File* client_to_server;
	File* server_to_client;

	pair<int, int> get_second_player_turn(); // ∆дЄт, пока второй игрок сходит
};