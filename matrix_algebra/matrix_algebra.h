#pragma once
#include <vector>

using namespace std;

class matrix_algebra {
public:

	void SetMatrixA(vector<vector<double>> A_);
	void SetVectorB(vector<double> b_);

	void PrintMatrixA();
	void PrintVectorB();

	void SetVectorP(vector<double> _p);
	bool LUP();

	void SetVectorX(vector<double> _x);
	void LinearSystemSolution();
	void PrintSolution();

private:
	vector<vector<double>> A;
	vector<double> b;
	vector<vector<double>> L;
	vector<vector<double>> U;
	vector<double> p;

	vector<double> x;
};