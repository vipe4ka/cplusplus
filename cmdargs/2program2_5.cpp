#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

void main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		if (argv[1] == nullptr) throw domain_error("Вы ничего не ввели");
		if (strcmp(argv[1], "-help") == 0) {
			cout << "Введите имя файла с расширением, а программа проверит его наличие в директории пользователя.\n";
			return;
		}
		ifstream file;
		file.open(argv[1]);
		if (!file.is_open())
			cout << "Файл " << argv[1] << " не найден.\n";
		else
			cout << "Файл " << argv[1] << " найден.\n";
		file.close();
	}
	catch (exception const& e) {
		cout << "Ошибка: " << e.what() << endl;
		return;
	}
}