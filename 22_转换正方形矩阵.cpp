#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector<int>> matrix);
void generateMatrix(vector<vector<int>> &matrix);

/*
    给定一个整型矩阵matrix, 按照从外向里以顺时针的顺序依次打印出每一个数字.
    例如: 如果输入如下4 X 4矩阵:  { 1,  2,  3,  4,
                                    5,  6,  7,  8, 
                                    9,  10, 11, 12, 
                                    13, 14, 15, 16 }
    转换后: { 13, 9,  5, 1,
              14, 10, 6, 2,
              15, 11, 7, 3,
              16, 12, 8, 4 }
    
*/

void rotateMatrix(vector<vector<int> > &matrix, int x_1, int y_1, int x_2, int y_2) {
    for (int i = 0; i < (x_2 - x_1); i++) {
        int temp = matrix[x_1][y_1 + i];
        matrix[x_1][y_1 + i] = matrix[x_2 - i][y_1];
        matrix[x_2 - i][y_1] = matrix[x_2][y_2 - i];
        matrix[x_2][y_2 - i] = matrix[x_1 + i][y_2];
        matrix[x_1 + i][y_2] = temp;
    }
}

void rotateMatrix(vector<vector<int> > &matrix) {
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = matrix.size() - 1;
    int y_2 = matrix[0].size() - 1;
    while (x_2 >= x_1) {        // 这里等号大于和大于等于没区别, 当x_2==x_1时, 只有一个数, 旋转不旋转都一样
        rotateMatrix(matrix, x_1++, y_1++, x_2--, y_2--);
    }
}

int main() {
    vector<vector<int>> matrix;
    generateMatrix(matrix);
    printMatrix(matrix);
    rotateMatrix(matrix);
    cout << "----------------------" << endl;
    printMatrix(matrix);

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
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 13;
    }
    matrix.push_back(temp);

}