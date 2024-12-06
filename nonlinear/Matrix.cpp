#include "Matrix.h"
#include <algorithm>
#include <iostream>

void Matrix::SetA(vector<vector<double>> _A) {
	A = _A;
}

void Matrix::SetVectorB(vector<double> _b) {
	b = _b;
}

void Matrix::GetP(vector<double>& _x) {
	vector<double> x = LinearSystemSolution();
	_x = x;
}

vector<double> Matrix::LinearSystemSolution() {
	L = A;
	for (int i = 0; i < L.size(); i++) {
		for (int j = 0; j < L[i].size(); j++) {
			if (i < j) L[i][j] = 0;
			if (i == j) L[i][j] = 1;
		}
	}

	U = A;
	for (int i = 0; i < U.size(); i++) {
		for (int j = 0; j < U[i].size(); j++) {
			if (i > j && i != j) U[i][j] = 0;
		}
	}

	vector<double> y(b.size(), 0);
	for (int k1 = 0; k1 < y.size(); k1++) {
		double sum = 0;
		for (int j = 0; j <= k1 - 1; j++) sum += L[k1][j] * y[j];
		y[k1] = b[k1] - sum;
	}
	vector<double> x(y.size(), 0);
	for (int k1 = x.size() - 1; k1 >= 0; k1--) {
		double sum = 0;
		for (int j = k1 + 1; j < x.size(); j++) sum += U[k1][j] * x[j];
		if (U[k1][k1] == 0) {
			x[k1] = 0;
			continue;
		}
		x[k1] = (y[k1] - sum) / U[k1][k1];
	}

	return x;
}