#include <cstdio>
#include <cmath>

const int		n = 10, 
				kmax = 4;

const double    h = 0.1;

double func(double x, double y) {
	return x * x - 2 * y;
}

double analytic(double x) {
	return (0.75 / exp(2.0 * x)) + ((x * x) / 2.0) - (x / 2.0) + 0.25;
}

void main() {
	double x = 0, y = 1;

	for (int i = 0; i < n; i++) {
		double yk = y;
		for (int k = 0; k < kmax; k++) {
			if (k == 0) yk = y + h * func(x, y);
			else yk = y + (h / 2.0) * (func(x, y) + func(x + h, yk));
		}
		y = yk;
		x += h;
		printf("%f %f %f\n", x, y, analytic(x));
	}
}