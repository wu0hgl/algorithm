#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组arr, 全是正数; 一个整数aim, 求累加和等于aim的最长子数组,
    要求额外空间复杂度O(1), 时间复杂度O(N)
*/

int getMaxLength_1(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim <= 0)) {
        return -1;
    }
    int res = INT_MIN;
    for (int end = 0; end < static_cast<int>(arr.size()); end++) {
        for (int start = 0; start <= end; start++) {
            int sum = 0;
            for (int i = start; i <= end; i++) {
                sum += arr[i];
            }
            if (sum == aim) {
                res = max(res, (end - start + 1));
            }
        }
    }
    return res;
}

int getMaxLength_2(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim <= 0)) {
        return -1;
    }

    int lPtr = 0;
    int rPtr = 0;
    int sum = arr[0];
    int len = 0;
    while (rPtr < static_cast<int>(arr.size())) {
        if (sum == aim) {
            len = max(len, rPtr - lPtr + 1);
            sum -= arr[lPtr++];     // sum要变化对应值
        }
        else if (sum < aim) {
            rPtr++;
            if (rPtr == static_cast<int>(arr.size())) { // 防止越界
                break;
            }
            sum += arr[rPtr];
        }
        else {
            sum -= arr[lPtr++];
        }
    }
    return len;
}

int main() {
    //vector<int> arr = { 1, 2, 3, 100, 4, 1, 1, 1, 1, 1, 1 };
    vector<int> arr;
    generatorRandomArray(arr, 50, 5);
    printVector(arr);

    cout << getMaxLength_1(arr, 20) << endl;
    cout << getMaxLength_2(arr, 20) << endl;

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