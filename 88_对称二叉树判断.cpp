#include <iostream>
#include <string>
using namespace std;

/*
    对称二叉树判断
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

bool process(Node* head1, Node* head2) {
    if ((nullptr == head1) && (nullptr == head2)) {     // 左右头结点都为nullptr
        return true;
    }
    if ((nullptr == head1) || (nullptr == head2)) {     // 左右头结点一个为nullptr, 另一个不为nullptr
        return false;
    }
    if (head1->value != head2->value)                   // 头结点对应的value不相等
        return false;

    if (process(head1->left, head2->right) && process(head1->right, head2->left))
        return true;
    else
        return false;
}

bool isSymmetrical(Node* head) {
    return process(head, head);
}

/* 不能利用下层结构来判断上层结构, 下层非对称, 上层可以是对称的
bool isSymmetrical(Node* head) {
    if (head == nullptr) {
        return true;
    }

    Node* left = head->left;
    Node* right = head->right;
    if ((left != nullptr) && (right != nullptr) && (left->value == right->value)) {
        bool L = isSymmetrical(left);
        bool H = isSymmetrical(right);
        if (H && L) {
            return true;
        }
        else {
            return false;
        }
    }
    else if ((left == nullptr) && (right == nullptr)) {
        return true;
    }
    else {
        return false;
    }
}
*/
int main() {
    Node *head = &Node(1);
    head->left = &Node(2);
    head->right = &Node(2);
    head->left->left = &Node(4);
    head->right->right = &Node(4);
    //head->left->right = &Node(5);
    //head->right->left = &Node(6);
    printTree(head);
    cout << "=============================================" << endl;
    if (isSymmetrical(head)) {
        cout << "对称二叉树" << endl;
    }
    else {
        cout << "非对称二叉树" << endl;
    }

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