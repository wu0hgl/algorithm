#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

/*
    判断一颗二叉树是否是平衡树
*/

int process_1(Node *head, int level, bool &res) {
    if (head == nullptr) {
        return level;
    }
    int lH = process_1(head->left, level + 1, res);
    if (!res) {
        return level;
    }
    int rH = process_1(head->right, level + 1, res);
    if (!res) {
        return level;
    }
    if (abs(lH - rH) > 1) {
        res = false;
    }
    return max(lH, rH);
}

bool isBalance_1(Node *head) {
    bool res = true;            // 初始化为true
    process_1(head, 0, res);
    //cout << process_1(head, 0, res) << endl;
    return res;
}

// 成员都是基础数据类型, 可以直接拷贝构造
class ReturnData {
public:
    ReturnData(bool isB, int high) : isB(isB), high(high) { }
    //~ReturnData() { cout << "析构函数" << endl; }
    bool isB;
    int high;
};

ReturnData isBalance_2(Node *head) {
    if (head == nullptr) {
        return ReturnData(true, 0);
    }

    ReturnData leftData = isBalance_2(head->left);
    if (!leftData.isB) {
        return ReturnData(false, 0);
    }
    
    ReturnData rightData = isBalance_2(head->right);
    if (!rightData.isB) {
        return ReturnData(false, 0);
    }

    if (abs(leftData.high - rightData.high) > 1) {
        return ReturnData(false, 0);
    }

    return ReturnData(true, max(leftData.high, rightData.high) + 1);
}

bool process_2(Node *pRoot, int *pDepth) {  // 把ReturnData中isB当作返回值, high作为输出参数
    if (nullptr == pRoot) {
        *pDepth = 0;
        return true;
    }
    int left = 0;
    int right = 0;
    if ((process_2(pRoot->left, &left))
        && process_2(pRoot->right, &right)) {
        int dif = left - right;
        if ((dif >= -1) && (dif <= 1)) {
            *pDepth = 1 + (left > right ? left : right);
            return true;
        }
    }

    return false;
}

bool isBalance_3(Node* pRoot) {
    int record = 0;
    return process_2(pRoot, &record);
}

int getHeight(Node* head, int level, vector<bool>& record) {
    if (head == nullptr) {
        return level;
    }

    int lH = getHeight(head->left, level + 1, record);
    if (!record[0]) {
        return level;
    }

    int rH = getHeight(head->right, level + 1, record);
    if (!record[0]) {
        return level;
    }

    if (abs(lH - rH) > 1) {
        record[0] = false;
    }

    return max(lH, rH);
}
bool isBalance_4(Node* head) {
    vector<bool> record = vector<bool>(1, true);
    getHeight(head, 1, record);

    return record[0];
}

int main() {
    Node *head = &Node(1);
    head->left = &Node(2);
    head->right = &Node(3);
    head->left->left = &Node(4);
    head->left->right = &Node(5);
    head->right->left = &Node(6);
    head->right->right = &Node(7);

    printTree(head);
    cout << "=============================================" << endl;

    if (isBalance_1(head)) {
        cout << "平衡二叉树" << endl;
    }
    else {
        cout << "非平衡二叉树" << endl;
    }
    cout << "=============================================" << endl;
    
    if (isBalance_2(head).isB) {
        cout << "平衡二叉树" << endl;
    }
    else {
        cout << "非平衡二叉树" << endl;
    }
    //cout << isBalance_2(head).high << endl;
    cout << "=============================================" << endl;

    if (isBalance_3(head)) {
        cout << "平衡二叉树" << endl;
    }
    else {
        cout << "非平衡二叉树" << endl;
    }
    cout << "=============================================" << endl;

    if (isBalance_4(head)) {
        cout << "平衡二叉树" << endl;
    }
    else {
        cout << "非平衡二叉树" << endl;
    }
    cout << "=============================================" << endl;
    
    return 0;
}

void printTree(Node *head) {
    cout << "Binary Tree:" << endl;
    printInOrder(head, 0, "H", 17);
    cout << endl;
}

string getSpace(int num) {
    string space = " ";
    string buf;
    for (int i = 0; i < num; i++) {
        buf.append(space.c_str());
    }
    return buf;
}

void printInOrder(Node *head, int height, string to, int len) {
    if (head == nullptr) {
        return;
    }
    printInOrder(head->right, height + 1, "v", len);
    string val = to + to_string(head->value) + to;
    int lenM = val.length();
    int lenL = (len - lenM) / 2;
    int lenR = len - lenM - lenL;
    val = getSpace(lenL) + val + getSpace(lenR);
    cout << (getSpace(height * len) + val).c_str() << endl;
    printInOrder(head->left, height + 1, "^", len);
}