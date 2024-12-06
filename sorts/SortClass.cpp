#include <iostream>
#include <conio.h>
#include <random>
#include "SortClass.h"

void SortClass::SetSize() {
    n = NULL;
    std::cin >> n;
    delete[] mass;
    delete[] startMass;
}

int SortClass::GetSize() {
    return n;
}

void SortClass::CreateStartMass(int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<int> randomize(min, max);
    startMass = new int[n];
    for (int i = 0; i < n; i++)
        startMass[i] = randomize(mersenne);
}

void SortClass::CreateMass() {
    mass = new int[n];
    for (int i = 0; i < n; i++) mass[i] = startMass[i];
}

int SortClass::GetPos(int i) {
    if (mass) return mass[i];
    else return startMass[i];
}

void SortClass::SelectionSort() {
    CreateMass();
    auto timeStart = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        int m = i;
        for (int j = i + 1; j < n; ++j)
            if (mass[m] > mass[j]) m = j;
        std::swap(mass[m], mass[i]);
    }
    auto timeEnd = std::chrono::steady_clock::now();
    Check(timeStart, timeEnd);
}

void SortClass::ShellSort() {
    CreateMass();
    auto timeStart = std::chrono::steady_clock::now();
    int d = n / 2, j;
    while (d > 0) {
        for (int i = 0; i < n - d; i++) {
            j = i;
            while (j >= 0 && mass[j] > mass[j + d]) {
                std::swap(mass[j], mass[j + d]);
                j--;
            }
        }
        d /= 2;
    }
    auto timeEnd = std::chrono::steady_clock::now();
    Check(timeStart, timeEnd);
}

void SortClass::QuickSort(int left, int right) {
    CreateMass();
    auto timeStart = std::chrono::steady_clock::now();
    QuickSortRecursion(left, right);
    auto timeEnd = std::chrono::steady_clock::now();
    Check(timeStart, timeEnd);
}

void SortClass::QuickSortRecursion(int left, int right) {
    if (left >= right) return;
    int supElement = mass[left], tleft = left, tright = right - 1;
    while (tleft <= tright) {
        while (mass[tleft] < supElement) ++tleft;
        while (mass[tright] > supElement) --tright;
        if (tleft <= tright) {
            std::swap(mass[tleft], mass[tright]);
            ++tleft;
            --tright;
        }
    }
    QuickSortRecursion(left, tright + 1);
    QuickSortRecursion(tleft, right);
}


void SortClass::CountingSort() {
    CreateMass();
    int max = 0;
    for (int i = 0; i < n; i++)
        if (mass[i] > max) max = mass[i];
    auto timeStart = std::chrono::steady_clock::now();
    int* countMass = new int[max + 1];
    for (int i = 0; i < max + 1; i++) countMass[i] = 0;
    for (int i = 0; i < n; i++) countMass[mass[i]]++;
    int j = 0;
    for (int i = 0; i < max + 1; i++)
        for (int k = 0; k < countMass[i]; k++) {
            mass[j] = i;
            j++;
        }
    auto timeEnd = std::chrono::steady_clock::now();
    Check(timeStart, timeEnd);
}

void SortClass::IntepolSearch() {
    std::cout << "Введите значение элемента: ";
    int key;
    std::cin >> key;
    system("cls");
    int elemPos = -1, steps = -1;
    if (!mass) {
        std::cout << "Ошибка - нет отсортированного массива.\n Нажмите любую клавишу...";
        _getch();
        return;
    }
    auto timeStart = std::chrono::steady_clock::now();
    int middle, min = 0, max = n - 1;
    while (min <= max) {
        steps++;
        if (mass[min] == mass[max])
            if (mass[min] == key) {
                elemPos = min;
                break;
            }
            else { 
                elemPos = -1;
                break;
            }
        middle = min + ((key - mass[min]) * ((max - min) / (mass[max] - mass[min])));
        if (middle < min || middle > max) {
            elemPos = -1;
            break;
        }
        if (key == mass[middle]) {
            elemPos = middle;
            break;
        }
        else if (key < mass[middle]) max = middle - 1;
        else min = middle + 1;
    }
    auto timeEnd = std::chrono::steady_clock::now();
    if (elemPos == -1) {
        std::cout << "Ошибка. Нажмите любую клавишу...";
        _getch();
    }
    else {
        std::cout << "Элемент со значением " << key << " найден на " << elemPos << "-й позиции." << std::endl;
        std::cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()
            << " мс" << std::endl;
        std::cout << "Количество шагов: " << steps << std::endl;
        std::cout << "Нажмите любую клавишу...";
        _getch();
    }
}

void SortClass::FollowBinarySearch(int key, int min, int max) {
    system("cls");
    bool foundFlag = false;
    int min1 = min, max1 = max - 1;
    int mid = (max1 + min1) / 2, steps = -1;
    auto timeStart = std::chrono::steady_clock::now();
    while (!foundFlag && max1 >= min1) {
        steps++;
        if (key == mass[mid])
            foundFlag = true;
        else if (key < mass[mid])
            max1 = mid - 1;
        else
            min1 = mid + 1;
        mid = (max1 + min1) / 2;    }
    auto timeEnd = std::chrono::steady_clock::now();
    if (!foundFlag) {
        std::cout << "Ошибка." << std::endl;
    }
    else {
        std::cout << "Элемент со значением " << key << " найден на " << mid << "-й позиции." << std::endl;
        std::cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()
            << " мс" << std::endl;
        std::cout << "Количество шагов: " << steps << std::endl;
    }
    std::cout << "\nВведите новый элемент для поиска (для выхода введите -1): ";
    int nextKey; std::cin >> nextKey;
    if (nextKey < 0) return;
    if (nextKey == key) {
        FollowBinarySearch(key, 0, n);
        return;
    }
    int mult = -1;
    if (nextKey < key) {
        do {
            mult++;
            min1 -= pow(2, mult);
            if (min1 <= 0) {
                min1 = 0;
                break;
            }
        } while (nextKey < mass[min1]);
        FollowBinarySearch(nextKey, min1, mid);
        return;
    }
    else if (nextKey > key) {
        do {
            mult++;
            max1 += pow(2, mult);
            if (max1 >= n) {
                max1 = n;
                break;
            }
        } while (nextKey > mass[max1]);
        FollowBinarySearch(nextKey, mid, max1);
        return;
    }
}

void SortClass::Check(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    system("cls");
    for (int i = 1; i < n; i++) {
        if (mass[i - 1] > mass[i]) {
            std::cout << "Массив не отсортирован. ";
            break;
        }
        if (i == n - 1) std::cout << "Массив отсортирован. ";
    }
    std::cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " мс" << std::endl;
    std::cout << "Нажмите любую клавишу...";
    _getch();
}