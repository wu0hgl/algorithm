#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    在一个数组中, 每一个数左边比当前数小的数累加起来, 叫做这个数组的小和. 
    求一个数字的小和. 如[1, 3, 4, 2, 5]小和为16
*/

int merge(vector<int>& arr, int left, int mid, int right) {
    int leftPtr = left;      // 左侧游标
    int rightPtr = mid + 1; // 右侧游标

    vector<int> temp(right - left + 1);
    int ptr = 0;
    int res = 0;

    while (leftPtr <= mid && rightPtr <= right) {
        res += (arr[leftPtr] < arr[rightPtr] ? arr[leftPtr] * (right - rightPtr + 1) : 0);    // 没有浪费小范围比较时的次数
        temp[ptr++] = arr[leftPtr] < arr[rightPtr] ? arr[leftPtr++] : arr[rightPtr++];
    }
    while (leftPtr <= mid) {
        temp[ptr++] = arr[leftPtr++];
    }
    while (rightPtr <= right)
        temp[ptr++] = arr[rightPtr++];

    for (ptr = 0; ptr < (right - left + 1); ptr++) {
        arr[left + ptr] = temp[ptr];
    }

    return res;
}

int mergeSort(vector<int>& arr, int left, int right) {
    if (left == right)
        return 0;

    int mid = left + ((right - left) >> 1);

    return (mergeSort(arr, left, mid)
            + mergeSort(arr, mid + 1, right)
            + merge(arr, left, mid, right));
}

int main() {
    vector<int> arr;
    generatorRandomArray(arr, 5, 5);
    printVector(arr);

    cout << mergeSort(arr, 0, static_cast<int>(arr.size()) - 1) << endl;

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

    srand(static_cast<int>(time(NULL)));
    for (int i = 0; i < len; i++) {
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        if (temp == 0) {
            continue;
        }
        else {
            vt.push_back(temp);
        }
    }
}