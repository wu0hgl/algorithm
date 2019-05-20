#include <iostream>
#include <queue>
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

/*
    判断一颗二叉树是否是完全二叉树
*/

bool isCBT(Node *head) {
    if (head == nullptr)
        return true;
    bool leaf = false;
    Node *l = nullptr;
    Node *r = nullptr;
    Node *cur = head;
    queue<Node *> q;
    q.push(cur);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        l = cur->left;
        r = cur->right;
        if ((leaf && (l != nullptr || r != nullptr))
            || (l == nullptr && (r != nullptr))) {
            return false;
        }

        //if (l != nullptr) {
        //    q.push(l);
        //}
        //if (r != nullptr) {
        //    q.push(r);
        //}
        //else {
        //    leaf = true;
        //}

        if (l != nullptr) {
            q.push(l);
        }
        if (r != nullptr) {
            q.push(r);
        }
        if (l == nullptr || r == nullptr) {
            leaf = true;
        }
    }
    return true;
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
    printTree(head_1);
    cout << "=============================================" << endl;
    printTree(head_2);
    cout << "=============================================" << endl;
    cout << "head_1: " << isCBT(head_1) << endl;
    cout << "head_2: " << isCBT(head_2) << endl;

    return 0;
}