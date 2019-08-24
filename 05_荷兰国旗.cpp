#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    给定一个数组arr, 和一个数num,
    请把小于num的数放在数组的左边, 等于num的数放在数组的中间, 大于num的数放在数组的右边
    要求额外空间复杂度O(1), 时间复杂度O(N)
*/

void func(vector<int> &arr, int left, int right, int aim) {
    int rightPtr = right + 1;   // 当前所指的位置就是大于aim数的左边界
    int leftPtr = left - 1;     // 当前所指的位置就是小于aim数的右边界
    int index = left;
    while (index < rightPtr) {  // 这里不能有等于号, 因为rightPtr所指位置就是大于aim的左边界
        if (arr[index] < aim) 
            swap(arr[++leftPtr], arr[index++]);
        else if (arr[index] > aim) 
            swap(arr[index], arr[--rightPtr]);  // 从右边界交换过来的数组还未与aim比较, 所以index不变
        else 
            index++;
        //printVector(arr);
    }
}

int main() {
    //vector<int> arr;
    //generatorRandomArray(arr, 30, 10);
    vector<int> arr = { 1, 4, 8 };
    printVector(arr);

    func(arr, 0, arr.size() - 1, 4);
    printVector(arr);

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
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (maxValue + 1));                                         // 随机生成正数
        if (temp == 0) {
            continue;
        }
        else {
            vt.push_back(temp);
        }
    }
}