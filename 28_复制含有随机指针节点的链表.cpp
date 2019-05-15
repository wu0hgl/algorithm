#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;
class Node {
public:
    Node(int data) : value(data) { this->next = nullptr; this->rand = nullptr; }
    Node *next;
    Node *rand;
    int value;
};

/*
    输入一个复杂链表(每个节点中有节点值, 以及两个指针, 一个指向下一个节点, 另一个特殊指针指向任意一个节点), 
    返回结果为复制后复杂链表的head. )注意，输出结果中请不要返回参数中的节点引用, 否则判题程序会直接返回空)
*/

Node* copyListWithRand_1(Node *pHead) {
    unordered_map<Node*, Node*> hMap;
    Node *ct = pHead;
    while (ct != nullptr) {
        Node *temp = new Node(ct->value);
        hMap[ct] = temp;
        ct = ct->next;
    }
    ct = pHead;
    while (ct != nullptr) {
        hMap[ct]->next = hMap[ct->next];
        hMap[ct]->rand = hMap[ct->rand];
        ct = ct->next;
    }
    return hMap[pHead];
}

Node* copyListWithRand_2(Node *pHead) {
    if (nullptr == pHead) {
        return nullptr;
    }
    Node *cur = pHead;
    Node *next = nullptr;
    while (cur != nullptr) {
        next = cur->next;
        cur->next = new Node(cur->value);
        cur->next->next = next;
        cur = next;

        //next = new Node(cur->value);
        //next->next = cur->next;
        //cur->next = next;
        //cur = next->next;
    }

    cur = pHead;
    Node *curCopy = nullptr;
    while (cur != nullptr) {
        next = cur->next->next;
        curCopy = cur->next;
        curCopy->rand = (cur->rand != nullptr ? cur->rand->next : nullptr);
        cur = next;
    }

    Node *res = pHead->next;
    cur = pHead;
    while (cur != nullptr) {
        next = cur->next->next;
        curCopy = cur->next;
        cur->next = next;
        curCopy->next = (next != nullptr ? next->next : nullptr);
        cur = next;
    }
    return res;
}

void printLinkList(Node *head) {
    cout << "order: ";
    Node *ct = head;
    while (ct != nullptr) {
        cout << ct->value << " ";
        ct = ct->next;
    }
    cout << endl;
    cout << "rand:  ";
    ct = head;
    while (ct != nullptr) {
        if (ct->rand == nullptr)
            cout << "- ";
        else
            cout << ct->rand->value << " ";
        ct = ct->next;
    }
    cout << endl;
}

void freeRandLinkList(Node *head) {
    while (nullptr != head) {
        Node* temp = head->next;
        free(head);
        head = temp;
    }
}

int main() {

    Node *head = new Node(1);
    Node *res_1 = nullptr;
    Node *res_2 = nullptr;
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    head->rand = head->next->next->next->next->next;        // 1 -> 6
    head->next->rand = head->next->next->next->next->next;  // 2 -> 6
    head->next->next->rand = head->next->next->next->next;  // 3 -> 5
    head->next->next->next->rand = head->next->next;        // 4 -> 3
    head->next->next->next->next->rand = nullptr;           // 5 -> null
    head->next->next->next->next->next->rand = head->next->next->next;  // 6 -> 4

    printLinkList(head);
    cout << "===================================" << endl;
    //head = listPartition_2(head, 5);
    res_1= copyListWithRand_1(head);
    printLinkList(res_1);
    cout << "===================================" << endl;
    res_2 = copyListWithRand_2(head);
    printLinkList(res_2);

    freeRandLinkList(head);
    freeRandLinkList(res_1);
    freeRandLinkList(res_2);
    return 0;
}