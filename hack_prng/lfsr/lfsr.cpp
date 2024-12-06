#include <random>
#include <fstream>

using namespace std;

int main() {
	unsigned int R1 = rand(), R2 = rand(), R3 = rand(), R4 = rand(), number, temp1, temp2;
	int c;
	ofstream file;
	file.open("numbers.txt");
	for (int i = 0; i < 100000; i++) {
		temp1 = R2 ^ (R3 << 31) ^ (R4 >> 1);
		R4 = R3;
		R3 = R2;
		R2 = R1;
		temp1 = (R4 | 0x1) + R1;
		c = (temp1 < R1);
		temp2 = (temp1 << 16) ^ (temp1 >> 16);
		if (c) temp1 = (R2 ^ (R4 | 0x1)) + temp2;
		else temp1 = R2 + temp2;
		c = (temp1 < temp2);
		number = c + (R3 ^ R2) + temp1;
		file << number << endl;
		R1 = number;
	}
}