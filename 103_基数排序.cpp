#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    基数排序
*/

void lsdRadixSort(vector<int>& arr) {
    int maxVal = 0;
    int digitPos = 1;
    int arraySize = arr.size();
    vector<int> bucket(arraySize);

    for (int i = 0; i < arraySize; i++)         // 确定最大元素以确定多少位
        if (arr[i] > maxVal)    maxVal = arr[i];

    while (maxVal / digitPos > 0) {
        int digitCount[10] = { 0 };
        for (int i = 0; i < arraySize; i++)         // 类似计数排序记录每一个位上多少数字
            digitCount[(arr[i] / digitPos) % 10]++;
        for (int i = 1; i < 10; i++)                // 累加目的是为了确定排序后每个数字应该位于第几位
            digitCount[i] += digitCount[i - 1];
        for (int i = arraySize - 1; i >= 0; i--)    // 为保证稳定性, 从右往左扫描
            bucket[--digitCount[arr[i] / digitPos % 10]] = arr[i];
        // 以上相当于计数排序

        for (int i = 0; i < arraySize; i++)         // 把桶里数字放到数组中
            arr[i] = bucket[i];

        digitPos *= 10;                             // 开始比较下一位
    }
}

int main() {
    //vector<int> arr = { 1, 2 };
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    printVector(arr);
    lsdRadixSort(arr);
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
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}