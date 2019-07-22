#include <iostream>
using namespace std;
class Node {
public:
    Node(int data) { value = data; next = nullptr; }
    Node *next; int value;
};
void printList(Node *head);

/*
    输入一个链表, 输出该链表中倒数第k个结点
*/

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

int main() {
    int k = 7;
    Node *head1 = &Node(1);
    head1->next = &Node(2);
    head1->next->next = &Node(3);
    head1->next->next->next = &Node(4);
    head1->next->next->next->next = &Node(5);
    head1->next->next->next->next->next = &Node(6);
    head1->next->next->next->next->next->next = &Node(7);
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

void printList(Node *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}