#include <iostream>
#include <Windows.h>
#include <any>
#include <cmath>
#include <string>

#define MAX 255

using namespace std;

any InputFactor() {
	char input[MAX];
	cin >> input;
	char* cp = input;
	for (int i = 0; cp[i]; i++)
		if (cp[i] == '.') {
			double factor = stof(input);
			return factor;
		}
	int factor = stoi(input);
	return factor;
}

double FormFactor(any& input) {
	auto& t = input.type();
	if (t == typeid(double)) {
		double factor = any_cast<double>(input);
		return factor;
	}
	if (t == typeid(int)) {
		double factor = any_cast<int>(input);
		return factor;
	}
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	cout << "Квадратное уравнение: Ax^2 + Bx + C = 0" << endl;
	cout << "Введите коэффициенты: \nA - ";
	any aInput = InputFactor();
	cout << "B - ";
	any bInput = InputFactor();
	cout << "C - ";
	any cInput = InputFactor();
	
	double A = FormFactor(aInput),
		   B = FormFactor(bInput),
		   C = FormFactor(cInput);

	cout << "\nВведенное уравнение: (" << A << ")x^2 + (" << B << ")x + (" << C << ") = 0" << endl;

	if (A == 0) {
		cout << "\nУравнение не является квадратным.\n";
		cout << "x = " << -C / B;
		return;
	}

	double D = pow(B, 2.0) - 4.0 * A * C;
	if (D < 0) {
		cout << "\nУравнение имеет комплексное решение:\n";
		D = fabs(D);
		cout << "x1 = " << -B / 2 * A << " + " << sqrt(D) / 2.0 * A << "i\n";
		cout << "x2 = " << -B / 2 * A << " - " << sqrt(D) / 2.0 * A << "i\n";
	}
	else if (D == 0) {
		cout << "\nУравнение имеет единственное решение:\n";
		cout << "x = " << -B / 2.0 * A;
	}
	else {
		cout << "\nРешения:\n";
		cout << "x1 = " << ( -B + sqrt(D)) / 2.0 * A << endl;
		cout << "x2 = " << ( -B - sqrt(D)) / 2.0 * A << endl;
	}
}