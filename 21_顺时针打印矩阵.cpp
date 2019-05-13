#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector<int>> matrix);
void generateMatrix(vector<vector<int>> &matrix);

/*
    给定一个整型矩阵matrix, 按照从外向里以顺时针的顺序依次打印出每一个数字. 
    例如: 如果输入如下4 X 4矩阵：1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
          则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
*/

void printFunc(vector<vector<int> > matrix, vector<int> &out, int x_1, int y_1, int x_2, int y_2) {
    if (x_1 == x_2) {               // 一行
        for (int i = 0; i < (y_2 - y_1 + 1); i++)
            out.push_back(matrix[x_1][y_1 + i]);
    }
    else if (y_1 == y_2) {          // 一列
        for (int i = 0; i < (x_2 - x_1 + 1); i++)
            out.push_back(matrix[x_1 + i][y_1]);
    }
    else {
        /*
        int ctR = x_1;
        int ctC = y_1;
        while (ctC != y_2) {
        out.push_back(matrix[x_1][ctC]);
        ctC++;
        }
        while (ctR != x_2) {
        out.push_back(matrix[ctR][y_2]);
        ctR++;
        }
        while (ctC != y_1) {
        out.push_back(matrix[x_2][ctC]);
        ctC--;
        }
        while (ctR != x_1) {
        out.push_back(matrix[ctR][y_1]);
        ctR--;
        }
        */

        for (int i = y_1; i < y_2; i++)
            out.push_back(matrix[x_1][i]);
        for (int i = x_1; i < x_2; i++)
            out.push_back(matrix[i][y_2]);
        for (int i = y_2; i > y_1; i--)
            out.push_back(matrix[x_2][i]);
        for (int i = x_2; i > x_1; i--)
            out.push_back(matrix[i][y_1]);
    }

    //for (int i = 0; i < out.size(); i++)
    //    cout << out[i] << " ";
    //cout << endl;
}

vector<int> printFunc(vector<vector<int> > matrix) {
    vector<int> ret;
    if (matrix.size() < 1)
        return ret;
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = matrix.size() - 1;
    int y_2 = matrix[0].size() - 1;
    while ((x_2 >= x_1) && (y_2 >= y_1)) {
        printFunc(matrix, ret, x_1++, y_1++, x_2--, y_2--);
    }

    return ret;
}



int main() {
    vector<vector<int>> matrix;
    generateMatrix(matrix);
    printMatrix(matrix);
    cout << "--------------------" << endl;
    vector<int> ret;
    ret = printFunc(matrix);
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i] << " ";
    cout << endl;

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