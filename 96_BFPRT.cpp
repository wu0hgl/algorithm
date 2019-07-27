#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int select(vector<int>& arr, int begin, int end, int i);

void insertionSort(vector<int> arr, int begin, int end) {
    for (int i = begin + 1; i != end + 1; i++) {
        for (int j = i; j != begin; j--) {
            if (arr[j - 1] > arr[j]) {
                swap(arr[j - 1], arr[j]);
            }
            else {
                break;
            }
        }
    }
}

int getMedian(vector<int> arr, int begin, int end) {
    insertionSort(arr, begin, end);
    int sum = end + begin;
    int mid = (sum / 2) + (sum % 2);
    return arr[mid];
}

int medianOfMedians(vector<int> arr, int begin, int end) {
    int num = end - begin + 1;
    int offset = num % 5 == 0 ? 0 : 1;
    vector<int> mArr(num / 5 + offset);
    for (int i = 0; i < mArr.size(); i++) {
        int beginI = begin + i * 5;
        int endI = beginI + 4;
        mArr[i] = getMedian(arr, beginI, min(end, endI));
    }
    return select(mArr, 0, mArr.size() - 1, mArr.size() / 2);
}

vector<int> partition(vector<int> arr, int begin, int end, int pivotValue) {
    int small = begin - 1;
    int cur = begin;
    int big = end + 1;
    while (cur != big) {
        if (arr[cur] < pivotValue) {
            swap(arr[++small], arr[cur++]);
        }
        else if (arr[cur] > pivotValue) {
            swap(arr[cur], arr[--big]);
        }
        else {
            cur++;
        }
    }
    vector<int> range(2);
    range[0] = small + 1;
    range[1] = big - 1;
    return range;
}

int select(vector<int>& arr, int begin, int end, int i) {
    if (begin == end) {
        return arr[begin];
    }

    int pivot = medianOfMedians(arr, begin, end);
    vector<int> pivotRange = partition(arr, begin, end, pivot);
    if (i >= pivotRange[0] && i <= pivotRange[1]) {
        return arr[i];
    }
    else if (i < pivotRange[0]) {
        return select(arr, begin, pivotRange[0] - 1, i);
    }
    else {
        return select(arr, pivotRange[1] + 1, end, i);
    }
}

int getMinKthByBFPRT(vector<int> arr, int k) {
    return select(arr, 0, arr.size() - 1, k - 1);
}

vector<int> getMinKNumsByBFPRT(vector<int>& arr, int k) {
    if ((k < 1) || (k > arr.size())) {
        return vector<int>();
    }

    int minKth = getMinKthByBFPRT(arr, k);  
    vector<int> res(k);
    int index = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] < minKth) {
            res[index++] = arr[i];
        }
    }
    for (; index != res.size(); index++) {
        res[index] = minKth;
    }

    return res;
}

int main() {
    vector<int> arr = { 6, 9, 1, 3, 1, 2, 2, 5, 6, 1, 3, 5, 9, 7, 2, 5, 6, 1, 9 };
    vector<int> ret = getMinKNumsByBFPRT(arr, 10);

    for (auto i : ret) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}