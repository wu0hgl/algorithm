#include <iostream>
#include <stack>
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
void inOrder(Node *head);

/*
    判断一课二叉树是否是搜索二叉树
*/

bool isBST_1(Node *head) {
    Node *cur = head;
    Node *pre = nullptr;
    stack<Node *>sk;
    while ((!sk.empty()) || (cur != nullptr)) {
        if (cur != nullptr) {
            sk.push(cur);
            cur = cur->left;
        }
        else {
            cur = sk.top();
            sk.pop();

            /* 二叉树中序遍历非递归版增加三行代码 */
            if ((pre != nullptr) && (cur->value <= pre->value))
                return false;
            pre = cur;

            cur = cur->right;
        }
    }
    return true;
}

bool isBST_2(Node *head) {
    if (head == nullptr) {
        return true;
    }
    bool res = true;
    Node *pre = nullptr;
    Node *cur1 = head;
    Node *cur2 = nullptr;
    while (cur1 != nullptr) {
        cur2 = cur1->left;
        if (cur2 != nullptr) {
            while (cur2->right != nullptr && cur2->right != cur1) {
                cur2 = cur2->right;
            }
            if (cur2->right == nullptr) {
                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }
            else {
                cur2->right = nullptr;
            }
        }
        if (pre != nullptr && pre->value > cur1->value) {
            res = false;
        }
        pre = cur1;
        cur1 = cur1->right;
    }
    return res;
}

bool process_12(Node* head, bool flag) {
    if (flag) {
        Node* next = head->left;
        while (next != nullptr) {
            if (next->value < head->value) {
                head = next;
                next = head->left;
            }
            else {
                return false;
            }
        }
        return true;
    }
    else {
        Node* next = head->right;
        while (next != nullptr) {
            if (next->value > head->value) {
                head = next;
                next = head->right;
            }
            else {
                return false;
            }
        }
        return true;
    }
}

// 只判断当前节点的左孩子与右孩子了
// 并没有判断整颗左子树与右子树中的最大值与最小值和当前节点是否满足二叉搜索树的条件
bool isBST_3(Node* head) {
    if (head == nullptr) {
        return true;
    }
    if (head->left == nullptr && (head->right == nullptr)) {
        return true;
    }
    if ((head->left != nullptr) && (head->right == nullptr)) {
        return process_12(head, true);
        //return (head->left->value < head->value);
    }
    if ((head->right != nullptr) && (head->left == nullptr)) {
        return process_12(head, false);
        //return head->right->value > head->value;
    }

    bool L = isBST_3(head->left);
    bool H = isBST_3(head->right);
    if (L && H
        && (head->left->value < head->value)
        && (head->right->value) > head->value) {
        return true;
    }
    else {
        return false;
    }
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

    Node* head_3 = &Node(10);
    head_3->left = &Node(5);
    head_3->right = &Node(15);
    head_3->right->left = &Node(6);
    head_3->right->right = &Node(20);

    Node* head_4 = &Node(1);
    head_4->right = &Node(4);
    head_4->right->right = &Node(3);

    cout << "head_1: ";
    inOrder(head_1);
    cout << endl;
    cout << "head_2: ";
    inOrder(head_2);
    cout << endl;
    cout << "================isBST_1===================" << endl;
    cout << "head_1: " << isBST_1(head_1) << endl;
    cout << "head_2: " << isBST_1(head_2) << endl;
    cout << "head_3: " << isBST_1(head_3) << endl;
    cout << "head_4: " << isBST_1(head_4) << endl;
    cout << "================isBST_2===================" << endl;
    cout << "head_1: " << isBST_2(head_1) << endl;
    cout << "head_2: " << isBST_2(head_2) << endl;
    cout << "head_3: " << isBST_2(head_3) << endl;
    cout << "head_4: " << isBST_2(head_4) << endl;
    cout << "================isBST_3===================" << endl;
    cout << "head_1: " << isBST_3(head_1) << endl;
    cout << "head_2: " << isBST_3(head_2) << endl;
    cout << "head_3: " << isBST_3(head_3) << endl;
    cout << "head_4: " << isBST_3(head_4) << endl;

    return 0;
}

void inOrder(Node *head) {
    if (head == nullptr) {
        return;
    }
    inOrder(head->left);
    cout << head->value << " ";
    inOrder(head->right);
}