#include <iostream>
#include <string>
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
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

void process_1(Node *root, string &str) {
    if (root == nullptr) {
        str += "#!";
        return;
    }
    str += to_string(root->value) + '!';
    process_1(root->left, str);
    process_1(root->right, str);
}
string Serialize(Node *root) {
    if (root == nullptr)
        return nullptr;
    string str;
    process_1(root, str);
    return str;
}

Node* process_2(string& str, int& pos) {
    if (str[pos] == '#' && str[pos + 1] == '!') {
        pos = pos + 2;
        return nullptr;
    }
    int num = 0;
    while (str[pos] != '!' && pos != str.size()) {
        //cout << str[pos] << " " << str[pos] - '0' << endl;
        num = num * 10 + str[pos] - '0';
        pos++;
    }
    Node* node = new Node(num);
    if (pos == str.size())
        return node;
    else
        pos++;

    node->left = process_2(str, pos);
    node->right = process_2(str, pos);

    return node;
}
Node* Deserialize(string str) {
    if (str.size() == 0)
        return nullptr;
    int pos = 0;
    Node *ret = process_2(str, pos);
    return ret;
}

int main() {
    Node *head_1 = &Node(11);
    head_1->left = &Node(22);
    head_1->right = &Node(33);
    head_1->left->left = &Node(44);
    head_1->left->right = &Node(55);
    head_1->right->left = &Node(66);
    head_1->right->right = &Node(77);

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
    string temp = Serialize(head_1);
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