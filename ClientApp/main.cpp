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

	while (1) {
		string linker_dir = read_ini("Files", "Linking_dir", "../Reversi.ini");
		string linker_filename = read_ini("Files", "Linker_filename", "../Reversi.ini");

		Visualiser* vis = new Console_visualiser();
		Competitor* comp = new Player(Competitor::ByArrows);
		Client* client = new Client(linker_dir + linker_filename, vis, comp);
		cout << "Введите 0, если хотите выйти, иначе введите любую другую строку: ";
		string _; cin >> _;
		if (_ == "0") break;
		int game_id = client->connect_to_server();
		client->play_game(game_id);
	}
}