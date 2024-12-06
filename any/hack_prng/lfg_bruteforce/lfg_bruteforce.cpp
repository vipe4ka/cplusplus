#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

unsigned long long int m = pow(2, 32),
					   n = 1000;

void main() {
	unsigned int start = clock();

	setlocale(LC_ALL, "Russian");

	unsigned long long int k, j;
	vector<unsigned long long int> x(n);

	ifstream file;
	file.open("numbers.txt");
	file.seekg(0, ios_base::beg);
	for (unsigned long long int i = 0; i < n; i++)
		file >> x[i];
	bool flag = false;
	unsigned long long int temp = 0;
	for (k = 2; k < m; k++) {
		file >> temp;
		x.push_back(temp);
		for (j = 1; j < k; j++) {
			flag = true;
			for (unsigned long long int i = 0; i < x.size() - k; i++) {
				if (x[i + k] != ((x[i + j] + x[i]) % m)) {
					flag = false;
					break;
				} 
			}
			if (flag) {
				cout << "Лаги: k = " << k << ", j = " << k - j << endl;
					break;
				}
			}
		if (flag) break;
	}

	unsigned int end = clock();
	unsigned int time = end - start;
	cout << "Время работы: " << time << " мс" << endl;
}