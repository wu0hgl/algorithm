#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    快排
*/

void partition(vector<int> &arr, int left, int right, vector<int> &out) {
    int L = left - 1;
    int R = right;
    int ct = left;

    while (ct < R) {
        if (arr[ct] < arr[right]) 
            swap(arr[ct++], arr[++L]);
        else if (arr[ct] > arr[right]) 
            swap(arr[ct], arr[--R]);
        else 
            ct++;
    }
    //printVector(arr);
    swap(arr[R], arr[right]);
    //printVector(arr);
    // 此时L+1与R恰好指向分界点
    out.push_back(L + 1);
    out.push_back(R);
}

void quickSort(vector<int> &vt, int left, int right) {
    if (left < right) {
        int random = left + int((rand() % (right - left + 1)));
        swap(vt[random], vt[right]);
        //printVector(vt);
        vector<int> temp;
        partition(vt, left, right, temp);
        quickSort(vt, left, temp[0] - 1);
        quickSort(vt, temp[1] + 1, right);
    }
}


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 200);
    //vector<int> arr = { 2, 1, 4, 3 };
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
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (range + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}
