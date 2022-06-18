#pragma once

#include <fstream>
#include <io.h>

#include "../Common classes/String_functions.h"

using namespace std;

class File {
public:
	int exceptions_count = 0; // Подряд количество раз, когда с файлом случались исключения

	string filename;
	ifstream file_input;
	ofstream file_output;
	int input_mode, output_mode;

	File() {
		file_output.exceptions(ofstream::failbit);
		file_input.exceptions(ifstream::failbit);
	}

	File(string fname) : filename(fname) {
		file_output.exceptions(ofstream::failbit);
		file_input.exceptions(ifstream::failbit);
	}

	File(string fname, int in_mode, int out_mode) : filename(fname), input_mode(in_mode), output_mode(out_mode) {
		file_output.exceptions(ofstream::failbit);
		file_input.exceptions(ifstream::failbit);

		file_input.open(filename, input_mode);
		file_output.open(filename, output_mode);
	}

	void clear();
	string read_whole_file();
	void close();
	int size();

	static string get_directory(string filename);
	static bool FileExists(const char* fname) {
		return _access(fname, 0) != -1;
	}

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