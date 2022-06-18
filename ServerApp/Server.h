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
///																�������� "0 0 0" �� "cl_id game_id is_first"
///														[-------------------------------------------------------]
///														|														|
///											"0 0 0"		V				��������� "0 0 0"						|
///	I)  ������ ���������� ��������:    Client---->linker.txt------------------------------------------------>Server
///										 ^			    |
///										 |				|
///										 [--------------]
///											���������
///									  "cl_id game_id is_first"
///											
/// 
/// 
///							  [---------[game_id]_[client1_id]_to_client.txt<----]
///							  |													 |
///							  V													 |
///	II)  ������ ������:   Client1---->[game_id]_[client1_id]_to_server.txt---->Server---->[game_id]_[client2_id]_to_client.txt
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
	vector<pair<int, int>> replace_0_0(vector<string>& parsed); // �������� ������ "0 0" �� "[client_id] [game_id]", ���������� ������ ��� \
																	[client_id] [game_id], ������� ���� ���������� ������ "0 0"
	Client* create_client(int client_id, int game_id);
	void connect_two_clients(Client*, Client*, int game_id);

	void check_running_games();
	bool check_game(Game*); // ���������� true, ���� ���� �����������
	void check_if_made_turn(File* client_to_serv, int& x, int& y, int& which_keg); // ����������, ������ �� ��� ������
	void make_turn_and_output(int x, int y, int which_keg, File* file, Game* game); // ������� ��� ������ ������� � ���� ��� ������� �������
public:
	const static int MAX_CLIENT_ID = 10;
	const static int MAX_GAME_ID = 10;

	Server(string linker_filename);

	void start_server();
	void print_error_message(exception&, File*); // ������� ��������� �� ������ � �������� exit(1)
};