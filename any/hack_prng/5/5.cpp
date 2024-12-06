#include <iostream>

using namespace std;



void main(int argv, char argc[]) {
    setlocale(LC_ALL, "Russian");
    if (argv == 0) {
        cout << "Вы ввели недостаточно параметров." << endl;
        return;
    }

    int num = argc[1], in = argc[2], out = argc[3];
    
}
