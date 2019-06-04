#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
    一个数组arr, 和一个整数aim. 如果可以任意选择arr中的数字, 能不能累加得到aim, 返回true或者false
*/

void printArr(vector<vector<bool>> &matrix);

bool isSum_1(vector<int> &arr, int i, int sum, int aim) {
    if (i == arr.size()) {
        return sum == aim;      // base case
    }
    /* 要当前数字||不要当前数字 */
    return isSum_1(arr, i + 1, sum, aim) || isSum_1(arr, i + 1, sum + arr[i], aim);
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

    vector<vector<bool>> matrix;
    int row = arr.size();
    int col = sum;

    /* 建表 */
    matrix.resize(row + 1);
    for (int i = 0; i <= row; i++) {
        matrix[i].resize(col + 1);
    }

    /* 最后一行为base case可直接计算 */
    for (int i = 0; i <= col; i++) {
        matrix[row][i] = false;
    }
    matrix[row][aim] = true;

    for (int i = row - 1; i >= 0; i--) {
        for (int j = 0; j <= col; j++) {
            matrix[i][j] = (j + arr[i] <= col) ?    // 防止数组越界
                (matrix[i][j] = matrix[i + 1][j] || (matrix[i + 1][j + arr[i]])) : (matrix[i][j] = matrix[i + 1][j]);
        }
    }
    printArr(matrix);
    
    return matrix[0][0];
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
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
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