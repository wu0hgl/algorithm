#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

/*
    判断单链表是否有环
*/

class Node {
public:
    Node(int data) : value(data) { next = nullptr; }
    int value;
    Node *next;
};

Node* EntryNodeOfLoop_1(Node* pHead)
{
    if ((pHead == nullptr) || (pHead->next == nullptr) || (pHead->next->next == nullptr))
        return nullptr;

    /* 这么初始化快慢指针下面的while循环为true */
    //Node *ptrFast = pHead;
    //Node *ptrSlow = pHead;

    Node *ptrFast = pHead->next->next;
    Node *ptrSlow = pHead->next;
 
    while (ptrFast != ptrSlow) {
        if ((ptrFast->next == nullptr) || (ptrFast->next->next == nullptr))
            return nullptr;
        ptrFast = ptrFast->next->next;
        ptrSlow = ptrSlow->next;
    }
    ptrFast = pHead;
    while (ptrSlow != ptrFast) {
        ptrFast = ptrFast->next;
        ptrSlow = ptrSlow->next;
    }
    return ptrFast;
}

Node* EntryNodeOfLoop_2(Node* pHead)
{
    set<Node *> mySet;
    while (pHead != nullptr) {
        auto temp = find(mySet.begin(), mySet.end(), pHead);
        if (temp == mySet.end()) {
            mySet.insert(pHead);
            pHead = pHead->next;
        }
        else
            return pHead;
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

    temp = EntryNodeOfLoop_1(head1);
    if (temp == nullptr)
        cout << "无环" << endl;
    else {
        cout << "有环, 入口: " << endl;
    }
    temp = EntryNodeOfLoop_2(head1);
    if (temp == nullptr)
        cout << "无环" << endl;
    else {
        cout << "有环, 入口: " << endl;
    }
    cout << "====================================" << endl;

    // 1->2->3->4->5->6
    head1 = &Node(1);
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = head1->next->next->next;    // 6->4

    temp = EntryNodeOfLoop_1(head1);
    if (temp == nullptr)
        cout << "无环" << endl;
    else {
        cout << "有环, 入口: " << temp->value << endl;
    }
    temp = EntryNodeOfLoop_2(head1);
    if (temp == nullptr)
        cout << "无环" << endl;
    else {
        cout << "有环, 入口: " << temp->value << endl;
    }

    return 0;
}