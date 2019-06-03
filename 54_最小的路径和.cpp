#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void printArr(vector<vector<int>> &matrix);
/*
    一个二维数组, 二维数组中的每个数都是正数, 要求从左上角走到右下角, 每一步只能向右或者向下. 沿途经过的数字要累加起来.
    要求返回最小的路径和
*/

// 暴力枚举
// 从左上向右下递归
int minPath1(vector<vector<int>> &matrix, int row, int col) {
    /* 到达右下角 */
    if ((row == matrix.size() - 1) && (col == matrix[0].size() - 1)) {      
        return matrix[row][col];
    }

    /* 到达最下边, 只能向右走, 当前位置到右下角的和 */
    if ((row == matrix.size() - 1) && (col != matrix[0].size() - 1)) {       
        return matrix[row][col] + minPath1(matrix, row, col + 1);
    }

    /* 到达最右边, 只能向下走, 当前位置到右下角的和 */
    if ((row != matrix.size() - 1) && (col == matrix[0].size() - 1)) {
        return matrix[row][col] + minPath1(matrix, row + 1, col);
    }

    //int right = minPath1(matrix, row, col + 1);
    //int down = minPath1(matrix, row + 1, col);

    //return matrix[row][col] + min(right, down);
    return matrix[row][col] + min(minPath1(matrix, row, col + 1), minPath1(matrix, row + 1, col));
}

// 暴力枚举
// 从右下向左上
int minPath2(vector<vector<int>> &matrix, int row, int col) {
    if ((row == 0) && (col == 0)) {
        return matrix[row][col];
    }
    if ((row == 0) && (col != 0)) {
        return matrix[row][col] + minPath2(matrix, row, col - 1);
    }
    if ((row != 0) && (col == 0)) {
        return matrix[row][col] + minPath2(matrix, row - 1, col);
    }
    return matrix[row][col] + min(minPath2(matrix, row, col - 1), minPath2(matrix, row - 1, col));
}

int minPath3(vector<vector<int>> &matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return 0;
    }
    int row = matrix.size();
    int col = matrix[0].size();

    vector<vector<int>> dp;
    dp.resize(row);
    for (int i = 0; i < row; i++) {
        dp[i].resize(col);
    }

    /* 从上向下填表 */
    dp[0][0] = matrix[0][0];
    for (int i = 1; i < row; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }
    printArr(dp);
    for (int j = 1; j < col; j++) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }
    printArr(dp);
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
        }
    }
    printArr(dp);
    return dp[row - 1][col - 1];

    /* 从下向上填表 */
    //dp[row - 1][col - 1] = matrix[row - 1][col - 1];
    //for (int i = row - 1; i > 0; i--) {
    //    dp[i - 1][col - 1] = dp[i][col - 1] + matrix[i - 1][col - 1];
    //}
    //printArr(dp);
    //for (int j = col - 1; j > 0; j--) {
    //    dp[row - 1][j - 1] = dp[row - 1][j] + matrix[row - 1][j - 1];
    //}
    //printArr(dp);

    //for (int i = row - 1; i > 0; i--) {
    //    for (int j = col - 1; j > 0; j--) {
    //        dp[i- 1][j - 1] = matrix[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
    //    }
    //}
    //printArr(dp);
    //return dp[0][0];
}

int main() {
    vector<vector<int>> matrix = {
        {3, 2, 1, 0},
        {7, 5, 0, 1},
        {3, 7, 6, 2}
    };
    
    cout << minPath1(matrix, 0, 0) << endl;
    cout << "========================" << endl;
    cout << minPath2(matrix, matrix.size() - 1, matrix[0].size() - 1) << endl;
    cout << "========================" << endl;
    cout << minPath3(matrix) << endl;

    return 0;
}

void printArr(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}