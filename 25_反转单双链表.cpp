#include <iostream>
using namespace std;

/*
    反转单双链表
*/

class ListNode {
public:
    ListNode(int data) { value = data; next = nullptr; }
    ListNode *next;
    int value;
};

ListNode* ReverseList(ListNode* head) {
    if ((nullptr == head) || (head->next == nullptr)) {
        return head;
    }
    ListNode* ret = ReverseList(head->next);
    head->next->next = head;        // 当前节点下一节点的next指向当前节点
    head->next = nullptr;           // 当前节点next指向空
    return ret;
}

ListNode* reverseList(ListNode *head) {
    ListNode *pre = nullptr;
    ListNode *next = nullptr;

    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }

    return pre;
}

void printList(ListNode *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

class DoubleNode {
public:
    int value;
    DoubleNode *last;
    DoubleNode *next;
    DoubleNode(int data) { this->value = data;  last = next = nullptr; }
};

DoubleNode* reverseDoubleList(DoubleNode *head) {
    DoubleNode *pre = nullptr;
    DoubleNode *next = nullptr;

    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        head->last = next;
        pre = head;
        head = next;
    }
    return pre;
}

void printDoubleList(DoubleNode *head) {
    DoubleNode *end = nullptr;
    cout << "双链表从头到尾: ";
    while (head != nullptr) {
        cout << head->value << " ";
        end = head;
        head = head->next;
    }
    cout << endl << "双链表从尾到头: ";
    while (end != nullptr) {
        cout << end->value << " ";
        end = end->last;
    }
    cout << endl;
}

int main() {
    ListNode n1(1), n2(2), n3(3);
    n1.next = &n2;
    n1.next->next = &n3;
    printList(&n1);

    ListNode *temp = nullptr;
    temp = ReverseList(&n1);
    cout << "---------------------------" << endl;
    printList(temp);
    cout << "---------------------------" << endl;
    temp = reverseList(temp);
    printList(temp);
    cout << "---------------------------" << endl;
    DoubleNode dn1(1), dn2(2), dn3(3), dn4(4);
    dn1.next = &dn2;
    dn1.next->next = &dn3;
    dn1.next->next->next = &dn4;
    dn4.last = &dn3;
    dn4.last->last = &dn2;
    dn4.last->last->last = &dn1;
    printDoubleList(&dn1);
    DoubleNode *temp_1 = reverseDoubleList(&dn1);
    printDoubleList(temp_1);
    return 0;
}