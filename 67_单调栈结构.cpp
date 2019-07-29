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
    vector<vector<int>> res(arr.size());
    //if (arr.size() == 0) {
    //    return res;
    //}
    list<int> ls;   // 里面存放minSK弹出的index
    int left = 0;
    int right = 0;
    stack<list<int>> minSK;

    for (size_t i = 0; i < arr.size(); i++) {
        while ((!minSK.empty()) && (arr[minSK.top().front()] > arr[i])) {
            ls = minSK.top();
            minSK.pop();
            left = minSK.empty() ? -1 : minSK.top().back(); // 取位于下面位置的列表中, 最晚加入的那个
            right = i;                                      // 使当前list弹出的index
            for (auto index : ls) {
                res[index].push_back(left);
                res[index].push_back(right);
            }
        }

        if ((!minSK.empty()) && (arr[minSK.top().front()] == arr[i])) {
            minSK.top().push_back(i);
        }
        else {
            list<int> ls;
            ls.push_back(i);
            minSK.push(ls);
        }
    }

    while (!minSK.empty()) {
        ls = minSK.top();
        minSK.pop();
        left = minSK.empty() ? -1 : minSK.top().back();
        right = -1;
        for (auto index : ls) {
            res[index].push_back(left);
            res[index].push_back(right);
        }
    }

    return res;
}

/* 不可重复 */
vector<vector<int>> getNearLessNoRepeat(vector<int>& arr) {
    vector<vector<int>> res;
    //if (arr.size() == 0) {
    //    return res;
    //}

    res.resize(arr.size());
    int index = 0;
    int right = 0;
    int left = 0;

    stack<int> minSK;
    vector<int> temp(2);

    for (size_t i = 0; i < arr.size(); i++) {
        /* 栈从小向大增长 */
        while ((!minSK.empty()) && (arr[minSK.top()] > arr[i])) {
            index = minSK.top();
            minSK.pop();
            right = i;                                  // i比minSK.top小, 使index弹出来
            left = minSK.empty() ? -1 : minSK.top();    // popIndex下面的值, 比arr[i]小
            temp[0] = left;
            temp[1] = right;
            res[index] = temp;
        }

        minSK.push(i);
    }

    /* 弹出栈 */
    while (!minSK.empty()) {
        index = minSK.top();
        minSK.pop();
        left = minSK.empty() ? -1 : minSK.top();    // 栈的下面的值
        right = -1;                                 // 出栈最右边的值都是-1, 因为没有使index弹出的元素
        temp[0] = left;
        temp[1] = right;
        res[index] = temp;
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
        
        /* 查找左边最近比cur小的数 */
        int cur = i - 1;    
        while (cur >= 0) {
            if (arr[cur] < arr[i]) {
                leftLessIndex = cur;
                break;
            }
            cur--;
        }

        /* 查找右边最近比cur小的数 */
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
    //vector<int> arr = { 4, 1, 1, 1, 8 };
    vector<vector<int>> res;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 5);
    printVector(arr);

    res = rightWay(arr);
    printVector(arr, res);
    cout << "=============================" << endl;
    //res = getNearLessNoRepeat(arr);
    //printVector(arr, res);
    //cout << "=============================" << endl;
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