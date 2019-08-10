#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    选择排序
*/

void selectSort_1(vector<int> &arr) {
    int outer = 0;
    int inner = 0;
    int index = 0;

    for (outer = 0; outer < arr.size() - 1; outer++) {
        index = outer;
        for (inner = outer + 1; inner < arr.size(); inner++) {
            if (arr[inner] < arr[index]) {
                index = inner;
            }
        }
        swap(arr[outer], arr[index]);
    }
}


void selectSort_2(vector<int>& arr) {
    int inner = 0;
    int outer = 0;
    int index = 0;

    for (inner = 0; inner < arr.size() - 1; inner++) {
        index = inner;
        for (outer = inner + 1; outer < arr.size(); outer++) {
            if (arr[outer] > arr[index]) {
                index = outer;
            }
        }
        swap(arr[inner], arr[index]);
    }
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 20);
    printVector(arr);
    selectSort_1(arr);
    printVector(arr);
    selectSort_2(arr);
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
