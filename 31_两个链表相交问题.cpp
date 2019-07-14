#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

/*
    两个链表相交问题
    实现一个函数, 如果两个链表相交, 返回相交的第一个结点, 如果不相交返回nullptr. 
    如果链表1长度N, 链表2长度M, 要求时间复杂度O(M+N), 额外空间复杂度O(1)
*/

class Node {
public:
    Node(int data) : value(data) { next = nullptr; }
    int value;
    Node *next;
};

Node* getLoopNode(Node *pHead);
Node* noLoop(Node *pHead1, Node *pHead2);
Node* bothLoop(Node *pHead1, Node *loop1, Node *pHead2, Node *loop2);

Node* getIntersectNode(Node *pHead1, Node *pHead2) {
    if ((pHead1 == nullptr) || (pHead2 == nullptr)) {
        return nullptr;
    }
    Node *loop1 = getLoopNode(pHead1);
    Node *loop2 = getLoopNode(pHead2);

    /* 无环链表相交问题 */
    if ((loop1 == nullptr) && (loop2 == nullptr)) {     // 无环链表相交问题
        return noLoop(pHead1, pHead2);
    }
    
    /* 有环链表相交问题: (1)两个链表入口点相同; (2)两个链表的入口点不同; (3)两个链表对应的环不相交 */
    if ((loop1 != nullptr) && (loop2 != nullptr)) {     // 
        return bothLoop(pHead1, loop1, pHead2, loop2);
    }

    return nullptr;
}

Node* getLoopNode(Node *pHead) {
    if ((pHead == nullptr) || (pHead->next == nullptr) || (pHead->next->next == nullptr)) {
        return nullptr;
    }
    Node *ctSlow = pHead->next;
    Node *ctFast = pHead->next->next;
    while (ctFast != ctSlow)  {
        if ((ctFast->next == nullptr) || (ctFast->next->next == nullptr)) {
            return nullptr;
        }
        ctFast = ctFast->next->next;
        ctSlow = ctSlow->next;
    }
    
    ctFast = pHead;
    while (ctFast != ctSlow) {
        ctFast = ctFast->next;
        ctSlow = ctSlow->next;
    }

    return ctSlow;
}

Node* noLoop(Node *pHead1, Node *pHead2) {
    Node *cur1 = pHead1;
    Node *cur2 = pHead2;
    int count = 0;
    while (cur1->next != nullptr) {
        cur1 = cur1->next;
        count++;
    }
    while (cur2->next != nullptr) {
        cur2 = cur2->next;
        count--;
    }

    if (cur1 != cur2) {
        return nullptr;
    }

    cur1 = (count > 0 ? pHead1 : pHead2);
    cur2 = (cur1 == pHead1 ? pHead2 : pHead1);
    count = abs(count);
    while (count != 0) {
        count--;
        cur1 = cur1->next;
    }
    while (cur1 != cur2) {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}

Node* bothLoop(Node *pHead1, Node *loop1, Node *pHead2, Node *loop2) {
    Node *cur1 = nullptr;
    Node *cur2 = nullptr;
    if (loop1 == loop2) {   // 两个链表入口点相同, 转换为两无环链表相交问题
        cur1 = pHead1;
        cur2 = pHead2;
        int count = 0;
        while (cur1 != loop1) {
            count++;
            cur1 = cur1->next;
        }
        while (cur2 != loop1) {
            count--;
            cur2 = cur2->next;
        }
        cur1 = (count > 0 ? pHead1 : pHead2);
        cur2 = (cur1 == pHead1 ? pHead2 : pHead1);
        count = abs(count);
        while (count != 0) {
            count--;
            cur1 = cur1->next;
        }
        while (cur1 != cur2) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
        //return loop1;     // 返回相交的节点不是求换的入口节点
    }
    else {                  // 两个链表的入口点不同
        cur1 = loop1->next;
        while (cur1 != loop1) {
            if (cur1 == loop2) {
                return loop1;
            }
            cur1 = cur1->next;
        }
        return nullptr;     // 两个链表对应的环不相交
    }
}

int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}

void test_1() {
    // 1->2->3->4->5->6->7->null
    Node *head1 = &Node(1);
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = &Node(7);

    // 0->9->8->6->7->null
    Node *head2 = &Node(0);
    head2->next = &Node(9);
    head2->next->next = &Node(8);
    head2->next->next->next = head1->next->next->next->next->next; // 8->6
    cout << "无环: ";
    cout << getIntersectNode(head1, head2)->value << endl;
    cout << "==========================================" << endl;
}

void test_2() {
    // 1->2->3->4->5->6->7->4->->->
    Node *head1 = &Node(1);
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = &Node(7);
    head1->next->next->next->next->next->next = head1->next->next->next; // 7->4

    // 0->9->8->2->->->
    Node *head2 = &Node(0);
    head2->next = &Node(9);
    head2->next->next = &Node(8);
    head2->next->next->next = head1->next; // 8->2
    cout << "有环: ";
    cout << getIntersectNode(head1, head2)->value << endl;
    cout << "==========================================" << endl;
}

void test_3() {
    // 1->2->3->4->5->6->7->4->->->
    Node *head1 = &Node(1);
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = &Node(7);
    head1->next->next->next->next->next->next = head1->next->next->next; // 7->4

    // 0->9->8->6->4->5->6->->
    Node *head2 = &Node(0);
    head2->next = &Node(9);
    head2->next->next = &Node(8);
    head2->next->next->next = head1->next->next->next->next->next; // 8->6
    cout << "有环: ";
    cout << getIntersectNode(head1, head2)->value << endl;
    cout << "==========================================" << endl;
}