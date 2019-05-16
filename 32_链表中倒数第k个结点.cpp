#include <iostream>
using namespace std;

/*
反转单双链表
*/

class Node {
public:
    Node(int data) { value = data; next = nullptr; }
    Node *next;
    int value;
};

Node* FindKthToTail(Node* pListHead, unsigned int k) {
    Node *cur1 = pListHead;
    Node *ret = pListHead;
    int count = 0;
    while (cur1 != nullptr) {
        count++;
        cur1 = cur1->next;

        if (count > k) {
            ret = ret->next;
        }
    }
    return count >= k ? ret : nullptr;
}

void printList(Node *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int k = 7;
    Node *head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = new Node(7);
    printList(head1);

    Node *temp = nullptr;
    temp = FindKthToTail(head1, k);
    if (temp != nullptr) {
        cout << "倒数第" << k << "个节点: " << temp->value << endl;
    }
    else {
        cout << "倒数第" << k << "个节点为空" << endl;
    }
    return 0;
}