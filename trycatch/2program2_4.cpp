#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <array>
#include <cassert>
#include <limits>

#define MAX 255

using namespace std;
static const int n = 10;

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream file;
	file.open("numbers.txt");
	assert(file.is_open());

	array<int, n> A{};
	for (auto& i : A) {
		char numChar[MAX];
		int num;
		try {
			file.getline(numChar, MAX, '\n');
			num = stoi(numChar);
		}
		catch (exception const& e) {
			cout << "Ошибка: " << e.what() << endl;
			return;
		}
		i = num;
	}

	file.close();
	cout << "Массив:\n";
	copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));

	int element = 0;
	for (auto& i : A) {
		if (i < 0 && element == 0) element = i;
		else if (i < 0 && i > element) element = i;
	}

	try {
		if (element == 0) throw domain_error("В массиве нет отрицательного элемента.");
		cout << "Наибольший отрицательный элемент: " << element << endl;
	}
	catch (exception const& e) {
		cout << "Ошибка: " << e.what() << endl;
	}
}