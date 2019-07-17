#include <iostream>
#include <stack>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};

/*
    二叉树的遍历
*/

void preOrderUnRecur(Node *head) {
    if (head == nullptr) {
        return;
    }
    stack<Node *> sk;
    sk.push(head);
    while (!sk.empty()) {
        Node *cur = sk.top();
        sk.pop();
        cout << cur->value << " ";
        if (cur->right != nullptr)  // 先序, 先处理左节点后处理右节点, 而栈先进后出, 先压右节点
            sk.push(cur->right);
        if (cur->left != nullptr)   // 先序, 先处理左节点后处理右节点, 而栈先进后出, 后压左节点
            sk.push(cur->left);
    }
}

void inOrderUnRecur(Node *head) {
    Node *cur = head;
    stack<Node *> sk;
    while ((!sk.empty()) || (cur != nullptr)) {
        if (cur != nullptr) {   
            sk.push(cur);
            cur = cur->left;    // 一直向左穿
        }
        else {                  // 没有左节点时, cur移动至右节点
            cur = sk.top();
            sk.pop();
            cout << cur->value << " ";
            cur = cur->right;   // cur移动至右节点
        }
    }
}

void posOrderUnRecur1(Node *head) {
    if (head == nullptr) {
        return;
    }
    Node *cur = head;
    stack<Node *> sk;
    stack<Node *> ret;
    sk.push(cur);
    while (!sk.empty()) {
        Node *temp = sk.top();
        sk.pop();
        ret.push(temp);
        if (temp->left != nullptr) {    // 后序, 先处理右节点后处理左节点, 而栈先进后出, 先压左节点
            sk.push(temp->left);
        }
        if (temp->right != nullptr) {   // 后序, 先处理右节点后处理左节点, 而栈先进后出, 后压右节点
            sk.push(temp->right);
        }
    }
    while (!ret.empty()) {
        cout << ret.top()->value << " ";
        ret.pop();
    }
}

void posOrderUnRecur2(Node *head) {
    if (head == nullptr) {
        return;
    }

    stack<Node *> sk;
    sk.push(head);
    Node* cur = nullptr;
    Node* hasNode = head;   // 保存最近一次处理的节点

    while (!sk.empty()) {
        cur = sk.top();
        /* 左子树不为空 且 左子树未处理 且 右子树未处理 */
        if ((cur->left != nullptr) && (hasNode != cur->left) && (hasNode != cur->right)) {
            sk.push(cur->left);
        }
        /* 右子树不为空 且 右子树未处理 */
        else if ((cur->right != nullptr) && (hasNode != cur->right)) {
            sk.push(cur->right);
        }
        else {
            cout << cur->value << " ";
            //cout << sk.top()->value << " ";
            sk.pop();
            hasNode = cur;  // 当前节点打印过, 保存最近一次处理的节点
        }
    }
}

void preOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    cout << head->value << " ";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

void inOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    inOrderRecur(head->left);
    cout << head->value << " ";
    inOrderRecur(head->right);
}

void posOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    posOrderRecur(head->left);
    posOrderRecur(head->right);
    cout << head->value << " ";
}

int main() {
    Node *head = &Node(5);
    head->left = &Node(3);
    head->right = &Node(8);
    head->left->left = &Node(2);
    head->left->right = &Node(4);
    head->left->left->left = &Node(1);
    head->right->left = &Node(7);
    head->right->left->left = &Node(6);
    head->right->right = &Node(10);
    head->right->right->left = &Node(9);
    head->right->right->right = &Node(11);

    // recursive
    cout << "==============recursive==============" << endl;
    cout << "pre-order: " << endl << "\t";
    preOrderRecur(head);
    cout << endl;
    cout << "in-order: " << endl << "\t";
    inOrderRecur(head);
    cout << endl;
    cout << "pos-order: " << endl << "\t";
    posOrderRecur(head);
    cout << endl;

    // unrecursive
    cout << "============unrecursive=============" << endl;
    cout << "pre-order: " << endl << "\t";
    preOrderUnRecur(head);
    cout << endl;
    cout << "in-order: " << endl << "\t";
    inOrderUnRecur(head);
    cout << endl;
    cout << "pos-order: " << endl << "\t";
    posOrderUnRecur1(head);
    cout << endl << "\t";
    posOrderUnRecur2(head);
    cout << endl;
    return 0;
}