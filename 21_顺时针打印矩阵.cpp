#include <iostream>
#include <vector>
using namespace std;

/*
    ����һ�����;���matrix, ���մ���������˳ʱ���˳�����δ�ӡ��ÿһ������. 
    ����: �����������4 X 4����1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
          �����δ�ӡ������1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
*/

void printMatrix(vector<vector<int> > matrix, vector<int> &out, int x_1, int y_1, int x_2, int y_2) {
    if (x_1 == x_2) {               // һ��
        for (int i = 0; i < (y_2 - y_1 + 1); i++)
            out.push_back(matrix[x_1][y_1 + i]);
    }
    else if (y_1 == y_2) {          // һ��
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

vector<int> printMatrix(vector<vector<int> > matrix) {
    vector<int> ret;
    if (matrix.size() < 1)
        return ret;
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = matrix.size() - 1;
    int y_2 = matrix[0].size() - 1;
    while ((x_2 >= x_1) && (y_2 >= y_1)) {
        printMatrix(matrix, ret, x_1++, y_1++, x_2--, y_2--);
    }

    return ret;
}

int main() {
    vector<vector<int>> arr;
    vector<int> temp;
    for (int i = 0; i < 4; i++) {
        temp.push_back(i + 1);
    }
    arr.push_back(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 5;
    }
    arr.push_back(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 9;
    }
    arr.push_back(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = i + 13;
    }
    arr.push_back(temp);

    vector<int> ret;
    ret = printMatrix(arr);
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i] << " ";
    cout << endl;

    return 0;
}