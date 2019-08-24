#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

int maxLength_1(vector<int>& arr, int aim) {
    int L = 0;
    int R = 0;
    int res = 0;
    int sum = arr[0];
    while (R < arr.size()) {
        if (sum == aim) {
            res = max(res, R - L + 1);
            sum -= arr[L++];
        }
        else if (sum > aim) {
            sum -= arr[L++];
        }
        else {
            R++;
            if (R == arr.size())    break;
            sum += arr[R];
        }
    }
    return res;
}

/* 暴力解 */
int maxLength_2(vector<int>& arr, int aim) {
    size_t len = 0;
    for (size_t start = 0; start < arr.size(); start++) {
        int sum = 0;
        for (size_t end = start; end < arr.size(); end++) {
            sum += arr[end];
            if (sum == aim) {
                len = (end - start + 1) > len ? (end - start + 1) : len;
            }
        }
    }
    return len;
}

int main() {
    vector<int> arr;
    generatorRandomArray(arr, 5, 5);
    //vector<int> arr = { 1, 2, 1, 1, 1 };
    printVector(arr);

    cout << maxLength_1(arr, 3) << endl;
    cout << maxLength_1(arr, 3) << endl;

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
        vt.push_back(temp);
    }
}