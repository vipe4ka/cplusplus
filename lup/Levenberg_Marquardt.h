#pragma once
#include <vector>

using namespace std;

vector<vector<double>> operator+ (vector<vector<double>>& A, vector<vector<double>>& _A);

class Levenberg_Marquardt {
public:
	friend double func(double x, vector<double> omega);
	void SetN(int _n);

	void SetX(vector<double> _x);
	void SetY(vector<double> _y);

	//friend vector<vector<double>> operator+ (vector<vector<double>> &A, vector<vector<double>> &_A);
	friend vector<double> operator+ (vector<double>& b, vector<double>& _b);
	friend vector<vector<double>> operator* (vector<vector<double>>& A, vector<vector<double>>& _A);
	friend vector<vector<double>> operator* (double& x, vector<vector<double>>& A);
	friend vector<double> operator* (vector<vector<double>>& A, vector<double>& b);

	vector<double> LevenbergMarquardtMethod(vector<double>& omega);

private:
	const int r = 3, kmax = 1000;
	const double emax = 0.001;
	int n;
	vector<double> x;
	vector<double> y;

	double funcD(double x, vector<double> omega, int i);
};

