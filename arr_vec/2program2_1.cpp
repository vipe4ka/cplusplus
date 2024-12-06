#include <iostream>
#include <array>
#include <clocale>
#include <vector>
#include <algorithm>

using namespace std;

static const int arraySize = 10;

void main() {
	setlocale(LC_ALL, "Russian");

	array<int, arraySize> myArray{};
	cout << "Введите элементы массива (в диапозоне от -50 до 50):\n";
	for (int i = 0; i < arraySize; i++) {
		cout << "myArray[" << i << "] = ";
		cin >> myArray[i];
	}

	cout << "\nВведенный массив: ";
	copy(myArray.begin(), myArray.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	int sum = 0;
	for (auto& i : myArray) sum += i;
	int average = sum / arraySize;
	cout << "Среднее арифмитическое: " << average << endl;

	for (auto& i : myArray)
		if (i == average) {
			swap(i, myArray.at(0));
			cout << "\nПолучившийся массив: ";
			copy(myArray.begin(), myArray.end(), ostream_iterator<int>(cout, " "));
			return;
		}

	vector<int> min, max;
	for (auto& i : myArray) {
		if (i < average) min.push_back(i);
		else max.push_back(i);
	}
	sort(min.begin(), min.end(), greater<int>());
	sort(max.begin(), max.end());

	int element;
	if (abs(abs(average) - min[0]) < abs(abs(average) - max[0])) element = min[0];
	else element = max[0];
	min.clear();
	min.resize(0);
	min.shrink_to_fit();
	max.clear();
	max.resize(0);
	max.shrink_to_fit();

	for (auto& i : myArray)
		if (i == element) {
			swap(i, myArray.at(0));
			cout << "\nПолучившийся массив: ";
			copy(myArray.begin(), myArray.end(), ostream_iterator<int>(cout, " "));
			break;
		}

	myArray.fill(0);
}