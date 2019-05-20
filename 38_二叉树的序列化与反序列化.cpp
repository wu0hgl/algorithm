#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

/*
    二叉树序列化
    目前版本只有先序方式的序列化与反列化
*/

class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};

void Serialize(Node *root, string &str) {
    if (root == nullptr) {
        str += '#';
        return;
    }
    str += to_string(root->value) + ',';
    Serialize(root->left, str);
    Serialize(root->right, str);
}
char* Serialize(Node *root) {
    if (root == nullptr)
        return nullptr;
    string str;
    Serialize(root, str);
    char *p = new char[str.size() + 1];
    strcpy(p, str.c_str());
    p[str.size()] = '\0';
    return p;
}
Node* Deserialize(char **str) {
    if (**str == '#') {
        (*str)++;
        return nullptr;
    }
    int num = 0;
    while ((**str != ',') && (**str != '\0')) {
        num = num * 10 + ((**str) - '0');
        (*str)++;
    }
    Node* node = new Node(num);
    if (**str == '\0')
        return node;
    else
        (*str)++;
    node->left = Deserialize(str);
    node->right = Deserialize(str);
    return node;
}
Node* Deserialize(char *str) {
    if (str == nullptr)
        return nullptr;
    Node *ret = Deserialize(&str);
    return ret;
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
    char *temp = Serialize(head_1);
    cout << "Serialize: " << temp << endl;
    printTree(Deserialize(temp));
    cout << "=============================================" << endl;
    printTree(head_2);
    cout << "=============================================" << endl;
    temp = Serialize(head_2);
    cout << "Serialize: " << temp << endl;
    printTree(Deserialize(temp));
    cout << "=============================================" << endl;


    return 0;
}