#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    插入排序
*/

void insertSort(vector<int> &arr) {
    int outer;
    int inner;
    int temp;

    for (outer = 1; outer < arr.size(); outer++) {
        temp = arr[outer];
        inner = outer;
        while ((inner > 0) && (arr[inner - 1] > temp)) {
            swap(arr[inner - 1], arr[inner]);
            inner--;
        }
        arr[inner] = temp;
    }
}


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 20);
    printVector(arr);
    insertSort(arr);
    printVector(arr);

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (range + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}
