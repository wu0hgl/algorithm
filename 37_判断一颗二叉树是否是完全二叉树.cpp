#include <iostream>
#include <queue>
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
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

/*
    判断一颗二叉树是否是完全二叉树
*/

bool isCBT(Node *head) {
    if (head == nullptr)
        return true;
    bool leaf = false;
    Node *l = nullptr;
    Node *r = nullptr;
    Node *cur = head;
    queue<Node *> q;
    q.push(cur);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        //cout << cur->value << " ";
        l = cur->left;
        r = cur->right;
        if ((leaf && (l != nullptr || r != nullptr))    // 是叶子节点, 并且左右孩子任意一个不为空
            || (l == nullptr && (r != nullptr))) {      // 左孩子为空, 右孩子不为空
            return false;
        }

        if (l != nullptr) {
            q.push(l);
        }
        if (r != nullptr) {
            q.push(r);
        }
        // 左孩子为空, 开启叶子节点, 左孩子为空右孩子不为空已经在上面的if中判断过了
        // 左孩子不为空, 右孩子为空, 开启叶子节点状态
        // 左右孩子都为空
        if (l == nullptr || r == nullptr) {             // 对应上面两个状态
            leaf = true;

        //if (l != nullptr) {
        //    q.push(l);
        //}
        //if (r != nullptr) {
        //    q.push(r);
        //}
        //else {                // (l == nullptr && (r != nullptr) 已经判断过, 所以只需r可以用if else结构
        //    leaf = true;
        //}

        }
    }
    cout << endl;
    return true;
}

int main() {
    Node *head_1 = &Node(1);
    head_1->left = &Node(2);
    head_1->right = &Node(3);
    head_1->left->left = &Node(4);
    head_1->left->right = &Node(5);
    head_1->right->left = &Node(6);
    head_1->right->right = &Node(7);

    Node *head_2 = &Node(5);
    head_2->left = &Node(3);
    head_2->right = &Node(8);
    head_2->left->left = &Node(2);
    head_2->left->right = &Node(4);
    head_2->left->left->left = &Node(1);
    head_2->right->left = &Node(7);
    head_2->right->left->left = &Node(6);
    head_2->right->right = &Node(10);
    head_2->right->right->left = &Node(9);
    head_2->right->right->right = &Node(11);
    printTree(head_1);
    cout << "=============================================" << endl;
    printTree(head_2);
    cout << "=============================================" << endl;
    cout << "head_1: " << isCBT(head_1) << endl;
    cout << "head_2: " << isCBT(head_2) << endl;

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