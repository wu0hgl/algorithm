#include <iostream>
#include <string>
using namespace std;

/*
    利用二叉树的递归遍历来实现
*/

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

void Mirror(Node* head) {
    if (head == nullptr) {
        return;
    }

    Node* left = head->left;
    Node* right = head->right;
    
    head->left = right;
    head->right = left;
    
    Mirror(left);
    Mirror(right);
}

int main() {
    Node *head = &Node(1);
    head->left = &Node(2);
    head->right = &Node(3);
    head->left->left = &Node(4);
    head->left->right = &Node(5);
    head->right->left = &Node(6);

    printTree(head);
    cout << "=============================================" << endl;
    
    Mirror(head);
    printTree(head);

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