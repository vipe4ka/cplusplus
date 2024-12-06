#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Функция для разложения числа в непрерывную дробь
vector<int> continued_fraction(double a, int iterations) {
    vector<int> fractions;

    for (int i = 0; i < iterations; ++i) {
        int q = static_cast<int>(floor(a));  // Целая часть
        fractions.push_back(q);              // Добавляем ее в список
        double fractional_part = a - q;      // Дробная часть

        if (fabs(fractional_part) < 1e-9) {  // Если дробная часть близка к нулю, выходим
            break;
        }

        a = 1.0 / fractional_part;  // Инвертируем дробную часть
    }

    return fractions;
}

// Функция для восстановления числителя и знаменателя из цепной дроби
pair<long long, long long> get_fraction_from_continued(const vector<int>& fractions) {
    long long numerator = 1;
    long long denominator = 0;
    long long prev_numerator = 0;
    long long prev_denominator = 1;

    for (int i = fractions.size() - 1; i >= 0; --i) {
        long long temp_numerator = numerator;
        long long temp_denominator = denominator;

        numerator = fractions[i] * numerator + prev_numerator;
        denominator = fractions[i] * denominator + prev_denominator;

        prev_numerator = temp_numerator;
        prev_denominator = temp_denominator;
    }

    return { numerator, denominator };
}

// Функция для поиска НОД
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    setlocale(LC_ALL, "Russian");
    long long N;
    cout << "Введите число для факторизации: ";
    cin >> N;

    // Шаг 2: Начальное приближение — приближение квадратного корня N
    double a = sqrt(N);

    // Число итераций для точности разложения в непрерывную дробь
    int iterations = 100;

    // Шаг 3: Разложение sqrt(N) в непрерывную дробь
    vector<int> fractions = continued_fraction(a, iterations);

    // Выводим цепную дробь
    cout << "Непрерывная дробь для sqrt(" << N << "):\n[";
    for (size_t i = 0; i < fractions.size(); ++i) {
        cout << fractions[i];
        if (i != fractions.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // Шаг 4: Восстанавливаем приближенную дробь
    pair<long long, long long> fraction = get_fraction_from_continued(fractions);
    long long x = fraction.first;
    long long y = fraction.second;

    // Шаг 5: Поиск НОД для нахождения возможного делителя числа N
    long long factor = gcd(x, N);

    // Шаг 6: Проверка, является ли найденное число делителем
    if (factor != 1 && factor != N) {
        cout << "Найден делитель числа N: " << factor << endl;
        cout << "Другой делитель: " << N / factor << endl;
    }
    else {
        cout << "Не удалось найти делители методом Лемера и Пауэрса.\n";
    }

    return 0;
}