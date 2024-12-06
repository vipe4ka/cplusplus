#include "MyGraph.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

void MyGraph::AddEdge(int i, int j, int data) {
	aMatrix[i][j] = data;
}

void MyGraph::RemoveEdge(int i, int j) {
	aMatrix[i][j] = 0;
}

void MyGraph::Print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(3) << aMatrix[i][j] << " ";
		cout << endl;
	}
}

void MyGraph::DeepSearch() {
	bool* visit;
	auto timeStart = std::chrono::steady_clock::now();
	for (int i = 0; i < n; i++) {
		visit = new bool[n] {false};
		cout << i << ": ";
		DeepSearchRecursion(i, visit);
		cout << endl;
		delete[] visit;
	}
	auto timeEnd = std::chrono::steady_clock::now();
	Time(timeStart, timeEnd);
}

void MyGraph::DeepSearchRecursion(int v, bool* visit) {
	visit[v] = true;
	for (int i = 0; i < n; i++)
		if (aMatrix[v][i] && !visit[i]) {
			cout << "(" << v << "->" << i << "), ";
			DeepSearchRecursion(i, visit);
		}
}

void MyGraph::Dijkstra(int v1, int v2) {
	bool* visit = new bool[n];
	int* dist = new int[n];
	int* path = new int[n];

	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
		visit[i] = false;
	}

	int index;
	auto timeStart = std::chrono::steady_clock::now();
	path[v1] = -1;
	dist[v1] = 0;
	for (int k = 0; k < n - 1; k++) {
		int min = INT_MAX;
		for (int i = 0; i < n; i++)
			if (!visit[i] && dist[i] <= min) {
				min = dist[i];
				index = i;
			}
		visit[index] = true;
		for (int i = 0; i < n; i++)
			if (!visit[i] && aMatrix[index][i] && dist[index] != INT_MAX && dist[index] + aMatrix[index][i] < dist[i]) {
				dist[i] = dist[index] + aMatrix[index][i];
				path[i] = index;
			}
	}
	auto timeEnd = std::chrono::steady_clock::now();

	cout << "Кратчайшее расстояние " << v1 << " -> " << v2 << ": " << dist[v2] << endl;
	cout << "Кратчайший путь: " << v1 << " -> ";
	PrintPath(path, v2);

	Time(timeStart, timeEnd);
	delete[] visit;
	delete[] dist;
	delete[] path;
}


void MyGraph::PrintPath(int* path, int i) {
	if (path[i] == -1) return;
	PrintPath(path, path[i]);
	cout << i << " ";
}

void MyGraph::Prim() {
	int numEdge = 0;
	bool* visit = new bool[n] {false};
	visit[0] = true;
	int sum = 0;

	auto timeStart = std::chrono::steady_clock::now();
	while (numEdge < n - 1) {
		int min = INT_MAX;
		int row = 0;
		int col = 0;

		for (int i = 0; i < n; i++)
			if (visit[i])
				for (int j = 0; j < n; j++)
					if (!visit[j] && aMatrix[i][j])
						if (min > aMatrix[i][j]) {
							min = aMatrix[i][j];
							row = i;
							col = j;
						}
		sum += aMatrix[row][col];
		cout << "(" << row << " -> " << col << "): S = " << sum;
		if (numEdge != n - 2) cout << "\n+ ";
		else cout << endl;
		visit[col] = true;
		numEdge++;
	}
	auto timeEnd = std::chrono::steady_clock::now();

	delete[] visit;
	Time(timeStart, timeEnd);
}

void MyGraph::Kosaraju() {
	std::stack<int> order;
	bool* visit = new bool[n];
	for (int i = 0; i < n; i++)
		visit[i] = false;

	auto timeStart = std::chrono::steady_clock::now();

	for (int i = 0; i < n; i++)
		if (!visit[i]) fillOrder(i, visit, order);
	
	int** aMatrixT = new int* [n];
	for (int i = 0; i < n; i++) aMatrixT[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			aMatrixT[i][j] = aMatrix[j][i];

	for (int i = 0; i < n; i++)
		visit[i] = false;

	while (!order.empty()) {
		int v = order.top();
		order.pop();

		if (!visit[v]) {
			DFS(aMatrixT, v, visit);
			cout << endl;
		}
	}

	auto timeEnd = std::chrono::steady_clock::now();

	delete[] visit;
	for (int i = 0; i < n; i++) delete[] aMatrixT[i];
	delete[] aMatrixT;

	Time(timeStart, timeEnd);
}

void MyGraph::fillOrder(int v, bool* visit, std::stack<int>& order) {
	visit[v] = true;

	for (int i = 0; i < n; i++) 
		if (aMatrix[v][i] && !visit[i]) fillOrder(i, visit, order);

	order.push(v);
}

void MyGraph::DFS(int** matrix, int v, bool* visit) {
	visit[v] = true;
	cout << v << " ";

	for (int i = 0; i < n; i++)
		if (matrix[v][i] && !visit[i]) DFS(matrix, i, visit);

}

void MyGraph::Time(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
	std::cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " мс" << std::endl;
	std::cout << "Нажмите любую клавишу...";
	_getch();
}