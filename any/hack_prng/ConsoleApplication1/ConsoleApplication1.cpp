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
	SetConsoleCP(1251); //я русский
	SetConsoleOutputCP(1251);
	ifstream file;
	file.open("numbers.txt");
	assert(file.is_open()); //проверка на открытие файла

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
	//в чем смысл: сначала мы считываем числа из файла как char, затем с помощью метода stoi конвертируем число в int
	//если считался символ вместо числа, то метод stoi вызывает исключение

	file.close();
	cout << "Массив:\n";
	for (auto& i : A) cout << i << " ";
	cout << endl;

	int left{}, right{}, sum = 0;
	bool flag = false;
	for (auto& i : A)
		if (i < 0) {
			left = i;
			break;
		} //поиск первого отрицательного элемента
	for (auto& i : A)
		if (i >= 0) right = i; //поиск последнего положительного элемента

	for (int i = 0; i < A.size(); i++) {
		if (A[i] == left) { //суммирование после первого отрицательного
			for (int j = i + 1; j < A.size(); j++) {
				if (A[j] == right) break; //до последнего положительного
				sum += abs(A[j]);
			}
			break;
		}
	}
	assert(sum); //проверка на сумму: если необходимых элементов нет, то сумма будет равна нулю
	cout << "Сумма: " << sum << endl;
}