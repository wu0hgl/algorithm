#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
给定彼此独立的两颗树头结点分别为t1和t2, 判断t1中是否有与t2树拓扑结构完全相同的子树
*/

class Node {
public:
    Node(int data) {
        this->value = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    int value;
    Node *left;
    Node *right;
};

string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);
void preOrderRecur(Node *head);
void inOrderRecur(Node *head);

bool check(Node* h, Node* t2) {
    if (t2 == nullptr) {
        return true;
    }
    if ((h == nullptr) || (h->value != t2->value)) {
        return false;
    }
    return (check(h->left, t2->left) && check(h->right, t2->right));
}

bool contains(Node* t1, Node* t2) {
    if (t2 == nullptr) {
        return true;
    }
    if (t1 == nullptr) {
        return false;
    }
    return check(t1, t2) || contains(t1->left, t2) || contains(t1->right, t2);
}

int main() {
    Node *t1 = &Node(1);
    t1->left = &Node(2);
    t1->right = &Node(3);
    t1->left->left = &Node(4);
    t1->left->right = &Node(5);
    t1->right->left = &Node(6);
    t1->right->right = &Node(7);
    t1->left->left->right = &Node(8);
    t1->left->right->left = &Node(9);

    Node *t2 = &Node(2);
    t2->left = &Node(4);
    t2->left->right = &Node(8);
    t2->right = &Node(5);
    t2->right->left = &Node(9);

    Node *t3 = &Node(2);
    t3->left = &Node(4);
    t3->left->right = &Node(8);
    t3->right = &Node(5);
    t3->right->left = &Node(9);
    t3->right->right = &Node(10);

    t2->right->left->left = &Node(9);

    printTree(t1);
    printTree(t2);
    cout << contains(t1, t2) << endl;
    cout << "====================" << endl;
    printTree(t1);
    printTree(t3);
    cout << contains(t1, t3) << endl;
    cout << "====================" << endl;
    //cout << contains(t2, t3) << endl;

    return 0;
}

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