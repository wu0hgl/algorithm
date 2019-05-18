#include <iostream>
#include <stack>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; parent = nullptr; }
    int value;
    Node *left, *right, *parent;
};

/*
二叉树的前驱与后继节点
*/

Node* getLeftMost(Node *node) {
    if (node == nullptr)
        return node;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* getRightMost(Node *node) {
    if (node == nullptr) {
        return node;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node* getPredecessorNode(Node *node) {
    if (node == nullptr) {
        return node;
    }
    if (node->left != nullptr) {
        return getRightMost(node->left);
    }
    else {
        Node *parent = node->parent;
        while ((parent != nullptr) && (parent->right != node)) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

Node* getSuccessorNode(Node *node) {
    if (node == nullptr) {
        return node;
    }
    if (node->right != nullptr)
        return getLeftMost(node->right);
    else {
        Node *parent = node->parent;
        while ((parent != nullptr) && (parent->left != node)) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

void inOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    inOrderRecur(head->left);
    cout << head->value << " ";
    inOrderRecur(head->right);
}

int main() {
    Node *head = new Node(6);
    head->parent = nullptr;
    head->left = new Node(3);
    head->left->parent = head;
    head->left->left = new Node(1);
    head->left->left->parent = head->left;
    head->left->left->right = new Node(2);
    head->left->left->right->parent = head->left->left;
    head->left->right = new Node(4);
    head->left->right->parent = head->left;
    head->left->right->right = new Node(5);
    head->left->right->right->parent = head->left->right;
    head->right = new Node(9);
    head->right->parent = head;
    head->right->left = new Node(8);
    head->right->left->parent = head->right;
    head->right->left->left = new Node(7);
    head->right->left->left->parent = head->right->left;
    head->right->right = new Node(10);
    head->right->right->parent = head->right;

    cout << "inorder: " << endl;
    inOrderRecur(head);
    cout << endl;
    cout << "==================================" << endl;

    Node *test = head->left->left;  // 1's pre is null
    //cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->left->left->right;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->left;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->left->right;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->left->right->right;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->right->left->left;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->right->left;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->right;
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    test = head->right->right; // 10's next is null
    cout << test->value << " pre: " << getPredecessorNode(test)->value << endl;
    //cout << test->value << " next: " << getSuccessorNode(test)->value << endl;
    cout << "==================================" << endl;

    return 0;
}