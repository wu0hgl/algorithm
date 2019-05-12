#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    希尔排序
*/

void heapSort(vector<int> &vt) {
    int outer;
    int inner;

    int h = 1;
    while (h <= ((vt.size() / 3)))
        h = 3 * h + 1;

    while (h > 0) {
        for (outer = h; outer < vt.size(); outer++) {
            int temp = vt[outer];
            inner = outer;
            while ((inner > h - 1) && (vt[inner - h] > temp)) {
                //swap(vt[inner - 1], vt[inner]);
                vt[inner] = vt[inner - h];
                inner -= h;
            }
            vt[inner] = temp;
        }
        h = (h - 1) / 3;
    }
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 200);
    printVector(arr);
    heapSort(arr);
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
