#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "MyGraph.h"

using namespace std;

void main() {
    setlocale(LC_ALL, "Russian");
    cout << "Количество вершин: ";
    int n, i, j, data; cin >> n;
    MyGraph g(n);
    while (1) {
        system("cls");
        cout << "1. Добавить ребро\n2. Удалить ребро\n3. Вывести матрицу смежности\n4. Поиск в глубину\n5. Поиск кратчайшего пути\n6. Вывести остовное дерево\n7. Компоненты связности\n\nВведите 0, чтобы выйти...\n" << endl;
        int choice; cin >> choice;
        switch (choice) {
        case 0:
            exit(0);
        case 1:
            cout << "Вершина 1: "; cin >> i;
            cout << "Вершина 2: "; cin >> j;
            cout << "Вес: "; cin >> data;
            g.AddEdge(i, j, data);
            break;
            cout << "Ребро добавлено, нажмите любую клавишу...";
            _getch();
            break;
        case 2:
            cout << "Вершина 1: ";
            cin >> i;
            cout << "Вершина 2: ";
            cin >> j;
            g.RemoveEdge(i, j);
            break;
            cout << "Ребро удалено, нажмите любую клавишу...";
            _getch();
            break;
        case 3:
            g.Print();
            cout << "\nНажмите любую клавишу...";
            _getch();
            break;
        case 4:
            g.DeepSearch();
            break;
        case 5:
            cout << "Вершина 1: ";
            cin >> i;
            cout << "Вершина 2: ";
            cin >> j;
            g.Dijkstra(i, j);
            break;
        case 6:
            g.Prim();
            break;
        case 7:
            g.Kosaraju();
            break;
        default:
            continue;
        }
    }
}