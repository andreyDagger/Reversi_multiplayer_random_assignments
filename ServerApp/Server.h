#pragma once

#include <vector>
#include <fstream>
#include <map>

#include "Client.h"
#include "Game.h"
#include "C:/Users/Andrey/source/repos/Reversi_multiplayer_random_assignments/Common classes/File.h"

using namespace std;

/// <summary>
/// 
///	
///	
///	
///																Заменяет "0 0 0" на "cl_id game_id is_first"
///														[-------------------------------------------------------]
///														|														|
///											"0 0 0"		V				Считывает "0 0 0"						|
///	I)  Сервер подключает клиентов:    Client---->linker.txt------------------------------------------------>Server
///										 ^			    |
///										 |				|
///										 [--------------]
///											Считывает
///									  "cl_id game_id is_first"
///											
/// 
/// 
///							  [---------[game_id]_[client1_id]_to_client.txt<----]
///							  |													 |
///							  V													 |
///	II)  Клиент играет:   Client1---->[game_id]_[client1_id]_to_server.txt---->Server---->[game_id]_[client2_id]_to_client.txt
///																				 ^  					|
///																				 |						|
///																				 |						V
///															[game_id]_[client2_id]_to_server.txt<----Client2
/// 
/// 
/// </summary>

class Server {
private:
	File* linker;

	map<int, pair<int, int>> game_to_clients; // [game_id, {client1, client2}]
	vector<Game*> running_games;

	int next_game_id = 1;
	int next_client_id = 1;

	void assign_clients();
	vector<pair<int, int>> replace_0_0(vector<string>& parsed); // заменяет строки "0 0" на "[client_id] [game_id]", возвращает вектор пар \
																	[client_id] [game_id], которые были поставлены вместо "0 0"
	Client* create_client(int client_id, int game_id);
	void connect_two_clients(Client*, Client*, int game_id);
	void check_running_games();
	bool check_game(Game*); // Возвращает true, если игра закончилась
public:
	Server(string linker_filename) {
		linker = new File(linker_filename.c_str(), fstream::in, fstream::out | fstream::trunc);
	}

	void start_server();
};