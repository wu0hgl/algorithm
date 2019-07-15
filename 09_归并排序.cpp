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

void merge(vector<int> &arr, int left, int mid, int right) {
    int leftPtr = left;
    int rightPtr = mid + 1;
    vector<int> vt;
    while ((leftPtr <= mid) && (rightPtr <= right)) {
        vt.push_back(arr[leftPtr] < arr[rightPtr] ? arr[leftPtr++] : arr[rightPtr++]);
    }
    while (leftPtr <= mid)
        vt.push_back(arr[leftPtr++]);
    while (rightPtr <= right)
        vt.push_back(arr[rightPtr++]);
    for (size_t i = 0; i < vt.size(); i++)
        arr[left + i] = vt[i];
    return;
}

void mergeSort(vector<int> &vt, int left, int right) {
    //if (left <= right) {      // 不能有等于号
    if (left < right) {     
        int mid = left + ((right - left) >> 1);
        mergeSort(vt, left, mid);
        mergeSort(vt, mid + 1, right);
        merge(vt, left, mid, right);
    }
    //if (left == right)
    //    return;
    //int mid = left + ((right - left) >> 1);
    //mergeSort(vt, left, mid);
    //mergeSort(vt, mid + 1, right);
    //merge(vt, left, mid, right);
}


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 100, 200);
    printVector(arr);
    mergeSort(arr, 0, arr.size() - 1);
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
