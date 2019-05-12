#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    冒泡排序
*/

// 普通冒泡排序
void bubbleSort_1(vector<int> &arr) {
    int outer;
    int inner;
    for (outer = arr.size() - 1; outer > 0; outer--)
        for (inner = 0; inner < outer; inner++)
            if (arr[inner] > arr[inner + 1])
                swap(arr[inner], arr[inner + 1]);
}

// 改进后冒泡排序
void bubbleSort_2(vector<int> &arr) {
    int outer;
    int inner;
    bool needSwap = true;
    for (outer = arr.size() - 1; (outer > 0) && (needSwap == true); outer--) {
        needSwap = false;
        for (inner = 0; inner < outer; inner++) {
            if (arr[inner] > arr[inner + 1]) {
                needSwap = true;
                swap(arr[inner], arr[inner + 1]);
            }
        }
    }
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 20);
    printVector(arr);
    //bubbleSort_1(arr);
    bubbleSort_2(arr);
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
