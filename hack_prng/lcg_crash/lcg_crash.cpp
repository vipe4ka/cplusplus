#include <clocale>
#include <iostream>
#include <array>
#include <fstream>
#include <ctime>

#define arraySize 5

using namespace std;

unsigned int modInverse(unsigned int af, unsigned int mf) {
	int t, nt, r, nr, q, tmp;
	t = 0;  nt = 1;  r = mf;  nr = af % mf;
	while (nr != 0) {
		q = r / nr;
		tmp = nt;  nt = t - q * nt;  t = tmp;
		tmp = nr;  nr = r - q * nr;  r = tmp;
	}
	if (r > 1) return -1;
	if (t < 0) t += mf;
	return t;
}

void main() {
	unsigned int start = clock();

	setlocale(LC_ALL, "Russian");
	
	unsigned int mods[arraySize];
	ifstream file;
	file.open("numbers.txt");
	for (int i = 0; i < arraySize; i++)
		file >> mods[i];
	file.close();

	unsigned int aFind = 1,
				 mFind = 2,
				 cFind = 1;
	bool flag;
	for (auto& i : mods)
		if (i > mFind) mFind = i;
	mFind++;

	for (mFind; mFind < UINT_MAX; ++mFind) {
		int d0 = (mods[1] - mods[0]);  if (d0 < 0) d0 += mFind;
		int d1 = (mods[2] - mods[1]);  if (d1 < 0) d1 += mFind;
		int d2 = (mods[3] - mods[2]);  if (d2 < 0) d2 += mFind;
		int d3 = (mods[4] - mods[3]);  if (d3 < 0) d3 += mFind;

		int inverse = modInverse(d0, mFind);
		if (inverse < 0) continue;
		aFind = (d1 * inverse) % mFind;

		int my_diff1 = (aFind * d0) % mFind;
		int my_diff2 = (aFind * d1) % mFind;
		int my_diff3 = (aFind * d2) % mFind;

		if (my_diff1 != d1) {
			flag = false;
			continue;
		}

		if (my_diff2 == d2 && my_diff3 == d3) {
			flag = true;
			break;
		}
		else flag = false;
	}

	if (flag == false) {
		cout << "Значения a и m не могут быть найдены.";
		return;
	}

	flag = false;
	for (cFind; cFind < UINT_MAX / 1000; cFind++)
		if ((aFind * mods[0] + cFind) % mFind == mods[1]) {
			flag = true;
			break;
		}

	cout << "НАЙДЕНЫ ЗНАЧЕНИЯ:\n";
	cout << "a = " << aFind << "\nm = " << mFind;
	if (flag == true)
		cout << "\nc = " << cFind << endl;
	else {
		cout << "\nЗначение с не может быть найдено.\n";
	}

	unsigned int end = clock();
	unsigned int time = end - start;
	cout << endl << "Время работы: " << time << " мс" << endl;
}