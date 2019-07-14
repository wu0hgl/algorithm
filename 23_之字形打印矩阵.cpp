﻿#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector<int>> matrix);
void generateMatrix(vector<vector<int>> &matrix);

/*
    
    给定一个矩阵matrix, 按照"之"字形方式打印这个矩阵
    例如: 如果输入如下4 X 4矩阵:  { 1,  2,  3,  4,
                                    5,  6,  7,  8,
                                    9,  10, 11, 12 }
    输出 1, 2, 5, 9, 6, 3, 4, 7, 10, 11, 8, 12

*/

void printZ(vector<vector<int>> &matrix, int x_1, int y_1, int x_2, int y_2, bool flag) {
    if (flag) {
        while (x_1 != (x_2 + 1))
            cout << matrix[x_1++][y_1--] << " ";    // 下一行, 上一列
    }
    else {
        while (x_2 != (x_1 - 1))
        cout << matrix[x_2--][y_2++] << " ";        // 上一行, 下一列
    }
}

void printZ(vector<vector<int> > &matrix) {
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = 0;
    int y_2 = 0;
    int row = matrix.size();
    int col = matrix[0].size();
    int endRow = matrix.size() - 1;
    int endCol = matrix[0].size() - 1;
    bool flag = false;
    while (x_1 != endRow + 1) {
        printZ(matrix, x_1, y_1, x_2, y_2, flag);
        
        /* 以下左上角与右下角横纵坐标的先后顺序不能改变 */
        x_1 = (y_1 == endCol ? x_1 + 1 : x_1);  // 右上角, 由于y_1的变化引起x_1的变化, 所以先判断y_1
        y_1 = (y_1 == endCol ? y_1 : y_1 + 1);
        y_2 = (x_2 == endRow ? y_2 + 1 : y_2);  // 左下角, 由于x_2的变化引起y_2的变化, 所以先判断x_2
        x_2 = (x_2 == endRow ? x_2 : x_2 + 1);
        
        //y_1 = (y_1 == endCol ? y_1 : y_1 + 1);
        //x_1 = (y_1 == endCol ? x_1 + 1 : x_1);
        //x_2 = (x_2 == endRow ? x_2 : x_2 + 1);
        //y_2 = (x_2 == endRow ? y_2 + 1 : y_2);

        //y_1 = (y_1 + 1 == col ? col - 1 : y_1 + 1);
        //x_1 = (y_1 == col - 1 ? x_1 + 1 : x_1);
        //x_2 = (x_2 + 1 == row ? row - 1 : x_2 + 1);
        //y_2 = (x_2 == row - 1 ? y_2 + 1 : y_2);
        
        flag = !flag;
    }
}

int main() {
    vector<vector<int>> matrix;
    generateMatrix(matrix);
    printMatrix(matrix);
    cout << "----------------------" << endl;
    printZ(matrix);
    //printMatrix(matrix);

    return 0;
}

void printMatrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void generateMatrix(vector<vector<int>> &matrix) {
    vector<int> temp;
    for (int i = 0; i < 4; i++) {
        temp.push_back(i + 1);
    }
    matrix.push_back(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 5;
    }
    matrix.push_back(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 9;
    }
    matrix.push_back(temp);
    //for (int i = 0; i < 4; i++) {
    //    temp[i] = i + 13;
    //}
    //matrix.push_back(temp);
}