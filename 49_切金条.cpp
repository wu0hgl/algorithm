#include <iostream>
#include <queue>
#include <functional>
using namespace std;

/*
    一块金条切成两半, 需要花费和长度数值一样的铜板. 如长度为20的金条, 不管切成长度多大的两半, 都需要花费20个铜板. 
    一群人想分整块金条, 怎么分最省铜板?

    例如, 给定数组{10, 20, 30}, 数组长度代表3个人, 整块金条长度为10+20+30=60. 金条要分成10, 20, 30三个部分. 
    如果先把金条分成10和50, 花费60, 在把长度50的金条分成20和30, 花费50, 一共花费110
    如果先把金条分成30和30, 花费60, 在把长度30的金条分成10和20, 花费30, 一共花费90
*/

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
    cout << lessMoney(arr);
    cout << endl << "==================================" << endl;

    vector<int> arrForHeap = { 3, 5, 2, 7, 0, 1, 6, 4 };

    priority_queue<int> max1;                                   // 默认大根堆
    for (int i = 0; i < arrForHeap.size(); i++) {
        max1.push(arrForHeap[i]);
    }
    while (!max1.empty()) {
        cout << max1.top() << " "; max1.pop();
    }
    cout << endl << "==================================" << endl;

    priority_queue<int, vector<int>, MaxheapComparator> max2;   // 大根堆使用比较器
    for (int i = 0; i < arrForHeap.size(); i++) {
        max2.push(arrForHeap[i]);
    }
    while (!max2.empty()) {
        cout << max2.top() << " "; max2.pop();
    }
    cout << endl << "==================================" << endl;

    priority_queue<int, vector<int>, MinheapComparator> minQ2;  // 小根堆使用比较器
    for (int i = 0; i < arrForHeap.size(); i++) {
        minQ2.push(arrForHeap[i]);
    }
    while (!minQ2.empty()) {
        cout << minQ2.top() << " "; minQ2.pop();
    }
    cout << endl << "==================================" << endl;

    return 0;
}