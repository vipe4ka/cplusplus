#include "Levenberg_Marquardt.h"
#include "lup.h"
#include <iostream>

using namespace std;

void Levenberg_Marquardt::SetN(int _n) {
	n = _n;
}

double Levenberg_Marquardt::funcD(double x, vector<double> omega, int i) {
	if (i == 0) return sin(omega[1] * x + omega[2]);
	if (i == 1) return omega[0] * cos(omega[1] * x + omega[2]) * x;
	if (i == 2) return omega[0] * cos(omega[1] * x + omega[2]);
}

void Levenberg_Marquardt::SetX(vector<double> _x) {
	x = _x;
}

void Levenberg_Marquardt::SetY(vector<double> _y) {
	y = _y;
}

vector<double> Levenberg_Marquardt::LevenbergMarquardtMethod(vector<double>& omega) {
	vector<double> f(n, 0); //вектор невязок
	double e, e_new; // отклонение
	double mu = 0.01;
	vector<vector<double>> J(n, vector<double>(r, 0));
	double t;
	vector<vector<double>> JT(r, vector<double>(n, 0));
	vector<vector<double>> H(r, vector<double>(r, 0));

	vector<vector<double>> I(r, vector<double>(r, 0));
	for (int i = 0; i < r; i++) I[i][i] = 1;

	vector<double> omega_new(omega.size(), 0);

	vector<double> b(r, 0);
	vector<double> p(r, 0);
	lup lup;

	lup.SetVectorX(p);
	vector<double> p1(r, 0);
	lup.SetVectorP(p1);

	for (int k = 0; k < kmax; k++) {
		for (int i = 0; i < n; i++)
			f[i] = funcD(x[i], omega) - y[i];

		e = 0;
		for (int i = 0; i < n; i++)
			e += pow(f[i], 2);

		for (int m = 1;; m++) {

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < r; j++) {
					J[i][j] = funcD(x[i], omega, j);
				}
			}

			for (int i = 0; i < r; i++)
				for (int j = 0; j < n; j++)
					JT[i][j] = J[j][i];

			H = JT * J + mu * I;
			lup.SetMatrixA(H);

			double minus = -1.0;
			b = (minus * J) * f;
			lup.SetVectorB(b);

			if (lup.LUP() == false) {
				cout << "Ошибка нахождения сдвига.\n";
				for (int i = 0; i < p.size(); i++) p[i] = 0;
			}
			else {
				lup.LinearSystemSolution();
				p = lup.GetVectorX();
			}

			omega_new = omega + p;

			for (int i = 0; i < n; i++)
				f[i] = funcD(x[i], omega_new) - y[i];

			e_new = 0;
			for (int i = 0; i < n; i++)
				e_new += pow(f[i], 2);

			if (e_new > e) {
				mu *= 10.0;
				if (m > 5) {
					omega = omega_new;
					break;
				}
				else continue;
			}
			else {
				mu /= 10.0;
				omega = omega_new;
				break;
			}
			if (e_new <= emax) break;
		}
		if (e_new <= emax) break;
	}

	return omega;
}