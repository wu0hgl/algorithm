#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    堆排
*/

void heapInsert(vector<int> &arr, int index) {      // 上浮: 当前节点若比父节点大, 交换两个节点
    while (arr[index] > arr[(index - 1) / 2]) {     // (0 - 1) / 2 = 0还是和0比较
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapify(vector<int> &vt, int index, int size) {    // 下沉: 当前节点比子节点小
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

void heapSort(vector<int> &vt) {
    if (vt.size() < 2)
        return;
    for (int i = 0; i < vt.size(); i++) {
        heapInsert(vt, i);
    }
    int size = vt.size();
    swap(vt[0], vt[--size]);
    while (size > 0) {
        heapify(vt, 0, size);
        swap(vt[0], vt[--size]);
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
