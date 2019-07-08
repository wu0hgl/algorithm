#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组arr, 值可正, 可负, 可0. 一个整数aim, 
    求累加和小于等于aim的, 最长子数组, 要求时间复杂度O(N)
*/

int maxLengthAwesom_1(vector<int>& arr, int aim) {
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
            if (sum <= aim) {
                res = max(res, (end - start + 1));
            }
        }
    }

    return res;
}

int maxLengthAwesom_2(vector<int>& arr, int aim) {
    if (arr.size() == 0) {
        return 0;
    }
    int size = static_cast<int>(arr.size());
    vector<int> sums(size);
    vector<int> ends(size);
    sums[size - 1] = arr[size - 1];
    ends[size - 1] = size - 1;

    /* 生成数组 */
    for (int i = size - 2; i >= 0; i--) {
        if (sums[i + 1] < 0) {      // 小于0, 向右扩
            sums[i] = arr[i] + sums[i + 1];
            ends[i] = ends[i + 1];
        }
        else {                      // 大于0, 停止
            sums[i] = arr[i];
            ends[i] = i;
        }
    }

    int rPtr = 0;
    int sum = 0;
    int len = 0;
    for (int start = 0; start < size; start++) {
        while ((rPtr < size) && (sum + sums[rPtr] <= aim)) {
            sum += sums[rPtr];
            rPtr = ends[rPtr] + 1;
        }
        // 下一次start++, rPtr > start, 要把当前值移出, rPtr<=start, 说明窗口内没有元素, 不需要减去当前值
        sum -= rPtr > start ? arr[start] : 0;   // 出窗口
        len = max(len, rPtr - start);
        rPtr = max(rPtr, start + 1);            // 扩不出去, rPtr跳到下一位置
    }

    return len;
}

int main() {
    //vector<int> arr = { 1, 2, 3, 100, 4, 1, 1, 1, 1, 1, 1 };
    vector<int> arr;
    generatorRandomArray(arr, 50, 5);
    printVector(arr);

    cout << maxLengthAwesom_1(arr, 20) << endl;
    cout << maxLengthAwesom_2(arr, 20) << endl;

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
        //temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        //if (temp == 0) {
        //    continue;
        //}
        //else {
        //    vt.push_back(temp);
        //}
        vt.push_back(temp);
    }
}