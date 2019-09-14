#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value; Node *left; Node *right;
};
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

/*
    完全二叉树节点的个数
*/

int mostLeftLevel(Node *node, int level) {  // 以node为头节点所能到达的最大层数
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
    if (node->right != nullptr) {
        cout << node->value << " 的右节点不为空, 右节点为 " << node->right->value  
             << " 右节点可到达最大深度"<< mostLeftLevel(node->right, level + 1) 
             << endl;
    }
    else {
        cout << node->value << " 的右节点为空, " 
             << "当前节点到达最大深度 " << mostLeftLevel(node->right, level + 1) 
             << endl;
    }
    if (mostLeftLevel(node->right, level + 1) == h) {   // 调用mostLeftLevel时, 节点下一, 层数同时+1
        return (1 << (h - level)) + bs(node->right, level + 1, h);
    }
    else {
        return (1 << (h - level - 1)) + bs(node->left, level + 1, h);
    }
}

int nodeNum_1(Node *head) {
    if (head == nullptr) {
        return 0;
    }
    cout << "头结点: " << head->value 
         << " 可到达最大深度: " << mostLeftLevel(head, 1) 
         << endl;
    return bs(head, 1, mostLeftLevel(head, 1));
}

map<Node*, int> mp;
void func(Node* head) {
    if (head == nullptr)
        return;
    mp[head]++;
    func(head->left);
    func(head->right);
}

int nodeNum_2(Node* head) {
    mp.clear();
    func(head);
    return mp.size();
}

int main() {
    Node *head_2 = &Node(1);
    head_2->left = &Node(2);
    head_2->right = &Node(3);
    head_2->left->left = &Node(4);
    head_2->left->right = &Node(5);
    head_2->right->left = &Node(6);

    printTree(head_2);
    cout << "=============================================" << endl;
    cout << "node : " << nodeNum_1(head_2) << endl;
    cout << "node : " << nodeNum_2(head_2) << endl;

    Node *head_1 = &Node(1);
    head_1->left = &Node(2);
    head_1->right = &Node(3);
    head_1->left->left = &Node(4);
    head_1->left->right = &Node(5);
    head_1->right->left = &Node(6);
    head_1->right->right = &Node(7);
    head_1->left->left->left = &Node(7);
    printTree(head_1);
    cout << "=============================================" << endl;
    cout << "node : " << nodeNum_1(head_1) << endl;
    cout << "node : " << nodeNum_2(head_1) << endl;

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