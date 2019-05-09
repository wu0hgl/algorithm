#include<iostream>
#include <ctime>
#include<vector>
using namespace std;

int merge(vector<int> &vt, int left, int mid, int right) {
    int leftPtr = left;
    int rightPtr = mid + 1;
    vector<int> temp;
    int res = 0;
    while ((leftPtr <= mid) && (rightPtr <= right)) {
        res += (vt[leftPtr] > vt[rightPtr] ? (right - rightPtr + 1) : 0);
        /*
        if (vt[leftPtr] > vt[rightPtr]) {
            int cur = rightPtr;
            for (int i = 0; i <= right; i++) {
                cout << vt[leftPtr] << " " << vt[cur] << endl;
            }
        }
        */
        temp.push_back((vt[leftPtr] > vt[rightPtr] ? vt[leftPtr++] : vt[rightPtr++]));
    }
    while (leftPtr <= mid)
        temp.push_back(vt[leftPtr++]);
    while (rightPtr <= right)
        temp.push_back(vt[rightPtr++]);
    for (int i = 0; i < temp.size(); i++) {
        vt[left + i] = temp[i];
    }
    return res;
}

int mergeSort(vector<int> &vt, int left, int right) {
    if (left == right)
        return 0;
    int mid = left + ((right - left) >> 1);
    return (mergeSort(vt, left, mid)
        + mergeSort(vt, mid + 1, right)
        + merge(vt, left, mid, right));
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

int main() {
    vector<int> arr;
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        arr.push_back(static_cast<int>(rand() % 10));
    }
    printVector(arr);
    int sum = mergeSort(arr, 0, arr.size() - 1);
    printVector(arr);
    cout << "����Ը���: " << sum << endl;

    return 0;
}