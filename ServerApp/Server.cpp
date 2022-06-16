#include <string>
#include <Windows.h>
#include <cassert>

#include "../Common classes/String_functions.h"
#include "Server.h"

void Server::assign_clients() {
	string whole_file = linker->read_whole_file();
	vector<string> parsed = String_functions::split(whole_file, '\n');

	replace_0_0(parsed);
	
	int to_add1 = -1, to_add2 = -1;
	for (auto& temp : game_to_clients) {
		int game_id = temp.first;
		int client1_id = temp.second.first;
		int client2_id = temp.second.second;

		if (client2_id == -1) {
			to_add1 = game_id;
			to_add2 = client1_id;
			continue;
		}

		Client* client1 = create_client(client1_id, game_id);
		Client* client2 = create_client(client2_id, game_id);
		
		connect_two_clients(client1, client2, game_id);
	}
	game_to_clients.clear();
	if (to_add1 != -1)
		game_to_clients[to_add1] = make_pair(to_add2, -1); // ≈сли клиентов нечетное количество то один клиент останетс€ и мы его запомним


	linker->clear();
	for (int i = 0; i < parsed.size(); i++) {
		linker->file_output << parsed[i] << "\n";
		linker->file_output.flush();
	}
}

Client* Server::create_client(int client_id, int game_id) {
	string pref = File::get_directory(linker->filename) + to_string(client_id) + "_" + to_string(game_id);
	Client* res = new Client(client_id, pref + "_client_server.txt", \
		pref + "_server_client.txt");
	return res;
}

vector<pair<int, int>> Server::replace_0_0(vector<string>& parsed) {
	vector<pair<int, int>> res;
	for (int i = 0; i < parsed.size(); i++) {
		if (parsed[i] == "0 0 0") {
			if (game_to_clients.find(next_game_id) != game_to_clients.end()) {
				parsed[i] = to_string(next_client_id) + " " + to_string(next_game_id) + " 0";
				res.push_back(make_pair(next_client_id, next_game_id));

				game_to_clients[next_game_id].second = next_client_id;
				next_game_id++;
			}
			else {
				parsed[i] = to_string(next_client_id) + " " + to_string(next_game_id) + " 1";
				res.push_back(make_pair(next_client_id, next_game_id));

				game_to_clients[next_game_id].first = next_client_id;
				game_to_clients[next_game_id].second = -1;
			}
			next_client_id++;
		}
	}
	return res;
}

void Server::connect_two_clients(Client* client1, Client* client2, int game_id) {
	client1->is_first = true;
	client2->is_first = false;
	Game* game = new Game(game_id, client1, client2, Gaming_field::CLASSIC_FIELD_SIZE, Gaming_field::CLASSIC_FIELD_SIZE);
	running_games.push_back(game);
}

void Server::check_running_games() {
	for (int i = 0; i < running_games.size(); i++) {
		Game* game = running_games[i];
		if (check_game(game)) { // ≈сли true, то игра закончилась
			running_games.erase(running_games.begin() + i);
			i--;
		}
	}
}

bool Server::check_game(Game* game) {
	File*& f1_input = game->client1->client_to_server;
	File*& f2_input = game->client2->client_to_server;
	File*& f1_output = game->client1->server_to_client;
	File*& f2_output = game->client2->server_to_client;

	f1_input->file_input.close();
	f1_input->file_input.open(f1_input->filename, fstream::in);
	f2_input->file_input.close();
	f2_input->file_input.open(f2_input->filename, fstream::in);

	int x1 = -1, y1 = -1, which_keg1 = -1; // x1, y1 - ’од первого игрока; which_keg1 - какой по счету была фишка
	int x2 = -1, y2 = -1, which_keg2 = -1; 
	f1_input->file_input >> x1 >> y1 >> which_keg1;
	f2_input->file_input >> x2 >> y2 >> which_keg2;

	if (game->field->count_kegs() == which_keg1 - 1 && x1 != -1 && y1 != -1) {
		game->turn_counter++;
		game->field->place_keg_and_revert(x1, y1, Gaming_field::KegColor::Red);

		f2_output->file_output.close();
		f2_output->file_output.open(f2_output->filename, fstream::out | fstream::trunc);
		f2_output->file_output << x1 << " " << y1 << " " << which_keg1 << " ";
		f2_output->file_output.flush();
	}
	else if (game->field->count_kegs() == which_keg2 - 1 && x2 != -1 && y2 != -1 && which_keg2 != -1) {
		game->turn_counter++;
		game->field->place_keg_and_revert(x2, y2, Gaming_field::KegColor::Black);

		f1_output->file_output.close();
		f1_output->file_output.open(f1_output->filename, fstream::out | fstream::trunc);
		f1_output->file_output << x2 << " " << y2 << " " << which_keg2 << " ";
		f1_output->file_output.flush();
	}
	if (game->field->is_end())
		return true;
	return false;
}

void Server::start_server() {
	cout << "Server is working...\n";
	while (1) {
		Sleep(100);
		assign_clients();
		check_running_games();
	}
}