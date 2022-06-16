#pragma once

class CharOverflow : public exception { // –aзмер char[] массива слишком маленький
public:
	CharOverflow() {
	}
};

class CharNullptr : public exception { // char* оказалс€ nullptr
public:
	CharNullptr() {
	}
};

class Bad_transform_str_to_int : public exception {
private:
	string who;
public:
	const char* what() {
		return (who + " не €вл€етс€ целым неотрицательным числом").c_str();
	}

	Bad_transform_str_to_int(string s) : who(s) {}
};