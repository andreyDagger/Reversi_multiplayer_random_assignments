#include <iostream>
#include <AccCtrl.h>
#include <string>

#include "../Common classes/Console_visualiser.h"
#include "../Common classes/String_functions.h"
#include "Client.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	string linker_dir = read_ini("Files", "Linking_dir", "../Reversi.ini");
	string linker_filename = read_ini("Files", "Linker_filename", "../Reversi.ini");
	while (1) {
		Visualiser* vis = new Console_visualiser();
		vis->clear();
		Competitor* comp = new Player(Competitor::ByArrows);
		Client* client = new Client(linker_dir + linker_filename, vis, comp);

		vis->write("Введите 0, если хотите выйти, иначе введите любую другую строку: ");
		string what = vis->input_string();
		if (what == "0")
			break;

		int game_id = client->connect_to_server();
		client->play_game(game_id);
	}
}