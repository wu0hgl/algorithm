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
void printTree(Node *head);
void printInOrder(Node *head, int height, string to, int len);
string getSpace(int num);

class ReturnData {
public:
    bool isB;
    int h;
    ReturnData(bool isB, int h) {
        this->isB = isB;
        this->h = h;
    }
};

ReturnData process(Node* head) {
    if (head == nullptr) {
        return ReturnData(true, 0);
    }

    ReturnData leftData = process(head->left);
    if (!leftData.isB) {
        return ReturnData(false, 0);
    }

    ReturnData rightData = process(head->right);
    if (!rightData.isB) {
        return ReturnData(false, 0);
    }

    if (abs(leftData.h - rightData.h) > 1) {
        return ReturnData(false, 0);
    }

    // 返回左子树与右子树高度最大值+1
    return ReturnData(true, max(leftData.h, rightData.h) + 1); 
}
bool isB_1(Node* head) {
    return process(head).isB;
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
bool isB_2(Node* head) {
    vector<bool> record = vector<bool>(1, true);
    getHeight(head, 1, record);

    return record[0];
}

int main() {
    Node* head_1 = &Node(6);
    head_1->left = &Node(1);
    head_1->left->left = &Node(0);
    head_1->left->left->left = &Node(2);
    head_1->right = &Node(12);
    head_1->right->left = &Node(10);
    head_1->right->right = &Node(13);

    printTree(head_1);

    Node *head_2 = &Node(1);
    head_2->left = &Node(2);
    head_2->right = &Node(3);
    head_2->left->left = &Node(4);
    head_2->left->right = &Node(5);
    head_2->right->left = &Node(6);
    head_2->right->right = &Node(7);

    printTree(head_2);

    if (isB_1(head_1))  cout << "true" << endl;
    else                cout << "false" << endl;

    if (isB_1(head_2))  cout << "true" << endl;
    else                cout << "false" << endl;

    cout << "==================================" << endl;

    if (isB_2(head_1))  cout << "true" << endl;
    else                cout << "false" << endl;

    if (isB_2(head_2))  cout << "true" << endl;
    else                cout << "false" << endl;
    
    return 0;
}

void printTree(Node *head) {
    cout << "Binary Tree:" << endl;
    printInOrder(head, 0, "H", 17);
    cout << endl;
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

string getSpace(int num) {
    string space = " ";
    string buf;
    for (int i = 0; i < num; i++) {
        buf.append(space.c_str());
    }
    return buf;
}