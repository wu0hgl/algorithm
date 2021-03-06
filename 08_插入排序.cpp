﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    插入排序
*/

void insertSort_1(vector<int> &arr) {
    int inner = 0;
    int outer = 0;
    int temp = 0;
    for (outer = 1; outer < arr.size(); outer++) {
        temp = arr[outer];
        inner = outer;
        while ((inner > 0) && (arr[inner - 1] < temp)) {
            swap(arr[inner], arr[inner - 1]);
            inner--;
        }
        arr[inner] = temp;
    }
}

void insertSort_2(vector<int>& arr) {
    int inner = 0;
    int outer = 0;
    int temp = 0;

    for (outer = 0; outer < arr.size(); outer++) {
        temp = arr[outer];
        inner = outer;
        while ((inner > 0) && (arr[inner - 1] > temp)) {
            swap(arr[inner], arr[inner - 1]);
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
    insertSort_1(arr);
    printVector(arr);
    insertSort_2(arr);
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
