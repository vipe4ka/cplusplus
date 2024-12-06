#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include "DES.h"

using namespace std;

string ReadFile(string filename) {
    stringstream buffer;
    ifstream file;
    file.open(filename);
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "text has been read from text.txt" << endl;
    cout << "key has been read from key.txt" << endl;
    string text = ReadFile("text.txt");
    string key = ReadFile("key.txt");

    DES des(key);
    string block = "", ciphertext = "";
    int k = 0;
    for (auto& c : text) {
        block += c;
        k++;
        if (k == 8) {
            des.SetText(block);
            ciphertext += des.GetText();
            k = 0;
            block.clear();
        }
    }
    if (!block.empty()) {
        while (block.size() != 8)
            block.insert(block.begin(), '0');
        des.SetText(block);
        ciphertext += des.GetText();
    }
    
    cout << "\n\nresult:\n" << ciphertext << endl;
    ofstream file;
    file.open("result.txt");
    file << ciphertext;
    cout << "\nciphertext has been saved in result.txt" << endl;
}