#include <iostream>
#include <vector>
using namespace std;

/*
    һ��������ֻ��0��1����ֵ, ÿ��λ�ö����Ժ��Լ������������ĸ�λ������, �����һƬ1����һ��, ������ֽ���һ����, 
    ��һ���������ж��ٸ���
*/

void printArr(vector<vector<int>> &arr) {
    for (int i = 0;  i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void infect(vector<vector<int>> &arr, int i, int j, int row, int col) {
    if ((i < 0) || (i >= row) || (j < 0) || (j >= col) || (arr[i][j] != 1)) {
        return;
    }
    arr[i][j] = 2;
    infect(arr, i + 1, j, row, col);
    infect(arr, i - 1, j, row, col);
    infect(arr, i, j + 1, row, col);
    infect(arr, i, j - 1, row, col);
}

int countIsLands(vector<vector<int>> arr) {
    if (arr.size() == 0 || arr[0].size() == 0) {
        return 0;
    }
    int row = arr.size();
    int col = arr[0].size();
    int res = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 1) {
                res++;
                infect(arr, i, j, row, col);
            }
        }
    }
    //printArr(arr);
    return res;
}

int main() {
    vector<vector<int>> arr_1 = { 
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0, 1, 1, 1, 0 },
    { 0, 1, 1, 1, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
    cout << countIsLands(arr_1) << endl;

    vector<vector<int>> arr_2 = { 
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 1, 1, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 0, 0, 0, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
    cout << countIsLands(arr_2) << endl;

    return 0;
}