#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};
void preOrderRecur(Node *head);
void inOrderRecur(Node *head);
void posOrderRecur(Node *head);
string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);

/*
    给定一颗二叉树的头节点head, 完成二叉树的先序, 中序和后序遍历. 
    如果二叉树的节点数为N, 则要求时间复杂度为O(N), 额外空间复杂度O(1)
*/

void morris(Node *head) {
    if (head == nullptr) {
        return;
    }
    Node *cur = head;
    Node *mostRight = nullptr;
    while (cur != nullptr) {
        mostRight = cur->left;
        if (mostRight != nullptr) { // 当前节点cur有左子树
            /* 找到cur左子树上最右节点 */
            while ((mostRight->right != nullptr) && (mostRight->right != cur)) {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cout << cur->value << " ";
                cur = cur->left;
                continue;
            }
            else {
                mostRight->right = nullptr;
            }
        }
        cout << cur->value << " ";
        cur = cur->right;
    }
    cout << endl;
}

void morrisPre(Node *head) {
    if (head == nullptr) {
        return;
    }
    Node *cur = head;
    Node *mostRight = nullptr;
    while (cur != nullptr) {
        mostRight = cur->left;
        if (mostRight != nullptr) {
            while ((mostRight->right != nullptr) && (mostRight->right != cur)){
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cout << cur->value << " ";
                cur = cur->left;
                continue;
            }
            else {
                mostRight->right = nullptr;
            }
        }
        else {
            cout << cur->value << " ";
        }
        cur = cur->right;
    }
    cout << endl;
}

void morrisIn(Node *head) {
    if (head == nullptr) {
        return;
    }
    Node *cur = head;
    Node *mostRight = nullptr;
    while (cur != nullptr) {
        mostRight = cur->left;
        if (mostRight != nullptr) {
            while ((mostRight->right != nullptr) && (mostRight->right != cur)) {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {
                mostRight->right = nullptr;
            }
        }
        cout << cur->value << " ";
        cur = cur->right;
    }
    cout << endl;
}

Node* reverseEdge(Node *from) {
    Node *pre = nullptr;
    Node *next = nullptr;
    while (from != nullptr) {
        next = from->right;
        from->right = pre;
        pre = from;
        from = next;
    }
    return pre;
}

void printEdge(Node *head) {
    Node *tail = reverseEdge(head);
    Node *cur = tail;
    while (cur != nullptr) {
        cout << cur->value << " ";
        cur = cur->right;
    }
    reverseEdge(tail);
}
void morrisPos(Node *head) {
    if (head == nullptr) {
        return;
    }
    Node *cur = head;
    Node *mostRight = nullptr;
    while (cur != nullptr) {
        mostRight = cur->left;
        if (mostRight != nullptr) {
            while ((mostRight->right != nullptr) && (mostRight->right != cur)) {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {
                mostRight->right = nullptr;
                printEdge(cur->left);
            }
        }
        cur = cur->right;
    }
    printEdge(head);
    cout << endl;
}

int main() {
    Node *head = &Node(5);
    head->left = &Node(3);
    head->right = &Node(8);
    head->left->left = &Node(2);
    head->left->right = &Node(4);
    head->left->left->left = &Node(1);
    head->right->left = &Node(7);
    head->right->left->left = &Node(6);
    head->right->right = &Node(10);
    head->right->right->left = &Node(9);
    head->right->right->right = &Node(11);

    printTree(head);
    morris(head);
    cout << "=====================================" << endl;

    preOrderRecur(head);
    cout << endl;
    morrisPre(head);
    cout << "=====================================" << endl;

    inOrderRecur(head);
    cout << endl;
    morrisIn(head);
    cout << "=====================================" << endl;

    posOrderRecur(head);
    cout << endl;
    morrisPos(head);

    return 0;
}

void preOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    cout << head->value << " ";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

void inOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    inOrderRecur(head->left);
    cout << head->value << " ";
    inOrderRecur(head->right);
}

void posOrderRecur(Node *head) {
    if (head == nullptr)
        return;
    posOrderRecur(head->left);
    posOrderRecur(head->right);
    cout << head->value << " ";
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