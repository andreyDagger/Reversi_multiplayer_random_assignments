#include "Client.h"

int Client::connect_to_server() {
	string whole_file = linker->read_whole_file();
	int pos = count(whole_file.begin(), whole_file.end(), '\n');
	whole_file += "0 0 0\n";

	try {
		linker->file_output.open(linker->filename, fstream::out | fstream::trunc);
		linker->file_output << whole_file;
		linker->file_output.close();

		linker->exceptions_count = 0;
	}
	catch (exception& e) {
		linker->exceptions_count++;
		if (linker->exceptions_count >= 10)
			print_error_message(e, linker);
	}

	int game_id;
	while (1) {
		Sleep(247);

		try {
			whole_file = linker->read_whole_file();
			linker->exceptions_count = 0;
		}
		catch (exception& e) {
			linker->exceptions_count++;
			if (linker->exceptions_count >= 10) {
				print_error_message(e, linker);
			}
		}

		vector<string> parsed = String_functions::split(whole_file, '\n');
		if (parsed.size() <= pos || parsed[pos] == "0 0 0")
			continue;

		vector<string> parsed_string = String_functions::split(parsed[pos], ' ');
		if (parsed_string.size() < 3)
			continue;

		id = String_functions::str_to_int(parsed_string[0]);
		game_id = String_functions::str_to_int(parsed_string[1]);
		is_first = String_functions::str_to_int(parsed_string[2]);
		competitor->color = Gaming_field::get_color(is_first);

		try {
			string pref = File::get_directory(linker->filename) + to_string(id) + "_" + to_string(game_id);
			
			client_to_server = new File(pref + "_client_server.txt");
			server_to_client = new File(pref + "_server_client.txt");
		}
		catch (File::Bad_filename& e) {
			vis->write("Error: " + String_functions::char_to_str(e.what()) + "\n", Black, Red);
			system("pause");
			exit(1);
		}

		return game_id;
	}
}

pair<int, int> Client::get_second_player_turn() {
	vis->write("Ждём второго игрока...");
	while (1) {
		int x = -1, y = -1, which_keg = -1;

		try {
			if (File::FileExists(server_to_client->filename.c_str())) {
				server_to_client->file_input.open(server_to_client->filename, fstream::in);
				int file_size = server_to_client->size();
				if (file_size > 0)
					server_to_client->file_input >> x >> y >> which_keg;
				server_to_client->file_input.close();
			}
			server_to_client->exceptions_count = 0;
		}
		catch (exception& e) {
			server_to_client->exceptions_count++;
			if (server_to_client->exceptions_count >= 10) {
				vis->write("Error: " + String_functions::char_to_str(e.what()) + "\n", Black, Red);
				system("pause");
				exit(1);
			}
		}

		if (field->count_kegs() == which_keg - 1 && x != -1 && y != -1 && which_keg != -1) {
			field->place_keg_and_revert(x, y, Competitor::get_opposite_color(competitor->color));
			return make_pair(x, y);
		}
	}
}

void Client::play_game(int game_id) {
	field = new Gaming_field(Gaming_field::CLASSIC_FIELD_SIZE, Gaming_field::CLASSIC_FIELD_SIZE, vis);
	competitor->write_player_color_message(vis);

	while (1) {
		if (field->count_kegs() == 4 && !is_first)
			get_second_player_turn();

		vis->write("Вы ходите...");
		pair<int, int> point = competitor->make_turn(field);
		int x = point.first;
		int y = point.second;

		try {
			client_to_server->file_output.open(client_to_server->filename, fstream::out | fstream::trunc);
			client_to_server->file_output << x << " " << y << " " << field->count_kegs() << " ";
			client_to_server->file_output.close();
			client_to_server->exceptions_count = 0;
		}
		catch (exception& e) {
			client_to_server->exceptions_count++;
			if (client_to_server->exceptions_count >= 10)
				print_error_message(e, client_to_server);
		}

		if (field->is_end())
			break;
		get_second_player_turn();
		if (field->is_end())
			break;
	}
	field->write_end_information();
	system("pause");
}

void Client::print_error_message(exception& e, File* file) {
	vis->write("Error: " + String_functions::char_to_str(e.what()) + ". File: " + file->filename + "\n", Black, Red);
	system("pause");
	exit(1);
}