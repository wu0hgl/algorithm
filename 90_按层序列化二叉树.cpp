#include <iostream>
#include <queue>
#include <string>
using namespace std;

/*
    二叉树按层序列化
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

string Serialize(Node *head) {
    if (head == nullptr) {
        return "#!";
    }
    string res = to_string(head->value) + "!";
    queue<Node*> q;
    q.push(head);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if (cur->left != nullptr) {
            res += to_string(cur->left->value) + "!";
            q.push(cur->left);
        }
        else {
            res += "#!";
        }
        if (cur->right != nullptr) {
            res += to_string(cur->right->value) + "!";
            q.push(cur->right);
        }
        else {
            res += "#!";
        }
    }
    return res;
}

vector<string> split(string& str1, const string& str2) {
    vector<string> res;
    size_t start = 0;
    //size_t pos = str1.find("!");
    size_t pos = str1.find(str2);
    while (pos != string::npos) {
        if (pos > start) {
            res.push_back(str1.substr(start, pos - start));
        }
        start = pos + 1;
        pos = str1.find("!", start);
    }

    if (start < str1.size()) {
        res.push_back(str1.substr(start));
    }
    return res;
}

Node* generateNodeByString(string& str) {
    if (str == "#") {
        return nullptr;
    }
    else {
        int num = 0;
        for (size_t i = 0; i < str.size(); i++) {
            num = num * 10 + (str[i] - '0');
        }
        return new Node(num);
    }
}

Node* Deserialize(string str) {
    vector<string> values = split(str, "!");
    if (values.size() == 0) {
        return nullptr;
    }
    int index = 0;
    Node *head = generateNodeByString(values[index++]);
    queue<Node*> q;
    if (head != nullptr) {
        q.push(head);
    }
    while (!q.empty()) {
        Node *cur = nullptr;
        cur = q.front();
        q.pop();
        cur->left = generateNodeByString(values[index++]);
        cur->right = generateNodeByString(values[index++]);
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
    }

    return head;
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
    string temp = Serialize(head_1);
    cout << "Serialize: " << temp.c_str() << endl;
    printTree(Deserialize(temp));
    cout << "=============================================" << endl;
    printTree(head_2);
    cout << "=============================================" << endl;
    temp = Serialize(head_2);
    cout << "Serialize: " << temp.c_str() << endl;
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