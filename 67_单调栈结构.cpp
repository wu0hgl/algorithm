#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <ctime>
using namespace std;
void printVector(vector<int> &vt);
void printVector(vector<int> arr, vector<vector<int>> &vt);
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);

/*
    解决数组中所有数, 左边距离它最近比它小/大的数, 右边距离它最近比它小/大的数. 要求O(N)
*/

/* 可重复 */
vector<vector<int>> getNearLessRepeat(vector<int>& arr) {
    int len = static_cast<int>(arr.size());
    vector<vector<int>> res;
    res.resize(len);
    stack<list<int>> sk;

    for (int i = 0; i < len; i++) {
        while ((!sk.empty()) && (arr[sk.top().front()] > arr[i])) {
            list<int> popIs = sk.top();
            sk.pop();
            // 取位于下面位置的列表中, 最晚加入的那个
            int leftLessIndex = sk.empty()
                ? -1
                : sk.top().back();
            for (auto popi : popIs) {
                res[popi].push_back(leftLessIndex);
                res[popi].push_back(i);
            }
        }
        if ((!sk.empty()) && (arr[sk.top().front()] == arr[i])) {
            sk.top().push_back(i);
        }
        else {
            list<int> ls;
            ls.push_back(i);
            sk.push(ls);
        }
    }
    while (!sk.empty()) {
        list<int> popIs = sk.top();
        sk.pop();
        // 取位于下面位置的列表中, 最晚加入的那个
        int leftLessIndex = sk.empty()
            ? -1
            : sk.top().back();
        for (auto popi : popIs) {
            res[popi].push_back(leftLessIndex);
            res[popi].push_back(-1);
        }
    }

    return res;
}

/* 不可重复 */
vector<vector<int>> getNearLessNoRepeat(vector<int>& arr) {
    int len = static_cast<int>(arr.size());
    vector<vector<int>> res;
    res.resize(len);
    stack<int> sk;

    /* 压栈 */
    for (int i = 0; i < len; i++) {
        /* 栈从小向大增长 */
        while ((!sk.empty()) && (arr[sk.top()] > arr[i])) {
            int popIndex = sk.top();
            sk.pop();
            int leftLessIndex = sk.empty() ? -1 : sk.top();
            res[popIndex].push_back(leftLessIndex); // popIndex下面的值
            res[popIndex].push_back(i);             // 使popIndex弹出来的值
        }
        sk.push(i);
    }
    
    /* 弹出栈 */
    while (!sk.empty()) {
        int popIndex = sk.top();
        sk.pop();
        int leftLessIndex = sk.empty() ? -1 : sk.top();
        res[popIndex].push_back(leftLessIndex);
        res[popIndex].push_back(-1);                // 出栈最右边的值都是-1, 因为没有使popIndex弹出的元素
    }

    return res;
}

/* 暴力解 */
vector<vector<int>> rightWay(vector<int> &arr) {
    int len = static_cast<int>(arr.size());
    vector<vector<int>> res;
    res.resize(len);
    for (int i = 0; i < len; i++) {
        int leftLessIndex = -1;
        int rightLessIndex = -1;
        
        /* 查找左边最小值 */
        int cur = i - 1;    
        while (cur >= 0) {
            if (arr[cur] < arr[i]) {
                leftLessIndex = cur;
                break;
            }
            cur--;
        }

        /* 查找右边最小值 */
        cur = i + 1;
        while (cur < len) {
            if (arr[cur] < arr[i]) {
                rightLessIndex = cur;
                break;
            }
            cur++;
        }

        res[i].push_back(leftLessIndex);
        res[i].push_back(rightLessIndex);
    }

    return res;
}

int main() {
    vector<int> arr;
    //vector<int> arr = { 4, 1, 5, 6, 8 };
    vector<vector<int>> res;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 5);
    printVector(arr);

    res = rightWay(arr);
    printVector(arr, res);
    cout << "=============================" << endl;
    //res = getNearLessNoRepeat(arr);
    //printVector(arr, res);
    cout << "=============================" << endl;
    res = getNearLessRepeat(arr);
    printVector(arr, res);

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void printVector(vector<int> arr, vector<vector<int>> &vt) {
    for (int outer = 0; outer < static_cast<int>(arr.size()); outer++) {
        cout << arr[outer] << "\t";
        for (int inner = 0; inner < static_cast<int>(vt[outer].size()); inner++) {
            if (vt[outer][inner] == -1) {
                cout << -1 << "\t";
            }
            else {
                cout << arr[vt[outer][inner]] << "\t";
            }
        }
        cout << endl;
    }
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