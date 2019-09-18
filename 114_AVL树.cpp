#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct  Node {
    Node(int v, int h) : value(v), height(h), left(nullptr), right(nullptr) {}
    int value;
    int height;
    Node* left;
    Node* right;
};
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

int Height(Node* head) {
    return head == nullptr ? -1 : head->height;
}

Node* LL(Node* head) {
    Node* temp = head->left;
    head->left = temp->right;
    temp->right = head;

    head->height = max(Height(head->left), Height(head->right)) + 1;
    temp->height = max(Height(temp->left), Height(head)) + 1;
    return temp;
}

Node* RR(Node* head) {
    Node* temp = head->right;
    head->right = temp->left;
    temp->left = head;

    head->height = max(Height(head->left), Height(head->right)) + 1;
    temp->height = max(Height(temp->right), Height(head)) + 1;

    return temp;
}

Node* LR(Node* head) {
    head->left = RR(head->left);
    return LL(head);
}

Node* RL(Node* head) {
    head->right = LL(head->right);
    return RR(head);
}

Node* insert(int value, Node* node) {
    if (node == nullptr) {
        node = new Node(value, 0);
    }
    else if (value < node->value) {
        node->left = insert(value, node->left);
        if (Height(node->left) - Height(node->right) == 2) {
            if (value < node->left->value)
                node = LL(node);
            else
                node = LR(node);
        }
    }
    else if (value > node->value) {
        node->right = insert(value, node->right);
        if (Height(node->right) - Height(node->left) == 2) {
            if (value > node->right->value)
                node = RR(node);
            else
                node = RL(node);
        }
    }
    node->height = max(Height(node->left), Height(node->right)) + 1;
    return node;
}

void test_1() {
    Node* n1 = new Node(1, 0);
    Node* head = nullptr;
    head = insert(2, n1);
    head = insert(3, head);
    head = insert(4, head);
    head = insert(5, head);
    head = insert(6, head);
    head = insert(7, head);
    printTree(head);
}

void test_2() {
    Node* n1 = new Node(7, 0);
    Node* head = nullptr;
    head = insert(6, n1);
    head = insert(5, n1);
    head = insert(4, head);
    head = insert(3, head);
    head = insert(2, head);
    head = insert(1, head);
    printTree(head);
}

int main() {
    test_1();
    cout << "================" << endl;
    test_2();
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