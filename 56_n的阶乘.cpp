#include <iostream>
using namespace std;

/* 
    n的阶乘
*/

long getFactoral_1(int n) {
    if (n == 1) {
        return 1L;
    }
    return static_cast<long> (n*getFactoral_1(n - 1));
}

long getFactoral_2(int n) {
    long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }

    return res;
}

int main() {
    int n = 5;

    cout << getFactoral_1(5) << endl;
    cout << getFactoral_2(5) << endl;

    return 0;
}