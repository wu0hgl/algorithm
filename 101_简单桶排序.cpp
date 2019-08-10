#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    简单桶排序
*/

void bucketSort(vector<int>& arr) {
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < min)   min = arr[i];
        if (arr[i] > max)   max = arr[i];
    }
    vector<int> count(max - min + 1);
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - min]++;
    }

    vector<int> res(arr.size());
    int i, j, k;
    for (i = j = 0; i < (max - min + 1); i++, j = k) {
        for (k = j; k < j + count[i]; k++) {
            res[k] = i + min;
        }
    }
    arr.swap(res);
}

int main() {
    //vector<int> arr = { 1, 2 };
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    printVector(arr);
    bucketSort(arr);
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