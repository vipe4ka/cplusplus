#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int n = 250000, k;
double e;

unsigned long long int m = pow(2, 32);	//число m менять согласно используемому ГПСЧ

void Write(int i, vector<int> count);
void Check(double xi);

void Uniformity() {
	k = 100;
	e = static_cast<double>(n) / static_cast<double>(k);
	vector<int> count(k, 0);
	ifstream file;
	file.seekg(0, ios_base::beg);
	file.open("numbers.txt");
	for (int i = 0; i < n; i++) {
		unsigned long long int randNum;
		file >> randNum;
		double x = static_cast<double>(randNum) / m;
		double y = k * x;
		for (int j = 0; j < k; j++) {
			if (y >= j && y < j + 1) count[j]++;
		}
	}
	Write(1, count);
	double xi = 0.0;
	for (int j = 0; j < k; j++)
		xi += pow(count[j] - e, 2) / e;
	Check(xi);
}

void Series() {
	int d = 50;		//верхняя граница интервала случайных чисел
	k = pow(d, 2);	// число элементов в матрице
	e = 1.0 * n / k;
	vector<vector<int>> count(d, vector<int>(d, 0));
	ifstream file;
	file.seekg(0, ios_base::beg);
	file.open("numbers.txt");
	unsigned long long int randNum1, randNum2;
	file >> randNum1; 
	for (int i = 0; i < n - 1; i++) {
		file >> randNum2;
		double x1 = static_cast<double>(randNum1) / m, x2 = static_cast<double>(randNum2) / m;
		double y1 = d * x1, y2 = d * x2;
		int j1 = -1, j2 = -1;
		for (int j = 0; j < d; j++) { 
			if (y1 >= j && y1 < j + 1) j1 = j;
			if (y2 >= j && y2 < j + 1) j2 = j;
		}	
		if (j1 > -1 && j2 > -1) count[j1][j2]++;
		randNum1 = randNum2;
	}

	ofstream file1;
	file1.open("histogram2.csv");

	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++)
			file1 << count[i][j] << ';';
		file1 << endl;
	}
	
	double xi = 0.0;
	for (int i = 0; i < d; i++)
		for (int j = 0; j < d; j++)
		   xi += pow(count[i][j] - e, 2) / e;
	Check(xi);
}

void Intervals() {
	int t = 7;
	k = t + 1;
	vector<int> count(k, 0);
	double a = 0.0, b = 0.5;
	vector<double> pr(k);
	double p = b - a;
	for (int j = 0; j < count.size(); j++) pr[j] = p * pow(1 - p, j);
	vector<double> E(k);
	for (int j = 0; j < E.size(); j++) E[j] = pr[j] * n;

	vector<unsigned long long int> arr(k);
	ifstream file;
	file.seekg(0, ios_base::beg);
	file.open("numbers.txt");
	for (auto& i : arr) file >> i;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++)
			if ((arr[j] / static_cast<double>(m)) >= a && (arr[j] / static_cast<double>(m)) <= b) {
				count[j]++;
				break;
			}
		for (int i = 1; i < arr.size(); i++) arr[i - 1] = arr[i];
		file >> arr[arr.size() - 1];
	}
	Write(3, count);
	double xi = 0.0;
	for (int j = 0; j < k; j++)
		xi += pow(count[j] - E[j], 2) / E[j];
	Check(xi);
}

void Write(int i, vector<int> count) {
	ofstream file;
	string s1 = "histogram";
	string s2 = to_string(i);
	string s3 = ".csv";
	s1.append(s2);
	s1.append(s3);
	file.open(s1);
	for (int j = 0; j < k; j++)
		file << count[j] << endl;
}

void Check(double xi) {
	double nu = k - 1;
	vector<double> xp = { -2.33, -1.64, -0.674, 0.00, 0.674, 1.64, 2.33 };
	vector<double> xiCR(xp.size());
	for (int i = 0; i < xp.size(); i++)
		xiCR[i] = nu + sqrt(2.0 * nu) * xp[i] + (2.0 / 3.0) * pow(xp[i], 2) - (2.0 / 3.0);

	if (xi > xiCR[6]) cout << "ТЕСТ ПРОВАЛЕН" << endl;
	if (xi > xiCR[5] && xi < xiCR[6]) cout << "ТЕСТ ВЫЯВИЛ ПОДОЗРИТЕЛЬНОСТЬ" << endl;
	if (xi > xiCR[4] && xi < xiCR[5]) cout << "ТЕСТ ПРОЙДЕН. Отклонение 75-95%" << endl;
	if (xi > xiCR[3] && xi < xiCR[4]) cout << "ТЕСТ ПРОЙДЕН. Отклонение 50-75%" << endl;
	if (xi > xiCR[2] && xi < xiCR[3]) cout << "ТЕСТ ПРОЙДЕН. Отклонение 25-50%" << endl;
	if (xi > xiCR[1] && xi < xiCR[2]) cout << "ТЕСТ ПРОЙДЕН. Отклонение 5-25%" << endl;
	if (xi > xiCR[0] && xi < xiCR[1]) cout << "ТЕСТ ПРОЙДЕН. Отклонение 1-5%" << endl;
	if (xi < xiCR[0]) cout << "ТЕСТ ПРОЙДЕН. Отклонение менее 1%" << endl;
}

void main() {
	unsigned int start = clock();
	setlocale(LC_ALL, "Russian");

	cout << "Критерий равномерности: ";
	Uniformity();
	cout << "Критерий серий: ";
	Series();
	cout << "Критерий интервалов: ";
	Intervals();

	unsigned int end = clock();
	unsigned int time = end - start;
	cout << "Время работы: " << time << " мс" << endl;
}