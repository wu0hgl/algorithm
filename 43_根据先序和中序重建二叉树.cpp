#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    输入二叉树先序遍历和中序遍历结果, 重建二叉树
*/

class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};

vector<int> preOrder;
vector<int> inOrder;

string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);
void preOrderRecur(Node *head);
void inOrderRecur(Node *head);

Node* constructTree(vector<int> pre, int startPre, int endPre, vector<int> in, int startIn, int endIn) {
    if ((startPre > endPre) || (startIn > endIn)) {
        return NULL;
    }

    Node* ret = new Node(pre[startPre]);

    for (int i = 0; i <= endIn; i++) {
        if (pre[startPre] == in[i]) {
            ret->left = constructTree(pre, startPre + 1, startPre + i - startIn, in, startIn, i - 1);
            ret->right = constructTree(pre, startPre + i - startIn + 1, endPre, in, i + 1, endIn);
            break;
        }
    }

    return ret;
}

int main() {
    Node *head = new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);
    head->right->left = new Node(6);
    printTree(head);
    cout << "=============================================" << endl;
    preOrderRecur(head);
    inOrderRecur(head);
    for (auto cur : preOrder) {
        cout << cur << " ";
    }
    cout << endl;
    for (auto cur : inOrder) {
        cout << cur << " ";
    }
    cout << endl;
    cout << "=============================================" << endl;
    Node *temp = constructTree(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size() - 1);
    printTree(temp);

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

void preOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    preOrder.push_back(head->value);
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

void inOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    inOrderRecur(head->left);
    inOrder.push_back(head->value);
    inOrderRecur(head->right);
}