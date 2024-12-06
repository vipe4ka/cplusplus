#include "matrix_algebra.h"
#include <iostream>
#include <iomanip>

//находим х из уравнения Ax = b

void matrix_algebra::SetMatrixA(vector<vector<double>> A_) { //суем в класс матрицу А
	A = A_;
}

void matrix_algebra::SetVectorB(vector<double> b_) { //суем в класс вектор b
	b = b_;
}

void matrix_algebra::PrintMatrixA() { //вывод матрицы А из класса в консоль
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++)
			cout << setw(15) << A[i][j];
		cout << endl;
	}
	cout << endl << endl;
}

void matrix_algebra::PrintVectorB() { //вывод вектора b из класса в консоль
	for (int i = 0; i < b.size(); i++) cout << b[i] << " ";
	cout << endl << endl;
}

void matrix_algebra::SetVectorP(vector<double> _p) { //суем в класс вектор p (в main() объяви нулевой вектор p нужного размера и запихни в класс)
	p = _p;
}

bool matrix_algebra::LUP() { //процесс LUP-разложения. функция булевая, поэтому в случае вырожденной матрицы вернет false, и дальнейшая реализация алгоритма прекратится
	//в main() напиши типа if (имя_переменной_класса.LUP() == false) return;
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
		if (p1 == 0) return false; //здеся вернет false
		swap(p[k], p[k1]);
		for (int i = 0; i < A.size(); i++)
			swap(A[k][i], A[k1][i]);
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

void matrix_algebra::SetVectorX(vector<double> _x) {
	x = _x;
}

void matrix_algebra::LinearSystemSolution() {
	vector<double> b1(p.size(), 0);
	for (int i = 0; i < b1.size(); i++) {
		b1[i] = b[p[i]];
	} //смысл LUP-разложения состоит в том, что в векторе b члены меняются местами согласно получившемуся вектору p.
	//допустим, n = 4, а вектор p у нас получился типа {1, 2, 0, 3}. тогда 0-ой член вектора b будет стоять на 3 месте, 1-ый на 0-ом месте и так далее
	b = b1;
	b1.clear(); //освобождение памяти от векторов b1 и p
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

void matrix_algebra::PrintSolution() { //вывод решения системы уравнений в консоль
	cout << "Решение СЛАУ: ";
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl << endl;
}


//если ты будешь работать в main() с решением системы уравнений, то напиши что-то типа такой функции
//и обязательно дай определение этой функции в matrix_algebra.h
/*
vector<double> matrix_algebra::GetX() {
	return x;
}
*/
//в main() создай переменную типа vector<double> x = имя_переменной_класса.GetX();