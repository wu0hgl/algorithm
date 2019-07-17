#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

/*
    二叉树之字形打印
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

vector<vector<int> > Print(Node* pRoot) {
    vector<vector<int>> ret;
    if (nullptr == pRoot) {
        return ret;
    }
    stack<Node *> levels[2];
    vector<int> vt;
    int current = 1;
    int next = 0;

    levels[current].push(pRoot);
    while ((!levels[0].empty()) || (!levels[1].empty())) {
        Node *temp = levels[current].top();
        levels[current].pop();
        vt.push_back(temp->value);

        if (1 == current) {
            if (nullptr != temp->left) {
                levels[next].push(temp->left);
            }
            if (nullptr != temp->right) {
                levels[next].push(temp->right);
            }
        }
        else {
            if (nullptr != temp->right) {
                levels[next].push(temp->right);
            }
            if (nullptr != temp->left) {
                levels[next].push(temp->left);
            }
        }

        if (levels[current].empty()) {
            ret.push_back(vt);
            vt.resize(0);           // 把之前保存的数据清空
            current = 1 - current;
            next = 1 - next;
        }
    }
    return ret;
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
    vector<vector<int>> temp = Print(head);
    for (size_t i = 0; i < temp.size(); i++) {
        for (size_t j = 0; j < temp[i].size(); j++) {
            cout << temp[i][j] << " ";
        }
        cout << endl;
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