#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组arr, 可以任意把arr分成很多不相容的子数组. 
    求: 分出来的子数组中, 异或和为0的子数组最多是多少
*/

int mostEOR_1(vector<int>& arr) {
    int res = 0;
    int xor = 0;
    vector<int> dp = vector<int>(arr.size(), 0);
    unordered_map<int, int> xMap;     // key: 某一个异或和, value: 或和上次出现的位置
    xMap[0] = -1;
    for (size_t i = 0; i < arr.size(); i++) {
        xor ^= arr[i];
        if (xMap.count(xor)) {      // 异或和之前出现过
            int pre = xMap[xor];    // 之前出现过的位置     
            dp[i] = (pre == -1 ? 1 : (dp[pre] + 1));
        }
        if (i > 0) {
            dp[i] = max(dp[i - 1], dp[i]);
        }
        xMap[xor] = i;              // 更新unordered_map
        res = max(res, dp[i]);
    }

    return res;
}

int most(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }

    int eor = 0;
    vector<int> dp = vector<int>(arr.size(), 0);
    unordered_map<int, int> xMap;
    xMap[0] = -1;
    dp[0] = (arr[0] == 0 ? 1 : 0);
    xMap[arr[0]] = 0;
    for (size_t i = 1; i < arr.size(); i++) {
        eor ^= arr[i];
        if (xMap.count(eor)) {
            int pre = xMap[eor];
            dp[i] = (pre == -1 ? 1 : (dp[pre] + 1));
        }
        dp[i] = max(dp[i - 1], dp[i]);
        xMap[eor] = i;
    }
    return dp[dp.size() - 1];
}

int mostEOR_2(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }

    vector<int> eors = vector<int>(arr.size(), 0);
    int eor = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        eor ^= arr[i];
        eors[i] = eor;
    }

    vector<int> dp = vector<int>(arr.size(), 0);
    dp[0] = (arr[0] == 0 ? 1 : 0);
    for (size_t i = 1; i < arr.size(); i++) {
        dp[i] = (eors[i] == 0 ? 1 : 0);
        for (size_t j = 0; j < i; j++) {
            if ((eors[i] ^ eors[j]) == 0) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        dp[i] = max(dp[i], dp[i - 1]);
    }
    return dp[dp.size() - 1];
}

//int most(vector<int>& arr) {
//    size_t pos = 0;
//    int ans = 0;
//
//    for (size_t outer = 0; outer < arr.size(); outer++) {
//        int xor = 0;
//        int temp = ans;
//        int temp_2 = pos;
//        while (pos <= outer) {
//            xor ^= arr[pos];
//            pos++;
//            if (xor == 0) {
//                ans++;
//                continue;
//            }
//        }
//
//        if (temp == ans) {  // 没有位置更新, 恢复pos
//            pos = temp_2;
//        }
//    }
//
//    return ans;
//}

int main() {
    vector<int> arr;
    generatorRandomArray(arr, 10, 5);
    //vector<int> arr = { 2, 0, 1, 4, 4 };
    //vector<int> arr = {3, 2, 1, 0, 1, 2, 3, 0};
    printVector(arr);

    cout << mostEOR_1(arr) << endl;
    cout << mostEOR_2(arr) << endl;
    cout << most(arr) << endl;

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
        vt.push_back(temp);
    }
}