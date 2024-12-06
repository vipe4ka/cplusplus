#include <set>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iterator>

using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	ifstream file;
	file.open("numbers.txt");

	set<double> nums;
	double num;
	while (file >> num)
		nums.insert(num);
	file.close();

	cout << "Множество:" << endl;
	copy(nums.begin(), nums.end(), ostream_iterator<double>(cout, " "));
	cout << endl << endl;

	cout << "Введите индекс элемента для удаления: ";
	int index;
	cin >> index;
	int it = 0;
	double element;
	for (auto& i : nums) {
		element = i;
		if (it == index) break;
		it++;
	}
	nums.erase(element);

	cout << "Получившееся множество:" << endl;
	copy(nums.begin(), nums.end(), ostream_iterator<double>(cout, " "));

	ofstream filenew;
	filenew.open("numbers.txt", ios_base::out);
	for (auto& i : nums) filenew << i << '\n';
	filenew.close();

}