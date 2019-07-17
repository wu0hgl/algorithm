﻿#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
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
    输入一颗二叉树的根节点和一个整数, 打印出二叉树中结点值的和为输入整数的所有路径. 
    路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径. 
*/

vector<vector<int> > ret;
vector<int> temp;

void dfsFind(Node* root, int expectNumber) {
    if (NULL == root) {
        return;
    }
    temp.push_back(root->value);    // 当前节点压栈
    if ((root->value == expectNumber) && (NULL == root->left) && (NULL == root->right)) {
        ret.push_back(temp);
    }

    dfsFind(root->left, expectNumber - root->value);
    dfsFind(root->right, expectNumber - root->value);
    //if (!temp.empty()) {
        temp.pop_back();            // 与上面的压栈操作相对应
    //}
}
vector<vector<int> > FindPath(Node* root, int expectNumber) {
    if (root) {
        dfsFind(root, expectNumber);
    }

    return ret;
}

int main() {
    Node *head = &Node(5);
    head->left = &Node(3);
    head->right = &Node(8);
    head->left->left = &Node(2);
    head->left->right = &Node(4);
    head->left->left->left = &Node(24);
    head->right->left = &Node(7);
    head->right->left->left = &Node(6);
    head->right->right = &Node(10);
    head->right->right->left = &Node(9);
    head->right->right->right = &Node(11);
    printTree(head);
    FindPath(head, 34);
    for (int i = 0; i < ret.size(); i++) {
        for (int j = 0; j < ret[i].size(); j++) {
            cout << ret[i][j] << " ";
        }
        cout << endl;
    }

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