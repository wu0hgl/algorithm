#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

/*
����һ������arr, ��һ����num,
���С��num����������������, ����num��������������м�, ����num��������������ұ�
Ҫ�����ռ临�Ӷ�O(1), ʱ�临�Ӷ�O(N)
*/

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void func(vector<int> &arr, int left, int right, int num) {
    int rightPtr = right + 1;
    int leftPtr = left - 1;
    int index = left;
    while (index < rightPtr) {
        if (arr[index] < num) {
            swap(arr[++leftPtr], arr[index++]);
        }
        else if (arr[index] > num) {
            swap(arr[index], arr[--rightPtr]);
        }
        else {
            index++;
        }
    }
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    for (int i = 0; i < 20; i++) {
        arr.push_back(static_cast<int>(rand() % 10));
    }
    printVector(arr);
    func(arr, 0, arr.size() - 1, 4);
    printVector(arr);

    return 0;
}