#include <fstream>
#include <random>

using namespace std;

int n = 250000;

void main() {
	ofstream file;
	file.open("numbers.txt");
	for (int i = 0; i < n; i++) file << rand() << endl;
}