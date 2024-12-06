#include "lup.h"
#include "iostream"
#include "iomanip"

void lup::SetMatrixA(vector<vector<double>> A_) {
	A = A_;
}

void lup::SetVectorB(vector<double> b_) {
	b = b_;
}

void lup::Swap(double& n1, double& n2) {
	double t = n1;
	n1 = n2;
	n2 = t;
}

void lup::SetVectorP(vector<double> _p) {
	p = _p;
}

bool lup::LUP() {
	p.resize(A.size()); // перестраховываемся
	for (int i = 0; i < p.size(); i++) p[i] = i;
	double p1;
	int k1;

	for (int k = 0; k < p.size(); k++) {
		p1 = 0;
		k1 = k;
		for (int i = k; i < p.size(); i++) {
			if (fabs(A[i][k]) > p1) {
				p1 = fabs(A[i][k]);
				k1 = i;
			}
		}
		if (p1 == 0) return false;
		Swap(p[k], p[k1]);
		for (int i = 0; i < A.size(); i++)
			Swap(A[k][i], A[k1][i]);
		for (int i = k + 1; i < A.size(); i++) {
			A[i][k] /= A[k][k];
			for (int j = k + 1; j < A.size(); j++)
				A[i][j] -= A[i][k] * A[k][j];
		}
	}

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

	return true;
}

void lup::SetVectorX(vector<double> _x) {
	x = _x;
}

void lup::LinearSystemSolution() {
	vector<double> b1(p.size(), 0);
	for (int i = 0; i < b1.size(); i++) {
		b1[i] = b[p[i]];
	}
	b = b1;
	b1.clear();
	b1.shrink_to_fit();
	p.clear();
	p.shrink_to_fit();

	double sum;

	vector<double> y(b.size(), 0);

	for (int k = 0; k < y.size(); k++) {
		sum = 0;
		for (int j = 0; j <= k - 1; j++) sum += L[k][j] * y[j];
		y[k] = b[k] - sum;
	}

	for (int k = x.size() - 1; k >= 0; k--) {
		sum = 0;
		for (int j = k + 1; j < x.size(); j++) sum += U[k][j] * x[j];
		x[k] = (y[k] - sum) / U[k][k];
	}
}

vector<double> lup::GetVectorX() {
	return x;
}