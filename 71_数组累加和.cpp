#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组arr, 数组有正有负, 和一个整数aim. 
    求在arr中， 累加和等于aim的最长子数组的长度
*/

int maxLength_1(vector<int>& arr, int aim) {
    int len = 0;
    int sum = 0;
    //map<int, int> lenMap;   // key: 累加和, value: 第一次出现累加和的位置
    unordered_map<int, int> lenMap;
    lenMap[0] = -1;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
        if (lenMap.count(sum - aim)) {
            int temp = i - lenMap[sum - aim];
            len = max(temp, len);
        } 

        if (!lenMap.count(sum)) {   // 未含有表示第一次出现
            lenMap[sum] = i;
        }
    }
    return len;
}

/* 暴力解 */
int maxLength_2(vector<int>& arr, int aim) {
    size_t len = 0;
    for (size_t start = 0; start < arr.size(); start++) {
        int sum = 0;
        for (size_t end = start; end < arr.size(); end++) {
            sum += arr[end];
            if (sum == aim) {
                len = (end - start + 1) > len ? (end - start + 1) : len;
            }
        }
    }
    return len;
}

int main() {
    vector<int> arr;
    generatorRandomArray(arr, 10, 5);
    //vector<int> arr = { 1, 2, 3};
    //vector<int> arr = { 1, 1, 3 };
    printVector(arr);

    cout << maxLength_1(arr, 3) << endl;
    cout << maxLength_2(arr, 3) << endl;

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
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (range + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}