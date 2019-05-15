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
    if ((pHead == nullptr) || (pHead->next == nullptr) || (pHead->next->next == nullptr))
        return nullptr;
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

void freeLinkList(Node *head) {
    while (nullptr != head) {
        Node* temp = head->next;
        head->next = nullptr;
        free(head);
        head = temp;
    }
}

int main() {
    // 1->2->3->4->5->6->7->null
    Node *head1 = new Node(1);
    Node *temp = nullptr;
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = new Node(7);
    //temp = EntryNodeOfLoop_1(head1);
    temp = EntryNodeOfLoop_2(head1);
    if (temp == nullptr)
        cout << "无换" << endl;
    else {
        cout << "有换, 入口: " << endl;
    }
    freeLinkList(head1);

    // 1->2->3->4->5->6
    head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = head1->next->next->next;    // 6->4
    //temp = EntryNodeOfLoop_1(head1);
    temp = EntryNodeOfLoop_2(head1);
    if (temp == nullptr)
        cout << "无换" << endl;
    else {
        cout << "有换, 入口: " << temp->value << endl;
    }
    //freeLinkList(head1);    // 有环情况释放节点有问题

    return 0;
}