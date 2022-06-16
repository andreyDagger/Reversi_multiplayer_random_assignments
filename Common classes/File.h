#pragma once

#include <fstream>

#include "../Common classes/String_functions.h"

using namespace std;

class File {
public:
	string filename;
	ifstream file_input;
	ofstream file_output;
	int input_mode, output_mode;

	const static int NULL_OPEN_MODE = 0;

	File(string fname, int in_mode, int out_mode) : filename(fname), input_mode(in_mode), output_mode(out_mode) {
		if (input_mode != NULL_OPEN_MODE)
			file_input.open(filename, input_mode);
		if (output_mode != NULL_OPEN_MODE)
			file_output.open(filename, output_mode);
	}

	void clear();
	void move_to_begining();
	string read_whole_file();
	void close();

	static string get_directory(string filename);

	// Исключения:

	class Bad_filename : public exception {
	private:
		string error_msg;
	public:
		Bad_filename(string message) : error_msg(message) {}

		const char* what() {
			return error_msg.c_str();
		}
	};
};