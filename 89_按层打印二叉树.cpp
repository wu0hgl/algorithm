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
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);
void printVector(vector<vector<int>>& arr);

/*
    按层打印二叉树
*/

vector<vector<int>> func_1(Node* head) {
    vector<vector<int> > ret;
    if (nullptr == head) {
        return ret;
    }
    queue<Node*> q;
    q.push(head);
    while (!q.empty()) {
        int size = q.size();
        vector<int> temp;
        while (size--) {
            Node* cur = q.front();
            q.pop();
            temp.push_back(cur->value);
            if (cur->left != nullptr) {
                q.push(cur->left);
            }
            if (cur->right != nullptr) {
                q.push(cur->right);
            }
        }
        ret.push_back(temp);
    }

    return ret;
}

vector<int> func_2(Node* root) {
    vector<int> ret;
    if (nullptr == root)
        return ret;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        root = q.front();
        q.pop();
        ret.push_back(root->value);
        if (root->left != nullptr)
            q.push(root->left);
        if (root->right != nullptr)
            q.push(root->right);
    }
    return ret;
}

int main() {
    Node *head_1 = &Node(1);
    head_1->left = &Node(2);
    head_1->right = &Node(3);
    head_1->left->left = &Node(4);
    head_1->left->right = &Node(5);
    head_1->right->left = &Node(6);
    head_1->right->right = &Node(7);

    Node *head_2 = &Node(5);
    head_2->left = &Node(3);
    head_2->right = &Node(8);
    head_2->left->left = &Node(2);
    head_2->left->right = &Node(4);
    head_2->left->left->left = &Node(1);
    head_2->right->left = &Node(7);
    head_2->right->left->left = &Node(6);
    head_2->right->right = &Node(10);
    head_2->right->right->left = &Node(9);
    head_2->right->right->right = &Node(11);
    printTree(head_1);
    cout << "=============================================" << endl;
    printTree(head_2);
    cout << "=============================================" << endl;
    vector<vector<int>> ret;
    vector<int> res;
    ret = func_1(head_1);
    printVector(ret);
    res = func_2(head_1);
    for (auto i : res) {
        cout << i << " ";
    }
    cout << endl << "=============================================" << endl;
    ret = func_1(head_2);
    printVector(ret);
    res = func_2(head_2);
    for (auto i : res) {
        cout << i << " ";
    }
    cout << endl;

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

void printVector(vector<vector<int>>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}