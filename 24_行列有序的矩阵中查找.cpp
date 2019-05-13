#include <iostream>
#include <vector>
using namespace std;
void generateMatrix(vector<vector<int>> &matrix);
void printMatrix(vector<vector<int>> matrix);

/*
    给定一个由N*M的整数型矩阵matrix和一个整数K, matrix的每一行和每一列都是排好序的. 
    实现一个函数, 判断K是否在matrix中. 要求时间复杂度O(N+M), 额外空间复杂度O(1)
    例如: 如果输入如下4 X 4矩阵: { 0,  1,  2,  5,
                                   2,  3,  4,  7,
                                   4,  4,  4,  8,
                                   5,  7,  7,  9 }

*/

bool findK(vector<vector<int>> &matrix, int k) {
    int row = 0;
    int col = matrix[0].size() - 1;

    while ((row < matrix.size()) && (col >= 0)) {
        if (matrix[row][col] == k) {
            return true;
        }
        else if (matrix[row][col] > k) {
            col--;
        }
        else {
            row++;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> matrix;
    int k = 90;
    generateMatrix(matrix);
    printMatrix(matrix);
    if (findK(matrix, k))
        cout << "find: " << k << endl;
    else
        cout << "not find: " << k << endl;
    return 0;
}

void generateMatrix(vector<vector<int>> &matrix) {
    vector<int> temp;
    temp.push_back(0);
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(5);
    matrix.push_back(temp);
    temp[0] = 2;
    temp[1] = 3;
    temp[2] = 4;
    temp[3] = 7;
    matrix.push_back(temp);
    temp[0] = 4;
    temp[1] = 4;
    temp[2] = 4;
    temp[3] = 8;
    matrix.push_back(temp);
    temp[0] = 5;
    temp[1] = 7;
    temp[2] = 7;
    temp[3] = 9;
    matrix.push_back(temp);
}

void printMatrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}