#include <iostream>
#include <vector>

using namespace std;

int n, num = 1;
vector<int> arr;

void Swap(int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//возьмем две перестановки. если их первые несколько элементов равны, а следующий после равных у первой перестановки меньше, чем у второй, то первая лексигографически меньше
bool Lex() {
    int pi = n - 2;
    while (pi != -1 && arr[pi] >= arr[pi + 1]) pi--; //ищем позицию pi
    if (pi == -1)
        return false; //если не нашли, то больше перестановок нет, т.к. весь массив в самом конце отсортирован по убыванию
    int pj = n - 1;
    while (arr[pi] >= arr[pj]) pj--; //ищем позицию pj
    Swap(pi, pj); //меняем местами
    int l = pi + 1, r = n - 1; // сортируем хвостик последовательности по убыванию
    while (l < r)
        Swap(l++, r--);
    return true;
}

void main() {
    cout << "n: "; //количество элементов в массиве
    cin >> n;
    cout << endl;
    for (int i = 0; i < n; i++) arr.push_back(i + 1);
    cout << num++ << ": "; //выводим начальный массив
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    while (Lex()) { //выводим перестановки, пока есть уникальные
        cout << num++ << ": ";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
}