#include "matrix_algebra.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int  n, k;
	cout << " Введите кол-во точек n: ";
	cin >> n;
	cout << " Введите степень полинома k (k < n): ";
	cin >> k;
	if (k >= n) {
		while (k >= n) {
			system("cls");
			cout << "Введенные данные не соответсвуют условию k < n. Введите их еще раз.\n";
			cout << " Введите кол-во точек n: ";
			cin >> n;
			cout << " Введите степень полинома k (k < n): ";
			cin >> k;
		}
	}

	vector<vector<double>> xy(n, vector<double>(2, 0));
	cout << endl << "Ввод точек." << endl;
	for (int i = 0; i < n; i++) {
		cout << "Введите координаты точки " << i + 1 << ":" << endl;
		for (int j = 0; j < 2; j++) {
			cout << "[" << i << "][" << j << "] - ";
			cin >> xy[i][j];
		}
	}
	cout << endl << "Введенные точки: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			cout << setw(15) << xy[i][j] << " ";
		}
		cout << endl << endl;
	}

	vector<vector<double>> A(k + 1, vector<double>(k + 1, 0));
	double sum = 0;
	for (int i = 0; i < k + 1; i++) {
		for (int j = 0, p = i; j < k + 1; j++, p++) {
			for (int m = 0; m < n; m++) {
				sum += pow(xy[m][0], p);
			}
			A[i][j] = sum;
			sum = 0;
		}
	}

	matrix_algebra ma;

	cout << "Матрица A: " << endl;
	ma.SetMatrixA(A);
	ma.PrintMatrixA();

	vector<double> b(k + 1, 0);
	for (int i = 0; i < k + 1; i++) {
		for (int j = 0; j < n; j++) {
			sum += (pow(xy[j][0], i) * xy[j][1]);
		}
		b[i] = sum;
		sum = 0;
	}
	cout << "Вектор b: ";
	ma.SetVectorB(b);
	ma.PrintVectorB();

	vector<double> p(b.size(), 0);
	ma.SetVectorP(p);

	if (ma.LUP() == false) {
		cout << "Матрица получилась вырожденной, СЛАУ недоопределена.\n";
		return;
	}

	vector<double> x(b.size(), 0);
	ma.SetVectorX(x);

	ma.LinearSystemSolution();
	ma.PrintSolution();
}