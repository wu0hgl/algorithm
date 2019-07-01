#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
    二叉树中, 一个节点可以往上走和往下走, 那么从节点A总能走到节点B. 节点A走到节点B的距离为: A走到B最短路径上的节点个数. 
    求一棵二叉树上的最远距离
*/

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

class ReturnType {
public:
    ReturnType(int m, int h){
        this->maxDistance = m;
        this->h = h;
    }
    int maxDistance;
    int h;
};

ReturnType process(Node* head) {
    if (head == nullptr) {
        return ReturnType(0, 0);
    }

    ReturnType leftReturnType = process(head->left);
    ReturnType rightReturnType = process(head->right);

    int includeHeadDistance = leftReturnType.h + 1 + rightReturnType.h;
    int p1 = leftReturnType.maxDistance;
    int p2 = rightReturnType.maxDistance;

    /* 返回结构 */
    int resultDistance = max(max(p1, p2), includeHeadDistance);
    int hitself = max(leftReturnType.h, rightReturnType.h) + 1;

    return ReturnType(resultDistance, hitself);
}
int maxDistance_1(Node* head) {
    return process(head).maxDistance;
}

int posOrder(Node* head, vector<int>& record) {
    if (head == nullptr) {
        record[0] = 0;
        return 0;
    }
    int lMax = posOrder(head->left, record);
    int maxfromLeft = record[0];

    int rMax = posOrder(head->right, record);
    int maxfromRight = record[0];

    int curNodeMax = maxfromLeft + maxfromRight + 1;

    record[0] = max(maxfromLeft, maxfromRight) + 1;
    //return curNodeMax;        // 本题中这么返回也可以
    return max(max(lMax, rMax), curNodeMax);
}
int maxDistance_2(Node* head) {
    vector<int> record = vector<int>(1, 0);     // 距离作为返回值, 高度作为记录

    return posOrder(head, record);
}

int main() {
    Node* head = &Node(6);
    head->left = &Node(1);
    head->left->left = &Node(0);
    head->left->right = &Node(3);
    head->right = &Node(12);
    head->right->left = &Node(10);
    head->right->left->left = &Node(4);
    head->right->left->left->left = &Node(2);
    head->right->left->left->right = &Node(5);
    head->right->left->right = &Node(14);
    head->right->left->right->left = &Node(11);
    head->right->left->right->right = &Node(15);
    head->right->left->right->right->left = &Node(20);
    head->right->right = &Node(13);
    head->right->right->left = &Node(20);
    head->right->right->right = &Node(16);

    printTree(head);

    cout << maxDistance_1(head) << endl;
    cout << maxDistance_2(head) << endl;

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