#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

/*
    完全二叉树节点的个数.cpp
*/

class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};

int mostLeftLevel(Node *node, int level) {
    while (node != nullptr) {
        level++;
        node = node->left;
    }
    return level - 1;
}

int bs(Node *node, int level, int h) {
    if (level == h) {
        return 1;
    }
    if (mostLeftLevel(node->right, level + 1) == h) {
        return (1 << (h - level)) + bs(node->right, level + 1, h);
    }
    else {
        return (1 << (h - level - 1)) + bs(node->left, level + 1, h);
    }
}

int nodeNum(Node *head) {
    if (head == nullptr) {
        return 0;
    }
    return bs(head, 1, mostLeftLevel(head, 1));
}

string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);

void printTree(Node *head) {
    //System->out->println("Binary Tree:");
    cout << "Binary Tree:" << endl;
    printInOrder(head, 0, "H", 17);
    cout << endl;
    //System->out->println();
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
    //System->out->println(getSpace(height * len) + val);
    cout << (getSpace(height * len) + val).c_str() << endl;
    printInOrder(head->left, height + 1, "^", len);
}

string getSpace(int num) {
    string space = " ";
    //stringBuffer buf = new stringBuffer("");
    string buf;
    for (int i = 0; i < num; i++) {
        buf.append(space.c_str());
    }
    return buf;
}

int main() {
    Node *head = new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);
    head->right->left = new Node(6);
    //System.out.println(nodeNum(head));
    printTree(head);
    cout << "=============================================" << endl;
    cout << "node : " << nodeNum(head) << endl;

    return 0;
}
