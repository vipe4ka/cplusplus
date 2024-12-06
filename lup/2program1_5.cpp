#include "lup.h"
#include "Levenberg_Marquardt.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int r = 3;

double func(double x, vector<double> omega) {
	return omega[0] * sin(omega[1] * x + omega[2]);
}

vector<vector<double>> operator+(vector<vector<double>>& A, vector<vector<double>>& _A) {
	vector<vector<double>> result(A.size(), vector<double>(A.size()));
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) result[i][j] = A[i][j] + _A[i][j];
	}
	return result;
}

vector<double> operator+(vector<double>& b, vector<double>& _b) {
	vector<double> result(b.size());
	for (int i = 0; i < result.size(); i++) result[i] = b[i] + _b[i];
	return result;
}

vector<vector<double>> operator*(vector<vector<double>>& A, vector<vector<double>>& _A) {
	int n = A.size();
	int m1 = A[0].size();
	int m2 = _A.size();
	int k = _A[0].size();

	if (m1 != m2) {
		cout << "размеры матриц не подходят для умножения" << endl;
		exit(-1); // аварийный выход из программы
	}

	vector<vector<double>> result(n, vector<double>(k, 0));
	for (int i = 0; i < n; i++) {
		for (int t = 0; t < m1; t++)
			for (int j = 0; j < k; j++)
				result[i][j] += A[i][t] * _A[t][j];
	}
	return result;
}

vector<vector<double>> operator*(double& x, vector<vector<double>>& A) {
	vector<vector<double>> result(A.size(), vector<double>(A.size(), 0));
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) result[i][j] = x * A[i][j];
	}
	return result;
}

vector<double> operator*(vector<vector<double>>& A, vector<double>& b) {
	int n = A.size();
	int m1 = A[0].size();
	int m2 = b.size();

	vector<double> result(n, 0);
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < m1; j++) result[i] += A[i][j] * b[j];
	}
	return result;
}

vector<double> PointsX(int n, double a, double b) {
	double random;
	vector<double> x(n, 0);
	for (int i = 0; i < n; i++) {
		random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		x[i] = (b - a) * random + a;
	}

	return x;
}

vector<double> PointsY(vector<double> x, int n, vector<double> omega) {
	double random, d = 0.1;
	vector<double> y(n, 0);
	for (int i = 0; i < n; i++) {
		random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		y[i] = (1 + d * (1 - 2 * random)) * func(x[i], omega);
		y[i] = func(x[i], omega);
	}

	return y;
}

void PrintVector(vector<double> x, int n) {
	for (int i = 0; i < n; i++) cout << x[i] << " ";
	cout << endl;
}

void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите число экспериментальных точек: ";
	int n;
	cin >> n;
	Levenberg_Marquardt lm;
	lm.SetN(n);

	cout << "Введите промежуток:\n";
	double a, b;
	cout << "a - ";
	cin >> a;
	cout << "b - ";
	cin >> b;

	vector<double> omega(r, 1);
	vector<double> omega_init(r, 1);

	cout << "Загадайте вектор параметров (3 элемента): " << endl;
	for (int i = 0; i < r; i++) {
		cout << i << "-ый элемент - ";
		cin >> omega_init[i];
	}
	cout << endl << endl;

	vector<double> x(n, 0);
	x = PointsX(n, a, b);
	lm.SetX(x);
	cout << "Сгенерированный вектор x: ";
	PrintVector(x, n);
	vector<double> y(n, 0);
	y = PointsY(x, n, omega_init);
	cout << "Сгенерированный вектор y: ";
	PrintVector(y, n);
	cout << endl;
	lm.SetY(y);
	cout << endl;

	omega = lm.LevenbergMarquardtMethod(omega);

	cout << "Вычисленный вектор параметров: ";
	PrintVector(omega, r);
	cout << "Загаданный вектор параметров: ";
	PrintVector(omega_init, r);
}