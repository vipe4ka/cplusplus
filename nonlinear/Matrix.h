#pragma once
#include <vector>

using namespace std;

class Matrix {
public:
	void SetA(vector<vector<double>> _A);
	void SetVectorB(vector<double> _b);
	void GetP(vector<double>& _x);

private:
	vector<double> LinearSystemSolution();
	vector<vector<double>> A;
	vector<double> b;
	vector<vector<double>> L = A;
	vector<vector<double>> U = A;

};