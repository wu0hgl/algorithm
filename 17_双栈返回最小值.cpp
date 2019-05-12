#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <queue>
#include <functional>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

class Solution {
public:
    stack<int> m_min;
    stack<int> m_sk;

    void push(int value) {
        if (m_min.empty()) {
            m_min.push(value);
            m_sk.push(value);
        }
        else {
            if (value > m_min.top()) {
                m_min.push(m_min.top());
                m_sk.push(value);
            }
            else {
                m_min.push(value);
                m_sk.push(value);
            }
        }
    }

    void pop() {
        m_sk.pop();
        m_min.pop();
    }
    int top() {
        return m_sk.top();
    }

    int min() {
        return m_min.top();
    }
};


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    printVector(arr);

    Solution s;
    for (int i = 0; i < arr.size(); i++) {
        s.push(arr[i]);
        cout << s.min() << endl;
    }

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
        //temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
        //Insert_2(temp);
    }
}