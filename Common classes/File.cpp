#include <string>
#include <algorithm>
#include <cassert>

#include "File.h"

using namespace std;

void File::clear() {
    file_input.close();
    file_output.close();
    file_input.open(filename, fstream::in | fstream::trunc);
    file_output.open(filename, fstream::out | fstream::trunc);
}

void File::move_to_begining() {
    assert(0); // Эта функция не работает
    file_input.seekg(0, file_input.beg);
    file_output.seekp(0, file_input.beg);
}

string File::read_whole_file() {
    file_input.close();
    file_input.open(filename, fstream::in);
    string res, cur;
    while (getline(file_input, cur)) {
        cur.push_back('\n');
        res += cur;
    }
    return res;
}

string File::get_directory(string filename) {
    for (int i = (int)filename.length() - 1; i >= 0; i--) {
        if (filename[i] == '/' || filename[i] == '\\') {
            string res = "";
            for (; i >= 0; i--) res += filename[i];
            reverse(res.begin(), res.end());
            return res;
        }
    }
    throw Bad_filename("Файл " + filename + " Должен иметь абсолютное имя");
}

void File::close() {
    file_input.close();
    file_output.close();
}