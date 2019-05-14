#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class Node {
public:
    Node(int data) : value(data) { this->next = nullptr; }
    Node *next;
    int value;
};

/*
    将单向链表按某值划分成左边小, 中间相等, 右边大的形式
*/

void partition(vector<Node*> &vt, int pivot) {
    int left = -1;
    int right = vt.size();
    int index = 0;
    while (index != right) {
        if (vt[index]->value < pivot) {
            swap(vt[++left], vt[index++]);
        }
        else if (vt[index]->value == pivot) {
            index++;
        }
        else {
            swap(vt[index], vt[--right]);
        }
    }
}

Node* listPartition_1(Node *head, int pivot) {
    if (nullptr == head) {
        return nullptr;
    }
    Node *ct = head;
    vector<Node *> arr;
    while (ct != nullptr) {
        arr.push_back(ct);
        ct = ct->next;
    }
    partition(arr, pivot);
    int i = 1;
    for (; i < arr.size(); i++) {
        arr[i - 1]->next = arr[i];
    }
    arr[i - 1]->next = nullptr;
    return arr[0];
}

Node* listPartition_2(Node *head, int pivot) {
    Node *sH = nullptr;
    Node *sT = nullptr;
    Node *eH = nullptr;
    Node *eT = nullptr;
    Node *bH = nullptr;
    Node *bT = nullptr;
    Node *ct = nullptr;
    while (head != nullptr) {
        ct = head->next;
        head->next = nullptr;
        if (head->value < pivot) {
            if (sH == nullptr) {
                sH = head;
                sT = head;
            }
            else {
                sT->next = head;
                sT = head;
            }
        }
        else if (head->value == pivot) {
            if (eH == nullptr) {
                eH = head;
                eT = head;
            }
            else {
                eT->next = head;
                eT = head;
            }
        }
        else {
            if (bH == nullptr) {
                bH = head;
                bT = head;
            }
            else {
                bT->next = head;
                bT = head;
            }
        }
        head = ct;
    }
    // small and equal reconnect
    if (sT != nullptr) {
        sT->next = eH;
        eT = eT == nullptr ? sT : eT;
    }
    // all reconnect
    if (eT != nullptr) {
        eT->next = bH;
    }
    return sH != nullptr ? sH : eH != nullptr ? eH : bH;
}

void printLinkList(Node *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

void freeLinkList(Node *head) {
    while (nullptr != head) {
        Node* temp = head->next;
        free(head);
        head = temp;
    }
}

int main() {
    Node *head = new Node(7);
    head->next = new Node(9);
    head->next->next = new Node(1);
    head->next->next->next = new Node(8);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(2);
    head->next->next->next->next->next->next = new Node(5);
    printLinkList(head);
    //head = listPartition_1(head, 3);
    head = listPartition_2(head, 5);
    printLinkList(head);

    freeLinkList(head);
    return 0;
}