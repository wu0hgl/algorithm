#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

int find(vector<int>& arr, int aim) {
    int L = 0;
    int R = arr.size() - 1;

    while (true) {
        int mid = L + ((R - L) >> 1);
        if (L > R){
            return -1;
        }
        else if (arr[mid] == aim) {
            return mid;
        }
        else {
            if (arr[mid] > aim) {
                R = mid - 1;
            }
            else {
                L = mid + 1;
            }
            //cout << mid << " " << arr[mid] << endl;
        }
    }
}

int main() {
    //vector<int> arr = { 6, 6, 0, 5, 1, 6, 9, 9, 8, 1 };
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    sort(arr.begin(), arr.end());
    printVector(arr);
    int pos = find(arr, 5);
    if (pos != -1) {
        cout << arr[pos] << endl;
    }
    else {
        cout << "not found" << endl;
    }

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
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}