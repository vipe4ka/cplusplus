#include <iostream>
#include <vector>

using namespace std;

void GrayCodesRecursion(int n, std::vector<string>& result) {
    if (n == 1) {
        result.push_back("0");
        result.push_back("1");
    }
    else {
        GrayCodesRecursion(n - 1, result);
        int size = result.size();
        for (int i = size - 1; i >= 0; i--) {
            result.push_back(result[i]);
        }
        for (int i = 0; i < size; i++) {
            result[i] = "0" + result[i];
        }
        for (int i = size; i < 2 * size; i++) {
            result[i] = "1" + result[i];
        }
    }
}

vector<string> InitCodes(int n) {
    vector<string> result;
    GrayCodesRecursion(n, result);
    return result;
}

void main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество битов: ";
    cin >> n;

    vector<string> grayCodes = InitCodes(n);

    cout << "Коды Грея для " << n << " битов:" << endl;
    for (int i = 0; i < grayCodes.size(); i++)
        cout << grayCodes[i] << " (" << i + 1 << ")" << endl;

}