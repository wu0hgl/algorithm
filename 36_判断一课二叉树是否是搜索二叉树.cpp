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

bool isBST_1(Node *head) {
    Node *cur = head;
    Node *pre = nullptr;
    stack<Node *>sk;
    while ((!sk.empty()) || (cur != nullptr)) {
        if (cur != nullptr) {
            sk.push(cur);
            cur = cur->left;
        }
        else {
            cur = sk.top();
            sk.pop();
            if (pre != nullptr && cur->value <= pre->value)
                return false;
            pre = cur;
            cur = cur->right;
        }
    }
    return true;
}


bool isBST_2(Node *head) {
    if (head == nullptr) {
        return true;
    }
    bool res = true;
    Node *pre = nullptr;
    Node *cur1 = head;
    Node *cur2 = nullptr;
    while (cur1 != nullptr) {
        cur2 = cur1->left;
        if (cur2 != nullptr) {
            while (cur2->right != nullptr && cur2->right != cur1) {
                cur2 = cur2->right;
            }
            if (cur2->right == nullptr) {
                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }
            else {
                cur2->right = nullptr;
            }
        }
        if (pre != nullptr && pre->value > cur1->value) {
            res = false;
        }
        pre = cur1;
        cur1 = cur1->right;
    }
    return res;
}

void inOrder(Node *head) {
    if (head == nullptr) {
        return;
    }
    inOrder(head->left);
    cout << head->value << " ";
    inOrder(head->right);
}

int main() {
    Node *head_1 = new Node(1);
    head_1->left = new Node(2);
    head_1->right = new Node(3);
    head_1->left->left = new Node(4);
    head_1->left->right = new Node(5);
    head_1->right->left = new Node(6);
    head_1->right->right = new Node(7);

    Node *head_2 = new Node(5);
    head_2->left = new Node(3);
    head_2->right = new Node(8);
    head_2->left->left = new Node(2);
    head_2->left->right = new Node(4);
    head_2->left->left->left = new Node(1);
    head_2->right->left = new Node(7);
    head_2->right->left->left = new Node(6);
    head_2->right->right = new Node(10);
    head_2->right->right->left = new Node(9);
    head_2->right->right->right = new Node(11);

    cout << "head_1: ";
    inOrder(head_1);
    cout << endl;
    cout << "head_2: ";
    inOrder(head_2);
    cout << endl;
    cout << "================isBST_1===================" << endl;
    cout << "head_1: " << isBST_1(head_1) << endl;
    cout << "head_2: " << isBST_1(head_2) << endl;
    cout << "================isBST_2===================" << endl;
    cout << "head_1: " << isBST_2(head_1) << endl;
    cout << "head_2: " << isBST_2(head_2) << endl;

    return 0;
}