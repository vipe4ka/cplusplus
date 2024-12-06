#pragma once
#include <string>
#include <bitset>
#include <vector>

using namespace std;

class DES {
public:
	DES(string key) {
		bitset<64> sourceKey = TextToBinary(key);
		
		const int PC_1[56] = {
					   57,49,41,33,25,17,9,
					   1,58,50,42,34,26,18,
					   10,2,59,51,43,35,27,
					   19,11,3,60,52,44,36,
					   63,55,47,39,31,23,15,
					   7,62,54,46,38,30,22,
					   14,6,61,53,45,37,29,
					   21,13,5,28,20,12,4
		};
		bitset<56> pc1;
		for (int i = 0; i < pc1.size(); i++)
			pc1[i] = sourceKey[PC_1[i] - 1];
		bitset<pc1.size() / 2> c;
		bitset<pc1.size() / 2> d;
		int p = 0;
		for (int i = 0; i < c.size(); i++) {
			c[i] = pc1[p];
			p++;
		}
		for (int i = 0; i < d.size(); i++) {
			d[i] = pc1[p];
			p++;
		}

		const int shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
		for (int r = 0; r < 16; r++) {
			for (int s = 0; s < shifts[r]; s++) {
				auto cbit = c[0];
				auto dbit = d[0];
				int c0 = cbit, d0 = dbit;
				for (size_t i = 1, j = 1; i < c.size(), j < d.size(); i++, j++) {
					c[i - 1] = c[i];
					d[j - 1] = d[j];
				}
				c[c.size() - 1] = c0;
				d[d.size() - 1] = d0;
			}
			bitset<56> keyShifted;
			p = 0;
			for (int i = 0; i < c.size(); i++) {
				keyShifted[p] = c[i];
				p++;
			}
			for (int i = 0; i < d.size(); i++) {
				keyShifted[p] = d[i];
				p++;
			}

			const int PC_2[48] = {
					   14,17,11,24,1,5,
					   3,28,15,6,21,10,
					   23,19,12,4,26,8,
					   16,7,27,20,13,2,
					   41,52,31,37,47,55,
					   30,40,51,45,33,48,
					   44,49,39,56,34,53,
					   46,42,50,36,29,32
			};
			bitset<48> keyset;
			for (int j = 0; j < keyset.size(); j++)
				keyset[j] = keyShifted[PC_2[j] - 1];
			keys.push_back(keyset);
		}	
	}
	void SetText(string text);
	string GetText();
private:
	vector<bitset<48>> keys;
	bitset<64> text;

	bitset<64> TextToBinary(string& source);
	void FeistelCipher();
};