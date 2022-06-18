#pragma once

#include "C:\Users\Andrey\source\repos\Reversi_multiplayer_random_assignments\Common classes\File.h"

class Client {
private:
	int id;
public:
	File* client_to_server;
	File* server_to_client;
	bool is_first = false;

	int get_id() const { return id; }

	Client(int ID, string client_server_fname, string server_client_fname) : id(ID) {
		client_to_server = new File(client_server_fname);
		server_to_client = new File(server_client_fname);
	}
};