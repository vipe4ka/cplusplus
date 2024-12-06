#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <conio.h>

using namespace std;

void main() {
    setlocale(LC_ALL, "Russian");
    printf("Введите размер массива: ");
    int n; scanf("%d", &n);
    printf("Введите диапазон массива:\nминимум - ");
    int min; scanf("%d", &min);
    printf("максимум - ");
    int max; scanf("%d", &max);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<int> randomize(min, max);
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = randomize(mersenne);

    FILE *inFile;
    inFile = fopen("in.txt", "w");
    for (int i = 0; i < n; i++) fprintf(inFile, "%d\n", arr[i]);
    fclose(inFile);
    delete[] arr;

    FILE *A, *B, *C, *D;
    int numOfSep, n1, n2, temp, steps = 0;
    bool change, noendB, noendC;

    auto timeStart = std::chrono::steady_clock::now();
    do {
        steps++;
        //разделение
        A = fopen("in.txt", "r");
        B = fopen("temp1.txt", "w");
        C = fopen("temp2.txt", "w");
        if (!A || !B || !C) {
            printf("Ошибка в работе с файлами.\n");
            return;
        }
        numOfSep = 0; change = true;
        fscanf(A, "%d", &n2);
        while (!feof(A)) {
            D = change ? B : C;
            fprintf(D, "%d\n", n2);
            while (fscanf(A, "%d", &n1) != EOF && n1 >= n2) {
                fprintf(D, "%d\n", n1);
                n2 = n1;
            }
            n2 = n1; numOfSep++;
            change = !change;
        }
        fclose(A);
        fclose(B);
        fclose(C);
        //слияние
        A = fopen("in.txt", "w");
        B = fopen("temp1.txt", "r");
        C = fopen("temp2.txt", "r");
        if (!A || !B || !C) {
            printf("Ошибка в работе с файлами.\n");
            return;
        }
        noendB = fscanf(B, "%d", &n1) != EOF;
        noendC = fscanf(C, "%d", &n2) != EOF;
        temp = n1 < n2 ? n1 : n2;
        while (noendB && noendC) {
            if (n1 <= n2) {
                fprintf(A, "%d\n", n1);
                temp = n1;
                noendB = fscanf(B, "%d", &n1) != EOF;
            }
            else {
                fprintf(A, "%d\n", n2);
                temp = n2;
                noendC = fscanf(C, "%d", &n2) != EOF;
            }
            if ((n1 < temp || !noendB) && n2 >= temp && noendC)
                do {
                    fprintf(A, "%d\n", n2);
                    temp = n2;
                    noendC = fscanf(C, "%d", &n2) != EOF;
                } while (n2 >= temp && noendC);
            if ((n2 < temp || !noendC) && n1 >= temp && noendB)
                do {
                    fprintf(A, "%d\n", n1);
                    temp = n1;
                    noendB = fscanf(B, "%d", &n1) != EOF;
                } while (n1 >= temp && noendB);
        }
        if (noendB) {
            fprintf(A, "%d\n", n1);
            while (fscanf(B, "%d", &n1) != EOF) fprintf(A, "%d\n", n1);
        }
        if (noendC) {
            fprintf(A, "%d\n", n2);
            while (fscanf(C, "%d", &n2) != EOF) fprintf(A, "%d\n", n2);
        }
        fclose(A);
        fclose(B);
        fclose(C);
    } while (numOfSep > 1);
    auto timeEnd = std::chrono::steady_clock::now();

    int time = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();
    printf("\nВремя выполнения: %d мс\n", time);
    printf("Количество шагов: %d\n", steps);
}