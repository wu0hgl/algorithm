#include <iostream>
#include <stack>
using namespace std;
class Node {
public:
    Node(int value) : m_value(value) { left = nullptr; right = nullptr; }
    int m_value;
    Node *left;
    Node *right;
};

void preOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    cout << head->m_value << " ";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

void inOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    inOrderRecur(head->left);
    cout << head->m_value << " ";
    inOrderRecur(head->right);
}

void posOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    posOrderRecur(head->left);
    posOrderRecur(head->right);
    cout << head->m_value << " ";
}

void preOrderUnRecur(Node *head) {
    if (head == nullptr) {
        return;
    }
    stack<Node *> sk;
    sk.push(head);
    while (!sk.empty()) {
        Node *cur = sk.top();
        sk.pop();
        cout << cur->m_value << " ";
        if (cur->right != nullptr)
            sk.push(cur->right);
        if (cur->left != nullptr)
            sk.push(cur->left);
    }
}

void inOrderUnRecur(Node *head) {
    Node *cur = head;
    stack<Node *>sk;
    while ((!sk.empty()) || (cur != nullptr)) {
        if (cur != nullptr) {
            sk.push(cur);
            cur = cur->left;
        }
        else {
            cur = sk.top();
            sk.pop();
            cout << cur->m_value << " ";
            cur = cur->right;
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
        if (temp->left != nullptr) {
            sk.push(temp->left);
        }
        if (temp->right != nullptr) {
            sk.push(temp->right);
        }
    }
    while (!ret.empty()) {
        cout << ret.top()->m_value << " ";
        ret.pop();
    }
}

void posOrderUnRecur2(Node *head) {
    if (head == nullptr) {
        return;
    }

    stack<Node *> sk;
    sk.push(head);
    Node *cur = nullptr;
    while (!sk.empty()) {
        cur = sk.top();
        if (cur->left != nullptr && head != cur->left && head != cur->right) {
            sk.push(cur->left);
        }
        else if (cur->right != nullptr && head != cur->right) {
            sk.push(cur->right);
        }
        else {
            cout << sk.top()->m_value << " ";
            sk.pop();
            head = cur;
        }
    }
}

int main() {
    Node *head = new Node(5);
    head->left = new Node(3);
    head->right = new Node(8);
    head->left->left = new Node(2);
    head->left->right = new Node(4);
    head->left->left->left = new Node(1);
    head->right->left = new Node(7);
    head->right->left->left = new Node(6);
    head->right->right = new Node(10);
    head->right->right->left = new Node(9);
    head->right->right->right = new Node(11);

    // recursive
    cout << "==============recursive==============" << endl;
    cout << "pre-order: " << endl;
    preOrderRecur(head);
    cout << endl;
    cout << "in-order: " << endl;
    inOrderRecur(head);
    cout << endl;
    cout << "pos-order: " << endl;
    posOrderRecur(head);
    cout << endl;

    // unrecursive
    cout << "============unrecursive=============" << endl;
    cout << "pre-order: " << endl;
    preOrderUnRecur(head);
    cout << endl;
    cout << "in-order: " << endl; 
    inOrderUnRecur(head);
    cout << endl;
    cout << "pos-order: " << endl;
    posOrderUnRecur1(head);
    cout << endl;
    posOrderUnRecur2(head);
    cout << endl;
    return 0;
}