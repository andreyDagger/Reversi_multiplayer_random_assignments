#include <iostream>
#include <vector>

#include "String_functions.h"
#include "String_exceptions.h"

using namespace std;

string String_functions::mult(string s, int x) {
    string ans = "";
    for (int i = 0; i < x; i++) {
        ans += s;
    }
    return ans;
}

int String_functions::strcmp1(char* s1, char* s2) {
    if (strlen(s1) > strlen(s2))
        return 1;
    if (strlen(s2) > strlen(s1))
        return -1;
    for (int i = 0; i < strlen(s1); i++)
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
    return 0;
}

vector<string> String_functions::split(const string s, char sep) {
    int last = 0;
    int i = 0;
    vector<string> ans;
    for (i = 0; i < strlen(s.c_str()); i++) {
        if (s[i] == sep) {
            ans.push_back(s.substr(last, i - last));
            last = i + 1;
        }
    }
    string last_str = s.substr(last, i - last);
    if (!last_str.empty())
        ans.push_back(last_str);
    return ans;
}

void String_functions::pchar_copy(char*& dest, const char* src) { // safe copying from one char* to another, you need to allocate memory for dest before using this function
    if (dest)
       free(dest);
    pchar_copy_dest_null(dest, src);
}

void String_functions::pchar_copy_dest_null(char*& dest, const char* src) {
    dest = (char*)calloc(strlen(src) + 1, sizeof(char));
    strcpy_s(dest, strlen(src) + 1, src);
}

string String_functions::char_to_str(const char* s) {
    string res = "";
    for (int i = 0; i < strlen(s); i++) {
        res.push_back(s[i]);
    }
    return res;
}

string String_functions::int_to_str(int n) {
    string res = "";
    while (n != 0) {
        res += char((n % 10) + 48);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int String_functions::str_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i]))
            throw Bad_transform_str_to_int(s);
        res = 10 * res + (s[i] - '0');
    }
    return res;
}

string String_functions::input_string() {
    char c;
    string res;

    while ((c = getchar()) == '\n') {}

    do {
        res += c;
        c = getchar();
    } while (c != EOF && c != '\n');

    return res;
}