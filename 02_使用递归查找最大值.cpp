#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

/*
    使用递归查找数组中的最大值
*/

void printArr(int *a, int len) {
    for (auto i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int func_1(int *a, int left, int right) {
    if (left == right)
        return a[left];

    int mid = left + ((right - left) >> 1);
    int maxLeft = func_1(a, left, mid);
    int maxRight = func_1(a, mid + 1, right);

    return max(maxLeft, maxRight);      // 库函数
}

int main() {
    int arr[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arr[i] = static_cast<int>(rand() % 100);
    }
    printArr(arr, 10);
    
    cout << func_1(arr, 0, 10) << endl;

    return 0;
}