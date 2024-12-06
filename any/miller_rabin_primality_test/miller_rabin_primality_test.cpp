#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;

cpp_int multiplicationInMod(cpp_int x, cpp_int y, cpp_int m) {
    if (y == 1)
        return x;
    if (y % 2 == 0) {
        cpp_int t = multiplicationInMod(x, y / 2, m);
        return (2 * t) % m;
    }
    return (multiplicationInMod(x, y - 1, m) + x) % m;
}

cpp_int powInMod(cpp_int a, cpp_int n, cpp_int mod) {
    if (n == 0)
        return 1;
    if (n % 2 == 0) {
        cpp_int t = powInMod(a, n / 2, mod);
        return multiplicationInMod(t, t, mod) % mod;
    }
    return (multiplicationInMod(powInMod(a, n - 1, mod), a, mod)) % mod;
}

bool MillerRabin(cpp_int n) {
    cout << "Enter number of steps: ";
    int steps; cin >> steps;

    cpp_int t = n - 1, s = 0;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }

    mt19937 mersenne;
    uniform_int_distribution<cpp_int> random(2, n - 2);

    for (int i = 0; i < steps; i++) {
        cpp_int a = random(mersenne);
        cpp_int x = powInMod(a, t, n);
        if (x != 1 or x != n - 1)
            for (int j = 0; j < s - 1; j++) {
                x = powInMod(x, 2, n);
                if (x == 1) return false;
                else if (x == n - 1) break;
            }
        else return false;
    }
    return true;
}

void main() {
    ifstream input("input.txt");
    assert(input);
    string numstr;
    getline(input, numstr);
    input.close();
    cpp_int num = cpp_int(numstr);
    cout << "Number:\n" << num << endl;
    if (num % 2 == 0) {
        cout << "Number is composite: num % 2 = 0" << endl;
        return;
    }

    auto timeStart = chrono::steady_clock::now();
    bool is_prime = MillerRabin(num);
    auto timeEnd = chrono::steady_clock::now();

    if (is_prime) cout << "Number is probably prime" << endl;
    else cout << "Number is composite" << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart).count() << " ms" << endl;
}