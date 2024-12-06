#pragma once
#include <chrono>
#include <fstream>
#include <stack>

class MyGraph {
public:
    MyGraph(int n) {
        this->n = n;
        aMatrix = new int* [n];
        for (int i = 0; i < n; i++) aMatrix[i] = new int[n];
        std::ifstream file("graph.txt");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                file >> aMatrix[i][j];
        file.close();
    }
    void AddEdge(int i, int j, int data);
    void RemoveEdge(int i, int j);
    void Print();
    void DeepSearch();
    void Dijkstra(int v1, int v2);
    void Prim();
    void Kosaraju();
    ~MyGraph() {
        for (int i = 0; i < n; i++)
            delete[] aMatrix[i];
        delete[] aMatrix;
    }
private:
    int** aMatrix;
    int n;
    void DeepSearchRecursion(int v, bool* visit);
    void PrintPath(int* path, int i);
    void fillOrder(int v, bool* visit, std::stack<int>& order);
    void DFS(int** matrix, int v, bool* visit);
    void Time(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);
};