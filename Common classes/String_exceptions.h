#pragma once

class CharOverflow : public exception { // �a���� char[] ������� ������� ���������
public:
	CharOverflow() {
	}
};

class CharNullptr : public exception { // char* �������� nullptr
public:
	CharNullptr() {
	}
};

class Bad_transform_str_to_int : public exception {
private:
	string who;
public:
	const char* what() {
		return (who + " �� �������� ����� ��������������� ������").c_str();
	}

	Bad_transform_str_to_int(string s) : who(s) {}
};