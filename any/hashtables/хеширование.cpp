#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <conio.h>

using namespace std;

typedef int T;  //тип элементов
typedef struct Node_ {
    T data;//данные, хранящиеся в вершине
    struct Node_* next; //следующая вершина
} Node;

Node** hashTable; //хеш-таблица
int hashTableSize; //размер хеш-таблицы
typedef int hashTableIndex; // индекс в хеш-таблице

//хеш-функция размещения вершины
hashTableIndex myhash(T data) {
    return (data % hashTableSize); //формула, по которой происходит хеширование
}

//функция поиска местоположения и вставки вершины в таблицу
Node* InsertNode(T data) {
    // вставка вершины в начало списка
    hashTableIndex bucket = myhash(data);
    Node* p;
    assert((p = new Node) != 0); //проверяем, хватает ли памяти
    Node* p0 = hashTable[bucket];
    hashTable[bucket] = p; //тут пихаем в начало списка
    p->next = p0; //меняем указатели
    p->data = data;
    return p;
}

//функция удаления вершины из таблицы
void DeleteNode(T data) {
    Node* p0 = 0;
    hashTableIndex bucket = myhash(data);
    Node* p = hashTable[bucket];
    while (p && !(p->data == data)) { //ищем число, которое надо удалить
        p0 = p;
        p = p->next;
    }
    if (!p) return;
    if (p0) p0->next = p->next; //удаляем
    else hashTable[bucket] = p->next;
    delete p, p0;
}

//функция поиска вершины со значением data
Node* FindNode(T data) {
    Node* p = hashTable[myhash(data)];
    while (p && !(p->data == data)) p = p->next;
    return p;
}

void main() {
    int c, n, data; //с - переменная выбора для меню, n - количество данных для хеширования, data - собственно само число, переменная k нужная для красивого вывода в консоль
    int* arr = new int; //массив из данных
    bool initHashTable = false; //проверка, существует ли хеш-таблица вообще (пока ее нет, поэтому false)
    ofstream file;
    while (1) {
        system("cls");
        cout << "1. Init new HashTable\n" << "2. Insert node\n" << "3. Find node\n" << "4. Print to console\n" << "5. Print to files\n" << "6. Delete node\n" << "7. Clear HashTable\n\n";
        cin >> c;
        switch (c) {
        case 1: //здесь создаем хеш-таблицу
            if (initHashTable) { //удаляем старую
                delete[] arr;
                delete[] hashTable;
            }
            cout << "Number of elements: ";
            cin >> n;
            cout << "HashTable size: ";
            cin >> hashTableSize;
            arr = new int[n];
            hashTable = new Node*[hashTableSize];
            for (int i = 0; i < hashTableSize; i++) hashTable[i] = NULL; //инициализация хеш-таблицы

            for (int i = 0; i < n; i++) arr[i] = rand(); //рандомная генерация массива
            for (int i = 0; i < n; i++) InsertNode(arr[i]); //заполнение хеш-таблицы элементами массива
            for (int i = n - 1; i >= 0; i--) FindNode(arr[i]); //поиск элементов массива по хеш-таблице
            
            initHashTable = true;
            break;
        case 2: //здесь вставляем новые данные в хеш-таблицу
            if (initHashTable) {
                cout << "Data: ";
                cin >> data;
                InsertNode(data);
            }
            else cout << "HashTable is not exist" << endl;
            _getch(); //каждый раз, когда выводится какая-то надпись, программа ждет, пока мы не нажмем какую-нибудь кнопку, и затем продолжает работу
            break;
        case 3: //здесь ищем данные в таблице
            if (initHashTable) {
                cout << "Data: ";
                cin >> data;
                if (FindNode(data)) cout << "Hash: " << myhash(data) << endl; //если нашли, то выводим значение хеш-функции
                else cout << "Node not found" << endl;
            }
            else cout << "HashTable is not exist" << endl;
            _getch();
            break;
        case 4: //выводим хеш-таблицу
            if (initHashTable) {
                cout << "HashTable:" << endl;
                for (int i = 0; i < hashTableSize; i++) {
                    cout << i << "  :  ";
                    Node* temp = hashTable[i];
                    while (temp) {
                        cout << temp->data << " -> ";
                        temp = temp->next;
                    }
                    cout << endl;
                }
            }
            else cout << "HashTable is not exist" << endl;
            _getch();
            break;
        case 5: //выводим таблицу в файл
            if (initHashTable) {
                // сохранение хеш-таблицы в файл HashTable.txt
                file.open("HashTable.txt");
                for (int i = 0; i < hashTableSize; i++) {
                    file << i << "  :  ";
                    Node* Temp = hashTable[i];
                    while (Temp) {
                        file << Temp->data << " -> ";
                        Temp = Temp->next;
                    }
                    file << endl;
                }
                file.close();
            }
            else cout << "HashTable is not exist" << endl;
            _getch();
            break;
        case 6: //тута удаляем один элемент
            if (initHashTable) {
                cout << "Data: ";
                cin >> data;
                DeleteNode(data);
                cout << "Node was deleted" << endl;
            }
            else cout << "HashTable is not exist" << endl;
            _getch();
            break;
        case 7: //тут удаляем всю таблицу
            if (initHashTable) {
                for (int i = n - 1; i >= 0; i--) DeleteNode(arr[i]); //очистка хеш-таблицы
                delete arr;
                delete hashTable;
                initHashTable = false;
                cout << "HashTable was deleted" << endl;
            }
            else cout << "HashTable is not exist" << endl;
            _getch();
            break;
        default: //если дурачок нажал неверный пункт меню
            cout << "whong choice" << endl;
            _getch();
        }
    }
}