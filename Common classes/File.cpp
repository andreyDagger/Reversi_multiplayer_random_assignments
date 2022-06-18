#include <string>
#include <algorithm>
#include <cassert>

#include "File.h"

using namespace std;

void File::clear() {
    file_output.open(filename, fstream::out | fstream::trunc);
    file_output.close();
}

string File::read_whole_file() {
    file_input.open(filename, fstream::in);
    string res, cur;
    try {
        while (1) {
            getline(file_input, cur);
            cur.push_back('\n');
            res += cur;
        }
    }
    catch (exception& e) {
        file_input.close();
        return res;
    }
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

int File::size() {
    std::ifstream file(filename.c_str(), std::ios_base::binary);
    long nFileLen = 0;
    if (file)
    {
        file.seekg(0, std::ios_base::end);
        nFileLen = file.tellg();
        file.close();
    }
    return nFileLen;
}