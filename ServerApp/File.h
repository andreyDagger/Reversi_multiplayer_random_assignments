#pragma once

#include <string>
#include <fstream>

using namespace std;

class File {
public:
	const char* filename;
	ifstream file_input;
	ofstream file_output;
	int input_mode, output_mode;

	const int NULL_OPEN_MODE = 0;

	File(const char* fname, int in_mode, int out_mode) : filename(fname), input_mode(in_mode), output_mode(out_mode) {
		if (input_mode != NULL_OPEN_MODE)
			file_input.open(filename, input_mode);
		if (output_mode != NULL_OPEN_MODE)
			file_output.open(filename, output_mode);
	}

	void clear();
	void move_to_begining();
	string read_whole_file();
};