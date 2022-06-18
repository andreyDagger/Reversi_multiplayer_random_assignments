#include <string>
#include <Windows.h>
#include <cassert>

#include "../Common classes/String_functions.h"
#include "Server.h"

Server::Server(string linker_filename) {
	// Удаляем все файлы, созданные на предыдущем запуске сервера
	string linker_dir;
	try {
		linker_dir = File::get_directory(linker_filename);
	}
	catch (File::Bad_filename& e) {
		print_color_endl(("Error: " + String_functions::char_to_str(e.what())).c_str(), Black, Red);
		system("pause");
		exit(1);
	}

	for (int cl_id = 1; cl_id <= MAX_CLIENT_ID; cl_id++) {
		for (int game_id = 1; game_id <= MAX_GAME_ID; game_id++) {
			remove((linker_dir + to_string(cl_id) + "_" + to_string(game_id) + "_" + "server_client.txt").c_str());
			remove((linker_dir + to_string(cl_id) + "_" + to_string(game_id) + "_" + "client_server.txt").c_str());
		}
	}

	linker = new File(linker_filename);
	try {
		linker->clear();
	}
	catch (exception& e) {
		print_error_message(e, linker);
	}
}

void Server::assign_clients() {
	string whole_file;
	try {
		whole_file = linker->read_whole_file();
		linker->exceptions_count = 0;
	}
	catch (exception& e) {
		linker->exceptions_count++;
		if (linker->exceptions_count >= 10)
			print_error_message(e, linker);
	}

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
		Client*	client2 = create_client(client2_id, game_id);
		
		connect_two_clients(client1, client2, game_id);
	}
	game_to_clients.clear();
	if (to_add1 != -1)
		game_to_clients[to_add1] = make_pair(to_add2, -1); // Если клиентов нечетное количество то один клиент останется и мы его запомним

	try {
		linker->file_output.open(linker->filename, fstream::out | fstream::trunc);
		for (int i = 0; i < parsed.size(); i++)
			linker->file_output << parsed[i] << "\n";
		linker->file_output.close();
	}
	catch (exception& e) {
		print_error_message(e, linker);
	}
}

Client* Server::create_client(int client_id, int game_id) {
	string dir;
	try {
		dir = File::get_directory(linker->filename);
	}
	catch (exception& e) {
		print_error_message(e, linker);
	}

	string pref = dir + to_string(client_id) + "_" + to_string(game_id);
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
		if (check_game(game)) { // Если true, то игра закончилась
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

	int x1 = -1, y1 = -1, which_keg1 = -1; // x1, y1 - Ход первого игрока; which_keg1 - какой по счету была фишка
	int x2 = -1, y2 = -1, which_keg2 = -1;

	check_if_made_turn(f1_input, x1, y1, which_keg1);
	check_if_made_turn(f2_input, x2, y2, which_keg2);

	make_turn_and_output(x1, y1, which_keg1, f2_output, game);
	make_turn_and_output(x2, y2, which_keg2, f1_output, game);

	if (game->field->is_end())
		return true;
	return false;
}

void Server::start_server() {
	cout << "Server is working...\n";
	while (1) {
		Sleep(387);
		assign_clients();
		check_running_games();
	}
}

void Server::print_error_message(exception& e, File* file) {
	print_color_endl(("Error " + String_functions::char_to_str(e.what()) + ". File: " + file->filename + "\n").c_str(), Black, Red);
	system("pause");
	exit(1);
}

void Server::check_if_made_turn(File* client_to_serv, int& x, int& y, int& which_keg) {
	try {
		if (File::FileExists(client_to_serv->filename.c_str())) {
			client_to_serv->file_input.open(client_to_serv->filename, fstream::in);
			int file_size = client_to_serv->size();
			if (file_size > 0)
				client_to_serv->file_input >> x >> y >> which_keg;
			client_to_serv->file_input.close();
		}
		client_to_serv->exceptions_count = 0;
	}
	catch (exception& e) {
		client_to_serv->exceptions_count++;
		if (client_to_serv->exceptions_count >= 10)
			print_error_message(e, client_to_serv);
	}
}

void Server::make_turn_and_output(int x, int y, int which_keg, File* file, Game* game) {
	if (game->field->count_kegs() == which_keg - 1 && x != -1 && y != -1) {
		game->turn_counter++;
		game->field->place_keg_and_revert(x, y, Gaming_field::KegColor::Red);

		try {
			file->file_output.open(file->filename, fstream::out | fstream::trunc);
			file->file_output << x << " " << y << " " << which_keg << " ";
			file->file_output.close();
			file->exceptions_count = 0;
		}
		catch (exception& e) {
			file->exceptions_count++;
			if (file->exceptions_count >= 10)
				print_error_message(e, file);
		}
	}
}