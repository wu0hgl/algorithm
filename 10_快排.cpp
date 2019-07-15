#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    ����
*/

void partition(vector<int> &arr, int left, int right, vector<int> &out) {
    int leftPtr = left - 1; // leftPtrָ��С��arr[right]���ұ߽�
    int rightPtr = right;   // rightPtrָ�����arr[right]����߽�
    int ctPtr = left;
    while (ctPtr < rightPtr) {
        if (arr[ctPtr] < arr[right])
            swap(arr[ctPtr++], arr[++leftPtr]);
        else if (arr[ctPtr] > arr[right])
            swap(arr[ctPtr], arr[--rightPtr]);
        else
            ctPtr++;
    }
    swap(arr[right], arr[rightPtr]);
    out.push_back(leftPtr + 1);
    out.push_back(rightPtr - 1);
}

void quickSort(vector<int> &vt, int left, int right) {
    if (left < right) {
        int random = left + int((rand() % (right - left + 1)));
        swap(vt[random], vt[right]);
        vector<int> temp;
        partition(vt, left, right, temp);
        quickSort(vt, left, temp[0] - 1);
        quickSort(vt, temp[1] + 1, right);
    }
}


int main() {
    //vector<int> arr;
    //srand(static_cast<int>(time(NULL)));
    //generatorRandomArray(arr, 20, 200);
    vector<int> arr = { 3, 3, 3 };
    printVector(arr);
    quickSort(arr, 0, arr.size() - 1);
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

    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // �������������
        //temp = static_cast<int>(rand() % (range + 1));          // �����������
        vt.push_back(temp);
    }
}
