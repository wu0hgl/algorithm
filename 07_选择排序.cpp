#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    选择排序
*/

void selectSort(vector<int> &arr) {
    int outer;
    int inner;
    int min;

    for (outer = 0; outer < arr.size(); outer++) {
        int min = outer;
        for (inner = outer + 1; inner < arr.size(); inner++) {
            if (arr[min] > arr[inner])
                min = inner;
        }
        swap(arr[min], arr[outer]);
    }
}


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 20);
    printVector(arr);
    selectSort(arr);
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
    //vt.resize(len);
    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (range + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}
