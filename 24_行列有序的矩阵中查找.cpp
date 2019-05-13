#include <iostream>
#include <vector>
using namespace std;
void generateMatrix(vector<vector<int>> &matrix);
void printMatrix(vector<vector<int>> matrix);

/*
    ����һ����N*M�������;���matrix��һ������K, matrix��ÿһ�к�ÿһ�ж����ź����. 
    ʵ��һ������, �ж�K�Ƿ���matrix��. Ҫ��ʱ�临�Ӷ�O(N+M), ����ռ临�Ӷ�O(1)
    ����: �����������4 X 4����: { 0,  1,  2,  5,
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