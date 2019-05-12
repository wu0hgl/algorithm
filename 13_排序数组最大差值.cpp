#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组, 求排序之后相邻两数的最大差值, 要求时间复杂度O(N), 且要求使用非基于比较的排序
*/

int bucket(long num, long len, long minId, long maxId) {
    return (int)((num - minId) * len / (maxId - minId));
}

int getMaxGap(vector<int> vt) {
    if (vt.size() < 2)
        return 0;

    int len = vt.size();
    int maxId = INT_MIN;
    int minId = INT_MAX;

    for (int i = 0; i < len; i++) {
        maxId = max(vt[i], maxId);
        minId = min(vt[i], minId);
    }
    vector<bool> hasNum(len + 1, false);
    vector<int> maxs(len + 1, 0);
    vector<int> mins(len + 1, 0);
    int bid = 0;        // 用于记录桶号
    for (int i = 0; i < len; i++) {
        bid = bucket(vt[i], len, minId, maxId);
        mins[bid] = hasNum[bid] ? min(mins[bid], vt[i]) : vt[i];
        maxs[bid] = hasNum[bid] ? max(maxs[bid], vt[i]) : vt[i];
        hasNum[bid] = true;
    }
    int res = 0;
    int lastMax = maxs[0];
    int i = 1;
    for (; i <= len; i++) {
        if (hasNum[i]) {
            res = max(res, mins[i] - lastMax);
            lastMax = maxs[i];
        }
    }

    return res;
}

int getMaxGapTest(vector<int> vt) {
    int max = 0;
    for (int i = 0; i < vt.size() - 1; i++) {
        int temp = abs(vt[i] - vt[i + 1]);
        if (temp > max) {
            max = temp;
            cout << "vt[1] = " << vt[i] << " vt[2] = " << vt[i + 1] << " maxGap = " << temp << endl;
        }
    }
    return max;
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 100);
    sort(arr.begin(), arr.end());
    printVector(arr);
    cout << getMaxGapTest(arr) << endl;
    cout << getMaxGap(arr) << endl;
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
        //temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}
