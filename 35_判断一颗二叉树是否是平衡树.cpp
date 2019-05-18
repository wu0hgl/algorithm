#include <iostream>
#include <stack>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};

int getHeight(Node *head, int level, bool &res) {
    if (head == nullptr) {
        return level;
    }
    int lH = getHeight(head->left, level + 1, res);
    if (!res) {
        return level;
    }
    int rH = getHeight(head->right, level + 1, res);
    if (!res) {
        return level;
    }
    if (abs(lH - rH) > 1) {
        res = false;
    }
    return max(lH, rH);
}

bool isBalance_1(Node *head) {
    bool res = true;
    getHeight(head, 1, res);
    return res;
}

class ReturnData {
public:
    ReturnData(bool isB, int high) : isB(isB), high(high) {}
    //~ReturnData() { cout << "Îö¹¹º¯Êý" << endl; }
    bool isB;
    int high;
};

shared_ptr<ReturnData> isBalance_2(Node *head) {
    if (head == nullptr) {
        return shared_ptr<ReturnData>(new ReturnData(true, 0));
    }

    shared_ptr<ReturnData> leftData = isBalance_2(head->left);
    if (!leftData->isB) {
        return shared_ptr<ReturnData>(new ReturnData(false, 0));
    }
    
    shared_ptr<ReturnData> rightData = isBalance_2(head->right);
    if (!rightData->isB) {
        return shared_ptr<ReturnData>(new ReturnData(false, 0));
    }

    if (abs(leftData->high - rightData->high) > 1) {
        return shared_ptr<ReturnData>(new ReturnData(false, 0));
    }

    return shared_ptr<ReturnData>(new ReturnData(true, max(leftData->high, rightData->high) + 1));
}

bool isBalance_3(Node *pRoot, int *pDepth) {
    if (nullptr == pRoot) {
        *pDepth = 0;
        return true;
    }
    int left = 0;
    int right = 0;
    if ((isBalance_3(pRoot->left, &left))
        && isBalance_3(pRoot->right, &right)) {
        int dif = left - right;
        if ((dif >= -1) && (dif <= 1)) {
            *pDepth = 1 + (left > right ? left : right);
            return true;
        }
    }

    return false;
}

bool isBalance_3(Node* pRoot) {
    int depth = 0;
    return isBalance_3(pRoot, &depth);
}

int main() {
    Node *head = new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);
    head->right->left = new Node(6);
    head->right->right = new Node(7);

    cout << isBalance_1(head) << endl;
    cout << isBalance_2(head)->isB << endl;
    cout << isBalance_3(head) << endl;
    
    return 0;
}