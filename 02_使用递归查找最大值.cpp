#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    使用递归查找数组中的最大值
*/

int process(vector<int> a, int left, int right) {
    if (left == right)
        return a[left];

    int mid = left + ((right - left) >> 1);
    int maxLeft = process(a, left, mid);
    int maxRight = process(a, mid + 1, right);

    return max(maxLeft, maxRight);      // 库函数
}
int findMax(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }

    return process(arr, 0, static_cast<int>(arr.size() - 1));
}

int main() {
    vector<int> arr;
    generatorRandomArray(arr, 30, 100);
    printVector(arr);
    
    cout << findMax(arr) << endl;

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    srand(static_cast<int>(time(NULL)));
    for (int i = 0; i < len; i++) {
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        if (temp == 0) {
            continue;
        }
        else {
            vt.push_back(temp);
        }
    }
}