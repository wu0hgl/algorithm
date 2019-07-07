#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);
void printVt(vector<vector<int>> &vt);

/*
    给定数组arr, arr中所有的值都为正数且不重复. 每个值代表一种面值的货币, 每种面值的货币可以使用任意张, 再给定一个整数aim代表要找的钱数. 
    求换钱有多少种方法
    例如:
        arr=[5,10,25,1], aim=0. 组成0元的方法有1种， 就是所有面值的货币都不用。 所以返回1。
        arr=[3,5], aim=2. 任何方法都无法组成2元, 所以返回0
*/

int process_1(vector<int>& arr, size_t index, int aim) {
    int res = 0;
    if (arr.size() == index) {
        res = (aim == 0
               ? 1 
               : 0);       // 终止位置aim不为0, 说明之前选择不是有效方法
    }
    else {
        for (int i = 0; (arr[index] * i <= aim); i++) { // i: 当前货币的多少张
            // index+1: 说明需要下一行的值, aim: 下一行当前位置, -arr[index]*i: 下一行当前位置向左偏移arr[index]*i
            res += process_1(arr, index + 1, (aim - arr[index] * i));
        }
    }
    return res;
}
int coins_1(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim < 0)) {
        return 0;
    }
    return process_1(arr, 0, aim);
}

// key: "index_aim"组成的字符串
// value: index和aim下的返回值
unordered_map<string, int> myMap;
int process_2(vector<int>& arr, int index, int aim) {
    int res = 0;
    if (index == arr.size()) {
        res = (aim == 0 ? 1 : 0);
    }
    else {
        for (int i = 0; (arr[index] * i <= aim); i++) {
            int nextAim = aim - arr[index] * i;
            string key = to_string(index + 1) + "_" + to_string(nextAim);
            if (myMap.count(key)) {
                res += myMap.at(key);
            }
            else {
                res += process_2(arr, index + 1, nextAim);
            }
        }
    }
    myMap.insert(pair<string, int>(to_string(index) + "_" + to_string(aim), res));

    return res;
}
int coins_2(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim < 0)) {
        return 0;
    }
    return process_2(arr, 0, aim);
}

int coins_3(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim < 0)) {
        return 0;
    }

    vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1));   // 递归arr.size() == index, 故dp列数为arr.size()+1
    dp[arr.size()][0] = 1;

    for (int row = arr.size() - 1; row >= 0; row--) {
        for (int col = 0; col <= aim; col++) {
            dp[row][col] = dp[row + 1][col];
            dp[row][col] += col - arr[row] >= 0 ? dp[row][col - arr[row]] : 0;
        }
    }

    return dp[0][aim];
}

int coins_4(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim < 0)) {
        return 0;
    }

    vector<vector<int>> dp(arr.size(), vector<int>(aim + 1));

    // 填写不依赖其他位置的值
    for (size_t i = 0; i < arr.size(); i++) {
        dp[i][0] = 1;
    }
    for (int j = 1; arr[0] * j <= aim; j++) {
        dp[0][arr[0] * j] = 1;
    }

    for (size_t i = 1; i < arr.size(); i++) {
        for (int j = 1; j <= aim; j++) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] += j - arr[i] >= 0 ? dp[i][j - arr[i]] : 0;
        }
    }

    return dp[arr.size() - 1][aim];
}

int coins_5(vector<int>& arr, int aim) {
    if ((arr.size() == 0) || (aim < 0)) {
        return 0;
    }

    vector<int> dp(aim + 1, 0);
    for (int j = 0; arr[0] * j <= aim; j++) {
        dp[arr[0] * j] = 1;
    }
    for (int i = 1; i < arr.size(); i++) {
        for (int j = 1; j <= aim; j++) {
            dp[j] += j - arr[i] >= 0 ? dp[j - arr[i]] : 0;
        }
    }

    return dp[aim];
}

int main() {
    //vector<int> arr = { 5, 3, 2 };
    vector<int> arr;
    generatorRandomArray(arr, 5, 5);
    printVector(arr);

    cout << coins_1(arr, 10) << endl;
    cout << coins_2(arr, 10) << endl;
    cout << coins_3(arr, 10) << endl;
    cout << coins_4(arr, 10) << endl;
    cout << coins_5(arr, 10) << endl;

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void printVt(vector<vector<int>> &vt) {
    for (size_t i = 0; i < vt.size(); i++) {
        for (size_t j = 0; j < vt[0].size(); j++) {
            cout << vt[i][j] << " ";
        }
        cout << endl;
    }
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