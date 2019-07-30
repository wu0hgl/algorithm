#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* 
    给定一棵二叉树的头节点head, 请返回最大搜索二叉子树的大小
*/

class Node {
public:
    Node(int value) : value(value) { left = nullptr; right = nullptr; }
    int value;
    Node *left;
    Node *right;
};
void printTree(Node *head);
void printInOrder(Node *head, int height, string to, int len);
string getSpace(int num);

class ReturnType {
public:
    ReturnType(int a, Node* b, int c, int d) {
        this->size = a;
        this->head = b;
        this->min = c;
        this->max = d;
    }
    int size;
    Node* head;
    int min;
    int max;
};

ReturnType process(Node* head) {
    if (head == nullptr) {
        return ReturnType(0, nullptr, INT_MAX, INT_MIN);
    }
    Node *left = head->left;
    ReturnType leftSubTressInfo = process(left);    // 左树递归返回
    Node *right = head->right;
    ReturnType rightSubTressInfo = process(right);  // 右树递归返回

    int includeItSelf = 0;
    if ((leftSubTressInfo.head == left)             // 左树最大搜索二叉树头部是当前节点左孩子
        && (rightSubTressInfo.head == right)        // 右树最大搜索二叉树头部是当前节点右孩子
        /* 上两个条件满足的情况下, 左树就是左子树, 右树就是右子树 */
        && (head->value > leftSubTressInfo.max)     // 当前节点值大于左子树最大值
        && (head->value < rightSubTressInfo.min)) { // 当前节点值小于右子树最小值

        includeItSelf = leftSubTressInfo.size + 1 + rightSubTressInfo.size;     // 更新数量
    }

    /* 构造返回结构size */
    int p1 = leftSubTressInfo.size;
    int p2 = rightSubTressInfo.size;
    int maxSize = max(max(p1, p2), includeItSelf);

    /* 构造返回结构头节点 */
    Node *maxHead = p1 > p2 ? leftSubTressInfo.head : rightSubTressInfo.head;
    if (maxSize == includeItSelf) {
        maxHead = head;
    }

    return ReturnType(maxSize,
                      maxHead,
                      min(min(leftSubTressInfo.min, rightSubTressInfo.min), head->value),
                      max(max(leftSubTressInfo.max, rightSubTressInfo.max), head->value)
                      );
}
Node* biggestSubBST_1(Node* head) {
    ReturnType ret = process(head);
    return ret.head;
}

Node* posOrder(Node* head, vector<int>& record) {
    if (head == nullptr) {          // 节点作为返回值
        record[0] = 0;              // size
        record[1] = INT_MAX;        // min
        record[2] = INT_MIN;        // max
        return nullptr;
    }

    int value = head->value;
    Node *left = head->left;
    Node *right = head->right;

    Node *lBST = posOrder(left, record);
    int lSize = record[0];
    int lMin = record[1];
    int lMax = record[2];

    Node *rBST = posOrder(right, record);
    int rSize = record[0];
    int rMin = record[1];
    int rMax = record[2];

    record[1] = min(rMin, min(lMin, value));
    record[2] = max(rMax, max(rMax, value));
    if ((left == lBST) && (right == rBST) && (value > lMax) && (value < rMin)) {
        record[0] = lSize + 1 + rSize;
        return head;
    }
    record[0] = max(lSize, rSize);
    return (lSize > rSize ? lBST : rBST);
}
Node* biggestSubBST_2(Node* head) {
    vector<int> record = vector<int>(3, 0);
    return posOrder(head, record);
}

int main() {
    Node* head = &Node(6);
    head->left = &Node(1);
    head->left->left = &Node(0);
    head->left->right = &Node(3);
    head->right = &Node(12);
    head->right->left = &Node(10);
    head->right->left->left = &Node(4);
    head->right->left->left->left = &Node(2);
    head->right->left->left->right = &Node(5);
    head->right->left->right = &Node(14);
    head->right->left->right->left = &Node(11);
    head->right->left->right->right = &Node(15);
    head->right->right = &Node(13);
    head->right->right->left = &Node(20);
    head->right->right->right = &Node(16);

    printTree(head);
    cout << "================================" << endl;
    printTree(biggestSubBST_1(head));
    cout << "================================" << endl;
    printTree(biggestSubBST_2(head));

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