#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>

#define arraySize 5

using namespace std;

unsigned int SEED = time(0),
a = 211,
c = 1663,
m = 7875;

unsigned int lcg() {
	SEED = (a * SEED + c) % m;
	return SEED;
}

void main() {
	ifstream file;
	file.open("C://Users//79011//source//repos//2 курс//курсач//lcg_crash//numbers.txt");

	unsigned int array[arraySize]{};
	for (int i = 0; i < arraySize; i++)
		file >> array[i];


	int cur = 0;
	while (cur < arraySize) {
		if (array[cur] == lcg()) cur++;
		else cur = 0;
	}

	while (1) {
		cout << lcg() << endl;
		_getch();
	}
}