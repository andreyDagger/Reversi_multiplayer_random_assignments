#pragma once

// Some helpful functions to work with strings

#include <iostream>
#include <vector>

using namespace std;

class String_functions {
public:
	static vector<string> split(const string s, char sep); // разделяет строку по [sep] и возвращает vector из слов, которые были разделены [sep]
	static string mult(string, int); // умножает строку на число n (повторяет n раз)

	static void pchar_copy(char*& dest, const char* src); // safe copying from one char* to another
	static void pchar_copy_dest_null(char*& dest, const char* src); // safe copying from one char* to another if dest = nullptr

	static int strcmp1(char* s1, char* s2); // сравнение строк с приоритетом на длину

	static string char_to_str(const char* s); // transforms char to string
	static string int_to_str(int); // transforms int to string
	static int str_to_int(string); // transforms string to int

	static string input_string();
};