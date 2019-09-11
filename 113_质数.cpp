#include <iostream>
#include <vector>
using namespace std;

/*
    ÇóÖÊÊı
*/

vector<int> arr1;
bool isPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
void func_1(int num) {
    for (int i = 2; i <= num; i++) {
        if (isPrime(i)) {
            arr1.push_back(i);
        }
    }
}

vector<int> arr2;
void func_2(int num) {
    vector<bool> flag(num + 1, true);
    for (int i = 2; i <= num; i++) {
        if (flag[i]) {
            arr2.push_back(i);
            for (int j = 2; i * j <= num; j++) {
                flag[i*j] = false;
            }
        }
    }
}

int main() {
    func_1(100);
    func_2(100);
    for (auto i : arr1)
        cout << i << " ";
    cout << endl;

    for (auto i : arr2)
        cout << i << " ";
    cout << endl;
    return 0;
}