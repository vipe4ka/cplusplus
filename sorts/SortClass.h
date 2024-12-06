#pragma once
#include <chrono>

class SortClass {
public:
	void SetSize();
	int GetSize();
	void CreateStartMass(int min, int max);
	int GetPos(int i);
	void SelectionSort();
	void ShellSort();
	void QuickSort(int left, int right);
	void CountingSort();
	void IntepolSearch();
	void FollowBinarySearch(int key, int min, int max);

	SortClass() {
		n = NULL;
		mass = nullptr;
		startMass = nullptr;
	}

	~SortClass() {
		delete[] mass;
		delete[] startMass;
	}

private:
	int n;
	int* mass;
	int* startMass;
	void CreateMass();
	void Check(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);
	void QuickSortRecursion(int left, int right);
};