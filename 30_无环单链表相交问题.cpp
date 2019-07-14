#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

/*
    无环单链表相交问题
*/

class Node {
public:
    Node(int data) : value(data) { next = nullptr; }
    int value;
    Node *next;
};

Node* FindFirstCommonNode_1(Node* pHead1, Node* pHead2) {
    if ((pHead1 == nullptr) || (pHead2 == nullptr)) {
        return nullptr;
    }
    Node *cur1 = pHead1;
    Node *cur2 = pHead2;
    int count = 0;
    while (cur1->next != nullptr) {
        count++;
        cur1 = cur1->next;
    }
    while (cur2->next != nullptr) {
        count--;
        cur2 = cur2->next;
    }
    if (cur1 != cur2)
        return nullptr;

    cur1 = (count > 0 ? pHead1 : pHead2);       // count>0: pHead1链表长, count<0: pHead2链表长, cur1指向长链表头节点
    cur2 = (cur1 == pHead1 ? pHead2 : pHead1);  // cur2指向短链表的节点

    count = abs(count);                         // 计数值取绝对值
    while (count != 0) {
        cur1 = cur1->next;
        count--;
    }
    while ((cur1 != cur2) && (cur1 != nullptr) && (cur2 != nullptr)) {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    //return cur1;
    return (cur1 == cur2 ? cur1 : nullptr);     // 这么判断更保险一些
}

Node* FindFirstCommonNode_2(Node* pHead1, Node* pHead2) {
    unordered_set<Node*> mySet;
    Node *ct1 = pHead1;
    while (ct1 != nullptr) {
        mySet.insert(ct1);
        ct1 = ct1->next;
    }
    ct1 = pHead2;
    while (ct1 != nullptr) {
        auto temp = find(mySet.begin(), mySet.end(), ct1);
        if (temp != mySet.end()) {
            return ct1;
        }
        ct1 = ct1->next;
    }
    return nullptr;
}

int main() {
    // 1->2->3->4->5->6->7->null
    Node *head1 = &Node(1);
    Node *temp = nullptr;
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = &Node(7);

    // 8->9->10->4
    Node *head2 = &Node(8);
    head2->next = &Node(9);
    head2->next->next = &Node(10);
    head2->next->next->next = head1->next->next->next;  // 4
    //head2->next->next->next = &Node(5);
    //head2->next->next->next->next = &Node(6);
    //head2->next->next->next->next->next = nullptr;

    temp = FindFirstCommonNode_1(head1, head2);
    if (temp == nullptr)
        cout << "无公共节点" << endl;
    else {
        cout << "有公共节点: " << temp->value << endl;
    }

    cout << "=============================" << endl;

    temp = FindFirstCommonNode_2(head1, head2);
    if (temp == nullptr)
        cout << "无公共节点" << endl;
    else {
        cout << "有公共节点: " << temp->value << endl;
    }

    return 0;
}