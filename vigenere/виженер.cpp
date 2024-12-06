#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

vector<string> InitCryptoTable(string key) {
    int shift;
    vector<string> table;
    for (int i = 0; i < key.size(); i++) {
        string temp;
        shift = alphabet.find(key[i]);
        for (int j = shift; j < alphabet.size(); j++) temp.push_back(alphabet[j]);
        for (int j = 0; j < shift; j++) temp.push_back(alphabet[j]);
        table.push_back(temp);
    }

    return table;
}

void main() {
    ifstream textFile;
    stringstream buffer;
    textFile.open("plaintext.txt");
    if (textFile.is_open()) buffer << textFile.rdbuf();
    textFile.close();
    string text = buffer.str();
    cout << "plain text has been read from \"plaintext.txt\":" << endl;
    cout << text << endl;
    cout << "enter keyword: ";
    string key; getline(cin, key);

    vector<string> cryptoTable = InitCryptoTable(key);

    string encryptText;
    int i = 0;
    for (auto& c : text) {
        if (alphabet.find(c) == string::npos) {
            encryptText += c;
            continue;
        }
        else encryptText.push_back(cryptoTable[i][alphabet.find(c)]);
        i++;
        if (i == key.size()) i = 0;
    }
    cout << "encrypted text:\n" << encryptText << endl;

    ofstream fileCrypt;
    fileCrypt.open("result.txt");
    if (fileCrypt.is_open()) fileCrypt << encryptText << endl;
    cout << "text has been saved in \"result.txt\"" << endl;
}