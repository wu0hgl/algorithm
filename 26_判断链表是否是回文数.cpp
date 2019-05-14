#include <iostream>
#include <stack>
using namespace std;

/*
    给定一个链表的头结点head, 判断该链表是否是会问结构. 
    如: 1, 2, 1返回true; 1, 2, 2, 1返回true; 1, 2, 3返回false. 
    如果求时间复杂度O(N), 额外空间复杂度O(1)为isPalindrome_3
*/

class Node {
public:
    Node(int data) : value(data) { this->next = nullptr; }
    Node *next;
    int value;
};

bool isPalindrome_1(Node *head) {
    Node *ct = head;
    stack<Node *> sk;
    while (ct != nullptr) {
        sk.push(ct);
        ct = ct->next;
    }
    ct = head;
    while (ct != nullptr) {
        if (ct->value != sk.top()->value) {
            return false;
        }
        ct = ct->next;
        sk.pop();
    }

    return true;
}

bool isPalindrome_2(Node *head) {
    if ((head == nullptr) || (head->next == nullptr)) {
        return true;
    }
    Node *ctSlow = head->next;
    Node *ctFast = head;
    stack<Node *> sk;
    while ((ctFast->next != nullptr) && (ctFast->next->next != nullptr)) {
        ctSlow = ctSlow->next;
        ctFast = ctFast->next->next;
    }
    while (ctSlow != nullptr) {
        sk.push(ctSlow);
        ctSlow = ctSlow->next;
    }
    while (!sk.empty()) {
        if (head->value != sk.top()->value) {
            return false;
        }
        sk.pop();
        head = head->next;
    } 

    return true;
}

bool isPalindrome_3(Node *head) {
    if ((head == nullptr) || (head->next == nullptr)) {
        return true;
    }
    Node *ctSlow = head;
    Node *ctFast = head;
    while ((ctFast->next != nullptr) && (ctFast->next->next)) {
        ctSlow = ctSlow->next;
        ctFast = ctFast->next->next;
    }

    ctFast = ctSlow->next;      // ctFast相当于head
    ctSlow->next = nullptr;     // ctSlow相当于prePtr
    Node *n1 = nullptr;         // n1相当于next
    while (ctFast != nullptr) {
        n1 = ctFast->next;
        ctFast->next = ctSlow;
        ctSlow = ctFast;
        ctFast = n1;
    }

    n1 = ctSlow;                // ctSlow相当于反转链表后的头结点
    ctFast = head;
    bool res = true;
    while ((ctSlow != nullptr) && (ctFast != nullptr)) {
        if (ctSlow->value != ctFast->value) {
            res = false;
            break;
        }
        ctSlow = ctSlow->next;
        ctFast = ctFast->next;
    }

    ctSlow = n1->next;      // 相当于head
    n1->next = nullptr;     // 相当于prePtr
    while (ctSlow != nullptr) {
        ctFast = ctSlow->next;  // ctFast相当于nextPtr
        ctSlow->next = n1;
        n1 = ctSlow;
        ctSlow = ctFast;
    }

    return res;
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
    Node *head = nullptr;
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;
    
    head = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(2);
    head->next->next->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(3);
    head->next->next->next->next->next = new Node(2);
    head->next->next->next->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;

    head = new Node(2);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(3);
    head->next->next->next->next->next = new Node(2);
    head->next->next->next->next->next->next = new Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    freeLinkList(head);
    cout << "========================================" << endl;


    return 0;
}


