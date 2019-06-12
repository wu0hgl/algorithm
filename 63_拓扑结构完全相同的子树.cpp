#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    给定彼此独立的两颗树头结点分别为t1和t2, 判断t1中是否有与t2树拓扑结构完全相同的子树
*/

class Node {
public:
    Node(int data) {
        this->value = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    int value;
    Node *left;
    Node *right;
};

string getSpace(int num);
void printInOrder(Node *head, int height, string to, int len);
void printTree(Node *head);
void preOrderRecur(Node *head);
void inOrderRecur(Node *head);


string serialByPre(Node *head) {
    if (head == nullptr) {
        return "#!";
    }
    string res = to_string(head->value) + "!";
    res += serialByPre(head->left);
    res += serialByPre(head->right);
    return res;
}

vector<int> getNextArray(string &m) {
    vector<int> next;
    if (m.size() == 1) {
        next.push_back(-1);
        return next;
    }
    next.resize(m.size());
    next[0] = -1;
    next[1] = 0;
    int cnt = 0;
    int pos = 2;
    while (pos < m.size()) {
        if (m[pos - 1] == m[cnt]) {
            next[pos++] = ++cnt;
        }
        else if (cnt > 0) {
            cnt = next[cnt];
        }
        else {
            next[pos++] = 0;
        }
    }

    return next;
}

int getIndexOf(string &s, string &m) {
    if ((s.size() == 0) || (m.size() == 0) || (s.size() < m.size())) {
        return -1;
    }
    vector<int> next = getNextArray(m);
    int si = 0;
    int mi = 0;
    while ((si < s.size()) && (mi < m.size())) {
        if (s[si] == m[mi]) {
            si++;
            mi++;
        }
        else if (next[mi] == -1) {
            si++;
        }
        else {
            mi = next[mi];
        }
    }

    return (mi == m.size() ? si - mi : -1);
}


bool isSubtree(Node *t1, Node *t2) {
    string t1Str = serialByPre(t1);
    string t2Str = serialByPre(t2);
    return (getIndexOf(t1Str, t2Str) != -1);
}

int main() {
    Node *t1 = &Node(1);
    t1->left = &Node(2);
    t1->right = &Node(3);
    t1->left->left = &Node(4);
    t1->left->right = &Node(5);
    t1->right->left = &Node(6);
    t1->right->right = &Node(7);
    t1->left->left->right = &Node(8);
    t1->left->right->left = &Node(9);

    Node *t2 = &Node(2);
    t2->left = &Node(4);
    t2->left->right = &Node(8);
    t2->right = &Node(5);
    t2->right->left = &Node(9);

    //t2->right->left->left = &Node(9);

    printTree(t1);
    printTree(t2);

    cout << isSubtree(t1, t2) << endl;

    return 0;
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
