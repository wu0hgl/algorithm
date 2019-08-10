#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    堆排
*/

/* 最大堆 */
void heapInsert_MAX(vector<int> &arr, int index) {      // 上浮: 当前节点若比父节点大, 交换两个节点
    while (arr[index] > arr[(index - 1) / 2]) {         // 循环边界条件挺有意思, (0 - 1) / 2 = 0还是和0比较
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
void heapify_MAX(vector<int> &vt, int index, int size) {    // 下沉: 当前节点比子节点小
    int left = index * 2 + 1;
    while (left < size) {
        int largest = (left + 1 < size && vt[left + 1] > vt[left])
            ? left + 1 
            : left;
        largest = vt[largest] > vt[index] ? largest : index;
        if (largest == index)
            return;
        swap(vt[index], vt[largest]);
        index = largest;
        left = 2 * index + 1;
    }
}
void heapSort_MIN_MAX(vector<int> &vt) {
    if (vt.size() < 2)
        return;
    for (int i = 0; i < static_cast<int>(vt.size()); i++) {
        heapInsert_MAX(vt, i);
    }
    int size = vt.size();
    swap(vt[0], vt[--size]);
    while (size > 0) {
        heapify_MAX(vt, 0, size);
        swap(vt[0], vt[--size]);
    }
}

/* 最小堆 */
void heapify_MIN(vector<int>& arr, int index) {
    while (arr[index] < arr[(index - 1) / 2]) {
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
void heapify_MIN(vector<int>& arr, int index, int len) {
    int lPtr = index * 2 + 1;
    while (lPtr < len) {
        int least = (lPtr + 1 < len && arr[lPtr + 1] < arr[lPtr]) 
                    ? lPtr + 1
                    : lPtr;
        least = arr[index] < arr[least] ? index : least;
        if (least == index) {
            return;
        }
        swap(arr[least], arr[index]);
        index = least;
        lPtr = index * 2 + 1;
    }
}
void heapSort_MAX_MIN(vector<int>& arr) {
    if (arr.size() < 2)
        return;
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        heapify_MIN(arr, i);
    }
    int size = arr.size();
    swap(arr[0], arr[size - 1]);
    for (int i = size - 1; i > 0; i--) {
        heapify_MIN(arr, 0, i);
        swap(arr[0], arr[i - 1]);
    }
}

int main() {
    //vector<int> arr = { 1, 2 };
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 200);
    printVector(arr);
    heapSort_MIN_MAX(arr);
    printVector(arr);
    heapSort_MAX_MIN(arr);
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
