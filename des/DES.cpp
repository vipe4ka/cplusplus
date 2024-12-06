#include "DES.h"

void DES::SetText(string text) {
	const int IP[64] = {
					 58,50,42,34,26,18,10,2,
					 60,52,44,36,28,20,12,4,
					 62,54,46,38,30,22,14,6,
					 64,56,48,40,32,24,16,8,
					 57,49,41,33,25,17, 9,1,
					 59,51,43,35,27,19,11,3,
					 61,53,45,37,29,21,13,5,
					 63,55,47,39,31,23,15,7
	};

	bitset<64> sourceText = TextToBinary(text);

	for (int i = 0; i < sourceText.size(); i++)
		this->text[i] = sourceText[IP[i] - 1];
}

bitset<64> DES::TextToBinary(string& source) {
	string str = source;
	source.resize(str.size() * 2);
	const size_t a = 'a' - 1;
	for (size_t i = 0, c = str[0] & 0xFF; i < source.size(); c = str[i / 2] & 0xFF)
	{
		source[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
		source[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0';
	}
	
	bitset<64> result;
	int k = 0;
	for (int i = 0; i < source.size(); i++) {
		switch (source[i]) {
		case '0':
			str = "0000";
			break;
		case '1':
			str = "0001";
			break;
		case '2':
			str = "0010";
			break;
		case '3':
			str = "0011";
			break;
		case '4':
			str = "0100";
			break;
		case '5':
			str = "0101";
			break;
		case '6':
			str = "0110";
			break;
		case '7':
			str = "0111";
			break;
		case '8':
			str = "1000";
			break;
		case '9':
			str = "1001";
			break;
		case 'a':
			str = "1010";
			break;
		case 'b':
			str = "1011";
			break;
		case 'c':
			str = "1100";
			break;
		case 'd':
			str = "1101";
			break;
		case 'e':
			str = "1110";
			break;
		case 'f':
			str = "1111";
			break;
		}
		bitset<4> c(str);
		for (int j = c.size() - 1; j >= 0; j--) {
			result[k] = c[j];
			k++;
		}
	}

	return result;
}

void DES::FeistelCipher() {
	const int SBOX_1[4][16] = { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
						   {0,15,7,4,15,2,13,1,10,6,12,11,9,5,3,8},
						   {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
						   {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} };

	const int SBOX_2[4][16] = { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
							   {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
							   {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
							   {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} };

	const int SBOX_3[4][16] = { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
							   {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
							   {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
							   {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} };

	const int SBOX_4[4][16] = { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
							   {12,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
							   {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
							   {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} };

	const int SBOX_5[4][16] = { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
							   {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
							   {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
							   {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} };

	const int SBOX_6[4][16] = { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
							   {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
							   {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
							   {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} };

	const int SBOX_7[4][16] = { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
							   {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
							   {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
							   {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} };

	const int SBOX_8[4][16] = { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
							   {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
							   {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
							   {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} };

	typedef const int(*SBOX)[16];
	SBOX SBox[8] = { SBOX_1, SBOX_2, SBOX_3, SBOX_4, SBOX_5, SBOX_6, SBOX_7, SBOX_8 };

	const int E[48] = { 32,1,2,3,4,5,
						4,5,6,7,8,9,
						8,9,10,11,12,13,
						12,13,14,15,16,17,
						16,17,18,19,20,21,
						20,21,22,23,24,25,
						24,25,26,27,28,29,
						28,29,30,31,32,1 };

	for (int r = 0; r < 16; r++) {
		bitset<32> L, R;
		int k = 0;
		for (int i = 0; i < L.size(); i++) {
			L[i] = text[k];
			k++;
		}
		for (int i = 0; i < R.size(); i++) {
			R[i] = text[k];
			k++;
		}

		bitset<48> RE;
		for (int i = 0; i < RE.size(); i++)
			RE[i] = R[E[i] - 1] xor keys[r][i];
		
		vector<bitset<6>> S;
		k = 0;
		for (int s = 0; s < 8; s++) {
			bitset<6> sbox;
			for (int i = 0; i < sbox.size(); i++) {
				sbox[i] = RE[k];
				k++;
			}
			S.push_back(sbox);
		}

		int sbox[8];
		for (int i = 0; i < S.size(); i++) {
			bitset<2> rowB;
			rowB[1] = S[i][0]; rowB[0] = S[i][5];
			int row = rowB.to_ulong();
			bitset<4> colB;
			colB[3] = S[i][1]; colB[2] = S[i][2]; colB[1] = S[i][3]; colB[0] = S[i][4];
			int col = colB.to_ulong();
			sbox[i] = SBox[i][row][col];
		}

		bitset<32> resS;
		k = 0;
		for (int i = 0; i < 8; i++) {
			bitset<4> c = sbox[i];
			for (int j = c.size() - 1; j >= 0; j--) {
				resS[k] = c[j];
				k++;
			}
		}

		const int Ft[32] = {
							  16,7,20,21,
							  29,12,28,17,
							  1,15,23,26,
							  5,18,31,10,
							  2,8,24,14,
							  32,27,3,9,
							  19,13,30,6,
							  22,11,4,25
		};
		bitset<32> F;
		for (int i = 0; i < F.size(); i++)
			F[i] = resS[Ft[i] - 1] xor L[i];

		k = 0;
		for (int i = 0; i < R.size(); i++) {
			text[k] = R[i];
			k++;
		}
		for (int i = 0; i < F.size(); i++) {
			text[k] = F[i];
			k++;
		}

	}
}

string DES::GetText() {
	FeistelCipher();

	bitset<32> L, R;
	int k = 0;
	for (int i = 0; i < L.size(); i++) {
		L[i] = text[k];
		k++;
	}
	for (int i = 0; i < R.size(); i++) {
		R[i] = text[k];
		k++;
	}
	k = 0;
	for (int i = 0; i < R.size(); i++) {
		text[k] = R[i];
		k++;
	}
	for (int i = 0; i < L.size(); i++) {
		text[k] = L[i];
		k++;
	}

	const int IP_1[64] = {
					   40,8,48,16,56,24,64,32,
					   39,7,47,15,55,23,63,31,
					   38,6,46,14,54,22,62,30,
					   37,5,45,13,53,21,61,29,
					   36,4,44,12,52,20,60,28,
					   35,3,43,11,51,19,59,27,
					   34,2,42,10,50,18,58,26,
					   33,1,41,9,49,17,57,25
	};
	bitset<64> result;
	for (int i = 0; i < result.size(); i++)
		result[i] = text[IP_1[i] - 1];

	string bits, hex = "";
	k = 0;
	for (int i = 0; i < result.size(); i++) {
		if (result.test(i)) bits += "1";
		else bits += "0";
		k++;
		if (k == 4) {
			if (bits == "0000") hex += "0";
			if (bits == "0001") hex += "1";
			if (bits == "0010") hex += "2";
			if (bits == "0011") hex += "3";
			if (bits == "0100") hex += "4";
			if (bits == "0101") hex += "5";
			if (bits == "0110") hex += "6";
			if (bits == "0111") hex += "7";
			if (bits == "1000") hex += "8";
			if (bits == "1001") hex += "9";
			if (bits == "1010") hex += "a";
			if (bits == "1011") hex += "b";
			if (bits == "1100") hex += "c";
			if (bits == "1101") hex += "d";
			if (bits == "1110") hex += "e";
			if (bits == "1111") hex += "f";

			k = 0; bits = "";
		}		
	}

	string ciphertext = hex;
	ciphertext.resize((hex.size() + 1) / 2);

	for (size_t i = 0, j = 0; i < ciphertext.size(); i++, j++)
	{
		ciphertext[i] = (hex[j] & '@' ? hex[j] + 9 : hex[j]) << 4, j++;
		ciphertext[i] |= (hex[j] & '@' ? hex[j] + 9 : hex[j]) & 0xF;
	}

	return ciphertext;
}