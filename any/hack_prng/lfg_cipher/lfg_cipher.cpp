#include <fstream>
#include <random>
#include <vector>
#include <bitset>

using namespace std;

unsigned int firstIndex = 12, //i - 5
secondIndex = 0, //i - 17
k = 17; //размер буфера (больший лаг)

unsigned long long int m = pow(2, 32);

vector<unsigned long long int> CreateBuffer() {
	vector<unsigned long long int> buffer;
	for (int i = 0; i < k; i++) buffer.push_back(rand());
	return buffer;
}

void main() {
	ofstream file;
	vector<unsigned long long int> buffer = CreateBuffer();
	vector<unsigned long long int> G(k);
	for (int i = 0; i < buffer.size(); i++)
		G[i] = buffer[buffer.size() - 1 - i];
	
	file.open("numbers.txt");
	for (int i = 0; i < 10000; i++) {
		unsigned long long int mu = buffer[buffer.size() - 1] >> 28;
		unsigned long long int M = G[(5 + mu) % 16];
		unsigned long long int L = buffer[secondIndex];
		L = ((L & 0x00ff) << 8) | ((L & 0xff00) >> 8);
		unsigned long long int value = (M + L) % m;
		buffer.erase(buffer.begin());
		buffer.push_back(value);
		//G.erase(buffer.end());
		//G.insert(G.begin(), value);
		file << value << endl;
	}
	file.close();
}