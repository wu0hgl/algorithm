#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定数组arr和整数num, 共返回有多少个子数组满足如下情况:
    max(arr[i..j]) - min(arr[i..j]) <= num
    max(arr[i..j])表示子数组arr[i..j]中的最大值, min(arr[i..j])表示子数组arr[i..j]中的最小值
    要求: 数组长度为N, 实现时间复杂度为O(N)的解法
*/

int getNum1(vector<int> &arr, int num) {
    int len = static_cast<int>(arr.size());
    if (len == 0) {
        return 0;
    }

    list<int> qmin;
    list<int> qmax;
    int L = 0;
    int R = 0;
    int res = 0;

    while (L < len) {

        /* 数组外扩 */
        while (R < len) {
            while ((!qmin.empty()) && (arr[qmin.back()] >= arr[R])) {
                qmin.pop_back();
            }
            qmin.push_back(R);
            while ((!qmax.empty()) && (arr[qmax.back()] <= arr[R])) {
                qmax.pop_back();
            }
            qmax.push_back(R);
            if (arr[qmax.front()] - arr[qmin.front()] > num) {  // 不满足条件, 再外扩的子数组都不满足条件
                break;
            }
            R++;
        }

        /* 下标是否过期, 是为了下次的while循环下标是否过期, 而不是本次 */
        if (qmin.front() == L) {
            qmin.pop_front();
        }
        if (qmax.front() == L) {
            qmax.pop_front();
        }

        res += R - L;
        L++;
    }

    return res;
}


bool isValid(vector<int> &arr, int start, int end, int num) {
    int maxValue = INT_MIN;
    int minValue = INT_MAX;
    for (int i = start; i <= end; i++) {
        maxValue = max(maxValue, arr[i]);
        minValue = min(minValue, arr[i]);
    }
    return (maxValue - minValue <= num);
}

/* 暴力方法 */
int getNum2(vector<int> &arr, int num) {
    int res = 0;
    int len = static_cast<int>(arr.size());
    for (int start = 0; start < len; start++) {
        for (int end = start; end < len; end++) {
            if (isValid(arr, start, end, num)) {
                res++;
            }
        }
    }
    return res;
}

int main() {
    vector<int> arr;
    vector<int> res;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    //vector<int> arr = { 4, 3, 5, 4, 3, 3, 6, 7 };
    printVector(arr);

    cout << getNum1(arr, 3) << endl;
    cout << getNum2(arr, 3) << endl;

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