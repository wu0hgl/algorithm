#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
void printArr(vector<vector<bool>> &matrix);

/*
    一个数组arr, 和一个整数aim. 如果可以任意选择arr中的数字, 能不能累加得到aim, 返回true或者false
*/

bool isSum_1(vector<int> &arr, int i, int sum, int aim) {
    if (i == arr.size()) {
        return sum == aim;      // base case
    }

    /* 要当前数字||不要当前数字 */
    //bool res_1 = isSum_1(arr, i + 1, sum, aim);
    //bool res_2 = isSum_1(arr, i + 1, sum + arr[i], aim);
    //return res_1 || res_2;

    return (isSum_1(arr, i + 1, sum, aim) 
           || isSum_1(arr, i + 1, sum + arr[i], aim));
}

/* 目前只能处理正数数组, 若含负数数组扩充二维表, 列数扩充负向最小值到正向最大值? */
bool isSum_2(vector<int> &arr, int aim) {
    if (arr.size() == 0) {
        return false;
    }

    int sum = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    if (sum < aim) {
        return false;
    }

    int row = arr.size();
    int col = sum;

    /* 建表 */
    vector<vector<bool>> dp(row + 1, vector<bool>(col + 1));
    //vector<vector<bool>> dp;
    //dp.resize(row + 1);
    //for (int i = 0; i <= row; i++) {
    //    dp[i].resize(col + 1);
    //}

    /* 最后一行为base case可直接计算 */
    for (int i = 0; i <= col; i++) {
        dp[row][i] = false;
    }
    dp[row][aim] = true;

    for (int i = row - 1; i >= 0; i--) {
        for (int j = 0; j <= col; j++) {
            dp[i][j] = (j + arr[i] <= col) ?    // 防止数组越界
                (dp[i][j] = dp[i + 1][j] || (dp[i + 1][j + arr[i]])) : (dp[i][j] = dp[i + 1][j]);
        }
    }
    printArr(dp);
    
    return dp[0][0];
}

int main() {
    vector<int> arr = { 3, 2, 5 };
    int aim = 7;
    cout << isSum_1(arr, 0, 0, aim) << endl;
    cout << "========================" << endl;
    cout << isSum_2(arr, aim) << endl;
    return 0;
}

void printArr(vector<vector<bool>> &matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j]) {
                cout << "T" << " ";
            }
            else {
                cout << "F" << " ";
            }
        }
        cout << endl;
    }
}