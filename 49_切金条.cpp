#include <iostream>
#include <queue>
#include <functional>
using namespace std;

int lessMoney(vector<int> &arr) {
    priority_queue<int, vector<int>, greater<int>> pQ;  // 小根堆
    for (size_t i = 0; i < arr.size(); i++) {
        pQ.push(arr[i]);
    }

    int sum = 0;
    int cur = 0; 
    while (pQ.size() > 1) {
        cur = pQ.top();  pQ.pop();
        cur += pQ.top(); pQ.pop();
        sum += cur;
        pQ.push(cur);
    }

    return sum;
}

struct MinheapComparator {
    bool operator()(int i, int j) {
        return i > j;
    }
};

struct MaxheapComparator {
    bool operator()(int i, int j) {
        return i < j;
    }
};

int main() {
    //vector<int> arr = { 8, 7, 6, 9 };
    vector<int> arr = { 10, 20, 30 };
    cout << lessMoney(arr) << endl;

    vector<int> arrForHeap = { 3, 5, 2, 7, 0, 1, 6, 4 };

    priority_queue<int> max1;                                   // 默认大根堆
    for (int i = 0; i < arrForHeap.size(); i++) {
        max1.push(arrForHeap[i]);
    }
    while (!max1.empty()) {
        cout << max1.top() << " "; max1.pop();
    }
    cout << endl;

    priority_queue<int, vector<int>, MaxheapComparator> max2;   // 大根堆使用比较器
    for (int i = 0; i < arrForHeap.size(); i++) {
        max2.push(arrForHeap[i]);
    }
    while (!max2.empty()) {
        cout << max2.top() << " "; max2.pop();
    }
    cout << endl;

    priority_queue<int, vector<int>, MinheapComparator> minQ2;  // 小根堆使用比较器
    for (int i = 0; i < arrForHeap.size(); i++) {
        minQ2.push(arrForHeap[i]);
    }
    while (!minQ2.empty()) {
        cout << minQ2.top() << " "; minQ2.pop();
    }
    cout << endl;

    return 0;
}