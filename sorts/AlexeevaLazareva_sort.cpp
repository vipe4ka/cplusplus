#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include "SortClass.h"

using namespace std;

void main() {
    setlocale(LC_ALL, "Russian");
    SortClass mysort;
    ofstream file;
    while (1) {
        system("cls");
        cout << "1. Создать массив\n2. Вывести массив\n3. Сортировка выбором" << endl;
        cout << "4. Сортировка методом Шелла\n5. Быстрая сортировка\n6. Сортировка подсчетом" << endl; 
        cout << "7. Интерполяционный поиск\n8. Бинарный следящий поиск\n\nНажмите 0, чтобы выйти...\n\n";
        int choice, k;
        cin >> choice;
        cout << endl;
        if (choice == 0) break;
        switch (choice) {
        case 1:
            system("cls");
            cout << "Введите размер массива: ";
            mysort.SetSize();
            cout << "Введите диапазон массива:\nминимум - ";
            int min; cin >> min;
            cout << "максимум - ";
            int max; cin >> max;
            mysort.CreateStartMass(min, max);
            break;
        case 2:
            system("cls");
            file.open("sorted.txt");
            k = 0;
            for (int i = 0; i < mysort.GetSize(); i++) {
                file << mysort.GetPos(i) << " ";
                k++;
                if (k == 40) {
                    file << endl;
                    k = 0;
                }
            }
            file.close();
            cout << "Массив выведен в файл \"sorted.txt\". Нажмите любую клавишу...";
            _getch();
            break;
        case 3:
            mysort.SelectionSort();
            break;
        case 4:
            mysort.ShellSort();
            break;
        case 5:
            mysort.QuickSort(0, mysort.GetSize());
            break;
        case 6:
            mysort.CountingSort();
            break;
        case 7:
            system("cls");
            mysort.IntepolSearch();
            break;
        case 8:
            system("cls");
            std::cout << "Введите значение элемента: ";
            int key;
            std::cin >> key;
            mysort.FollowBinarySearch(key, 0, mysort.GetSize());
            break;
        default:
            cout << "\nВведен неверный пункт меню";
            Sleep(2000);
        }
    }
}