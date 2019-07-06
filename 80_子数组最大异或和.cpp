#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <memory>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

// 时间复杂度O(N^3), 三个for循环没太懂什么意思, 完全可以简化为两个for
int getMaxE_1(vector<int> &arr) {
    int maxValue = INT_MIN;
    for (size_t end = 0; end < arr.size(); end++) {
        for (size_t start = 0; start <= end; start++) {
            int res = 0;
            for (size_t cur = start; cur <= end; cur++) {
                res ^= arr[cur];
            }
            maxValue = max(maxValue, res);
        }
    }

    return maxValue;
}

// 时间复杂度O(N^2), 
int getMaxE_2(vector<int> &arr) {
    if (arr.size() == 0) {
        return 0;
    }
    int maxValue = INT_MIN;
    for (size_t start = 0; start < arr.size(); start++) {
        int eor = 0;
        for (size_t j = start; j < arr.size(); j++) {
            eor ^= arr[j];
            maxValue = max(maxValue, eor);
        }
    }

    return maxValue;
}

/* 时间复杂度O(N^2), 空间换时间 */
int getMaxE_3(vector<int> &arr) {
    int maxValue = INT_MIN;
    vector<int> dp(arr.size(), 0);              // dp[i]记录0~i的异或结果
    int eor = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        eor ^= arr[i];                          // eor异或0~i的结果 
        maxValue = max(maxValue, eor);          // 得到0~i的异或结果与全局变量比较是否最大
        for (size_t start = 1; start <= i; start++) {   // 依次比较从0..i的异或结果, 外层for从0开始, 内层从1开始
            // curEor: start~i的异或结果
            int curEor = eor ^dp[start - 1];    // dp[i]记录0~i的异或结果, 当前异或结果^ 0~i的异或结果
            maxValue = max(maxValue, curEor);
        }
        dp[i] = eor;
    }

    return maxValue;
}

class Node;
typedef shared_ptr<Node> pNode;
class Node {
public:
    Node() {
        this->nexts[0] = nullptr;
        this->nexts[0] = nullptr;
    }
    pNode nexts[2];
};

class NumTrie {
public:
    NumTrie() {
        head = pNode(new Node);
    }

    void add(int num) {
        pNode cur = head;
        for (int move = 31; move >= 0; move--) {
            int path = ((num >> move) & 1);                 // 从低位到高位依次提取出0, 1
            cur->nexts[path] = (cur->nexts[path] == nullptr // 下一路径是否存在, 不存在新建
                                ? pNode(new Node) 
                                : cur->nexts[path]);    
            cur = cur->nexts[path];
        }
    }

    int maxXor(int num) {       // 
        pNode cur = head;
        int res = 0;
        for (int move = 31; move >= 0; move--) {
            int path = ((num >> move) & 1);
            // 期待的下一路径
            int best = (move == 31      // 是否为符号位
                        ? path          // 符号位不变, 因为maxXor选出的异或结果要与当前的异或结果异或, 符号位不变, 异或之后的符号为0, 正数
                        : (path ^ 1));  // 其余位取反
            best = (cur->nexts[best] != nullptr // 期待的路径是否存在
                    ? best                      // 存在
                    : (best ^ 1));              // 不存在
            res |= (path ^ best) << move;       // res从高位到低位设置结果
            cur = cur->nexts[best];             // 因为add中从高位到低位建立32个节点, 所以肯定会存在下一节点
        }
        return res;
    }

    pNode head;
};
int getMaxE_4(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }
    int maxValue = INT_MIN;
    int eor = 0;
    NumTrie numTrie;
    numTrie.add(0);             // 这行要有, 代表建出一个字典树
    for (auto cur : arr) {
        eor ^= cur;
        maxValue = max(maxValue, numTrie.maxXor(eor));  // 查找字典树中是否与当前遍历结果最大
        numTrie.add(eor);
    }

    return maxValue;
}

int main() {
    //vector<int> arr;
    //generatorRandomArray(arr, 10, 5);
    vector<int> arr = { 0, 4};
    //vector<int> arr = { 4, 0, 0 };
    //vector<int> arr = {3, 2, 1, 0, 1, 2, 3, 0};
    printVector(arr);

    

    cout << getMaxE_1(arr) << endl;
    cout << getMaxE_2(arr) << endl;
    cout << getMaxE_3(arr) << endl;
    cout << getMaxE_4(arr) << endl;

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
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
    }
}