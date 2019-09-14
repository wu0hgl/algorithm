#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
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

Node* lowestAncestor(Node* head, Node* p1, Node* p2) {
    if ((head == nullptr) || (head == p1) || (head == p2)) {
        return head;
    }
    Node* L = lowestAncestor(head->left, p1, p2);
    Node* R = lowestAncestor(head->right, p1, p2);
    if ((L != nullptr) && (R != nullptr)) {
        return head;
    }
    return L != nullptr ? L : R;
}

int main() {
    Node *head_1 = &Node(1);
    head_1->left = &Node(2);
    head_1->right = &Node(3);
    head_1->left->left = &Node(4);
    head_1->left->right = &Node(5);
    head_1->right->left = &Node(6);
    head_1->right->right = &Node(7);
    printTree(head_1);
    Node* temp = &Node(8);
    cout << "=============================================" << endl;
    Node* ret = lowestAncestor(head_1, head_1->right, head_1->right->right);
    if (ret != nullptr) {
        cout << ret->value << endl;
    }
    else {
        cout << "not found" << endl;
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