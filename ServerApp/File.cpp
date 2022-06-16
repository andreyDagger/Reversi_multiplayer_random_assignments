#include "File.h"

void File::clear() {
    file_input.close();
    file_output.close();
    file_input.open(filename, fstream::in | fstream::trunc);
    file_output.open(filename, fstream::out | fstream::trunc);
}

void File::move_to_begining() {
    file_input.seekg(file_input.beg);
    file_output.seekp(file_output.beg);
}

string File::read_whole_file() {
    string res, cur;
    while (getline(file_input, cur)) {
        cur.push_back('\n');
        res += cur;
    }
    return res;
}