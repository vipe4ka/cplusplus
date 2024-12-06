#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <chrono>

using namespace std;

vector<int> createOffsetTable(const string& pattern) {
    int patternLength = pattern.length();
    vector<int> offsetTable(256, patternLength); // Заполняем таблицу смещений значением patternLength

    for (int i = 0; i < patternLength - 1; ++i) {
        offsetTable[pattern[i]] = patternLength - i - 1;
    }

    return offsetTable;
}

int BoyerMooreSearch(const string& text, const string& key) {
    int n = text.length();
    int m = key.length();
    vector<int> offsetTable = createOffsetTable(key); // Создаем таблицу смещений

    int i = m - 1;
    int steps = 0;
    while (i < n) {
        int j = m - 1;

        while (j >= 0 && text[i] == key[j]) { // Проверяем символы справа налево
            --i;
            --j;
        }

        if (j == -1) { // Найдено совпадение
            cout << "\nШаги: " << steps << endl;
            return i + 1;
        }

        i += max(offsetTable[text[i]], m - j); // Выполняем смещение
        steps++;
    }

    cout << "\nШаги: " << steps << endl;
    return -1; // Совпадение не найдено
}

int main() {
    setlocale(LC_ALL, "Russian");

    stringstream buffer;
    ifstream file;
    file.open("text.txt");
    if (file) {
        buffer << file.rdbuf();
        file.close();
    }
    file.close();
    string text = buffer.str();
    cout << text << endl << endl << "Enter key for search: ";
    string key; getline(cin, key);

    auto timeStart = chrono::steady_clock::now();
    int result = BoyerMooreSearch(text, key);

    if (result == -1) {
        cout << "Совпадение не найдено" << endl;
    }
    else {
        cout << "Совпадение найдено в позиции " << result << endl;
    }
    auto timeEnd = chrono::steady_clock::now();

    cout << "Время выполнения: " << chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart).count() << " мс" << endl;

    return 0;
}