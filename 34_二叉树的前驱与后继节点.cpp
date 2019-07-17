#include <iostream>
#include <string>
#include <stack>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; parent = nullptr; }
    int value;
    Node *left, *right, *parent;
};
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

/*
    二叉树的前驱与后继节点
*/

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
    if (node->left != nullptr) {    // 左子树不为空, 找左子树最右侧节点
        return getRightMost(node->left);
    }
    else {                          // 无左子树
        Node *parent = node->parent;
        // parent != nullptr防止头结点穿出去
        while ((parent != nullptr) && (parent->right != node)) {    // 非右孩子: 查找该节点是以哪个节点为子树的最左边节点;
            node = parent;
            parent = node->parent;
        }
        return parent;              // 右孩子: 返回父节点
    }
}

Node* getLeftMost(Node *node) {
    if (node == nullptr)
        return node;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
Node* getSuccessorNode(Node *node) {
    if (node == nullptr) {
        return node;
    }
    if (node->right != nullptr)     // 有右子树, 返回右子树的最左边节点
        return getLeftMost(node->right);
    else {                          // 无右子树
        Node *parent = node->parent;
        // parent != nullptr防止头结点穿出去
        while ((parent != nullptr) && (parent->left != node)) {     // 非左孩子: 查找该结点是以哪个节点为子树的最右边节点;
            node = parent;
            parent = node->parent;
        }
        return parent;              // 左孩子: 返回父节点
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
    Node *head = &Node(6);
    head->parent = nullptr;
    head->left = &Node(3);
    head->left->parent = head;
    head->left->left = &Node(1);
    head->left->left->parent = head->left;
    head->left->left->right = &Node(2);
    head->left->left->right->parent = head->left->left;
    head->left->right = &Node(4);
    head->left->right->parent = head->left;
    head->left->right->right = &Node(5);
    head->left->right->right->parent = head->left->right;
    head->right = &Node(9);
    head->right->parent = head;
    head->right->left = &Node(8);
    head->right->left->parent = head->right;
    head->right->left->left = &Node(7);
    head->right->left->left->parent = head->right->left;
    head->right->right = &Node(10);
    head->right->right->parent = head->right;

    printTree(head);
    cout << "=============================================" << endl;

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