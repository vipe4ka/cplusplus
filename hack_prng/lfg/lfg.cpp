#include <fstream>
#include <random>
#include <vector>
#include <iostream>

using namespace std;

unsigned int firstIndex = 12, //i - 5
			 secondIndex = 0, //i - 17
			 k = 17; //размер буфера (больший лаг)

unsigned long long int m = pow(2, 32);

vector<unsigned long long int> CreateBuffer() {
	vector<unsigned long long int> buffer;
	for (int i = 0; i < k; i++) buffer.push_back(rand());
	return buffer;
}

void main() {
	unsigned int start = clock();

	setlocale(LC_ALL, "Russian");

	ofstream file;
	vector<unsigned long long int> buffer = CreateBuffer();
	file.open("numbers.txt");
	for (int i = 0; i < 250000; i++) {
		unsigned long long int value = (buffer[secondIndex] + buffer[firstIndex]) % m;
		buffer.erase(buffer.begin());
		buffer.push_back(value);
		file << value << endl;
	}
	file.close();

	unsigned int end = clock();
	unsigned int time = end - start;
	cout << "Время работы: " << time << " мс" << endl;
}