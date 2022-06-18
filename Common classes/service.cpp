#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sys\stat.h>

#include "String_functions.h"
#include "service.h"

using namespace std;

void set_global_var(int value) {
    GLOBAL_VARIABLE = value;
}

int get_global_var() {
    return GLOBAL_VARIABLE;
}

void SetConsoleColor(ConsoleColor color_back, ConsoleColor color_text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((color_back << 4) | color_text));
}

void print_color(const char* s, ConsoleColor color_back, ConsoleColor color_text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((color_back << 4) | color_text));
    cout << s;
    SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
}

void print_color_endl(const char* s, ConsoleColor color_back, ConsoleColor color_text) {
    print_color(s, color_back, color_text);
    cout << endl;
}

void SetConsoleCursorPos(int x, int y) {
    COORD position;										// Объявление необходимой структуры
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
    position.X = x;									// Установка координаты X
    position.Y = y;									// Установка координаты Y
    SetConsoleCursorPosition(hConsole, position);
}

string read_ini(const char* section, const char* key_name, const char* filename, const char* def) {
    char buf[MAXINIKEYSIZE];
    SetLastError(0);
    GetPrivateProfileStringA(section, key_name, def, buf, MAXINIKEYSIZE, \
        filename);
    int error_code = GetLastError();
    if (error_code != 0) {
        cout << "In file " << filename << "In section " << section << " " << "key name " << key_name << " wasn't found\n";
        exit(1);
    }
    return String_functions::char_to_str(buf);
}