#include <vector>
#include <ostream>
#include <iostream>
#include "Matrix.h"

using namespace std;

const double step = 0.1,
			 epsilon = 0.0001;

const int	 maxIter = 100,
			 n = 10;

double FormVectorF(int i, vector<double> x) {
	if (i == 0) return (3 + 2 * x[i]) * x[i] - 2 * x[i + 1] - 3;
	if (i == n - 1) return (3 + 2 * x[i]) * x[i] - x[i - 1] - 4;
	else return (3 + 2 * x[i]) * x[i] - x[i - 1] - 2 * x[i + 1] - 2;
}

void main() {
	vector<double> x(n, 0);

	for (int k = 0; k < maxIter; k++) {
		vector<vector<double>> J =
		{
			{4 * x[0] + 3, -2, 0, 0, 0, 0, 0, 0, 0, 0 },
			{-1, 4 * x[1] + 3, -2, 0, 0, 0, 0, 0, 0, 0 },
			{0, -1, 4 * x[2] + 3, -2, 0, 0, 0, 0, 0, 0 },
			{0, 0, -1, 4 * x[3] + 3, -2, 0, 0, 0, 0, 0 },
			{0, 0, 0, -1, 4 * x[4] + 3, -2, 0, 0, 0, 0 },
			{0, 0, 0, 0, -1, 4 * x[5] + 3, -2, 0, 0, 0 },
			{0, 0, 0, 0, 0, -1, 4 * x[6] + 3, -2, 0, 0 },
			{0, 0, 0, 0, 0, 0, -1, 4 * x[7] + 3, -2, 0 },
			{0, 0, 0, 0, 0, 0, 0, -1, 4 * x[8] + 3, -2 },
			{0, 0, 0, 0, 0, 0, 0, 0, -1, 4 * x[9] + 3 }
		};

		vector<double> f(n);
		
		for (int i = 0; i < n; i++) {
			f[i] = FormVectorF(i, x);
		}

		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (fabs(f[i]) > epsilon) {
				flag = false;
			}
		}
		if (flag) break;

		Matrix ma;
		ma.SetA(J);
		ma.SetVectorB(f);
		vector<double> p(n, 0);
		ma.GetP(p);

		for (int i = 0; i < n; i++) x[i] -= step * p[i];
	}

	copy(x.begin(), x.end(), ostream_iterator<double>(cout, " "));
}
