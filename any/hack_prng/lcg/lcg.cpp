#include <fstream>
#include <iostream>
#include <conio.h>
#include <ctime>

#define arraySize 250000

using namespace std;
unsigned int SEED = 1477,
			 a = 4331,
			 c = 3492,
			 m = 7902;

unsigned int lcg() {
	SEED = (a * SEED + c) % m;
	return SEED;
}

void main() {
	unsigned int start = clock();

	setlocale(LC_ALL, "Russian");

	ofstream file;
	file.open("numbers.txt");

	int i = 0;
	for (int i = 0; i < arraySize; i++)
		file << lcg() << endl;
	file.close();

	unsigned int end = clock();
	unsigned int time = end - start;
	cout << "Время работы: " << time << " мс" << endl;

	/*while (1) {
		cout << lcg() << endl;
		_getch();
	}*/
}