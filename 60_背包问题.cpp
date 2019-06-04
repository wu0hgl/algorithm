#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void printArr(vector<vector<int>> &matrix);
/*
    给定两个数组w和v, 两个数组长度相等, w[i]表示第i件商品的重量, v[i]表示第i件商品的价值. 
    再给定一个整数bag, 要求你挑选商品的重量加起来一定不能超过bag, 返回满足这个条件下, 你能获得的最大价值
*/

int process1(vector<int> &weights, vector<int> &values, int begin, int value, int bag) {
    if (bag < 0) {
        return 0;
    }
    if (begin == weights.size()) {
        return value;
    }
    return max(process1(weights, values, begin + 1, value, bag), 
        process1(weights, values, begin + 1, value + values[begin], bag - weights[begin]));
}
int maxValue1(vector<int> &c, vector<int> &p, int bag) {
    return process1(c, p, 0, 0, bag);
}

int process2(vector<int> &weights, vector<int> &values, int i, int alreadyweight, int bag) {
    if (alreadyweight > bag) {
        return -values[i - 1];
    }
    if (i == weights.size()) {
        return 0;
    }

    int val1 = process2(weights, values, i + 1, alreadyweight, bag);
    int val2 = values[i] + process2(weights, values, i + 1, alreadyweight + weights[i], bag);   // 

    return max(val1, val2);
}
int maxValue2(vector<int> &c, vector<int> &p, int bag) {
    return process2(c, p, 0, 0, bag);
}

int maxValue3(vector<int> & c, vector<int> & p, int bag) {
    vector<vector<int>> dp;
    dp.resize(c.size() + 1);
    for (int i = 0; i <= c.size(); i++) {
        dp[i].resize(bag + 1);
    }
    
    for (int i = c.size() - 1; i >= 0; i--) {
        for (int j = bag; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j];
            if (j + c[i] <= bag) {
                dp[i][j] = max(dp[i][j], p[i] + dp[i + 1][j + c[i]]);
            }
        }
        //printArr(dp);
    }
    //printArr(dp);
    return dp[0][0];
}

int main() {
    vector<int> c = { 3, 2, 4, 7 };
    vector<int> p = { 5, 6, 3, 19 };
    int bag = 11;

    //vector<int> c = { 1, 2};
    //vector<int> p = { 4, 5,};
    //int bag = 2;

    cout << maxValue1(c, p, bag) << endl;
    cout << maxValue2(c, p, bag) << endl;
    cout << maxValue3(c, p, bag) << endl;

    return 0;
}

void printArr(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "====================" << endl;
}