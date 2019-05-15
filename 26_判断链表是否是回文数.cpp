#include <iostream>
#include <stack>
using namespace std;

/*
    ����һ�������ͷ���head, �жϸ������Ƿ��ǻ��ʽṹ. 
    ��: 1, 2, 1����true; 1, 2, 2, 1����true; 1, 2, 3����false. 
    �����ʱ�临�Ӷ�O(N), ����ռ临�Ӷ�O(1)ΪisPalindrome_3
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
    Node *ctSlow = head;                // ż�����ڵ㵽�м����ڵ�ǰһλ��, ����ǡ�õ��м�ڵ�
    Node *ctFast = head;
    while ((ctFast->next != nullptr) && (ctFast->next->next != nullptr)) {
        ctSlow = ctSlow->next;
        ctFast = ctFast->next->next;
    }
    /* ��ת��ctSlow��ͷ�ĵ����� */
    ctFast = ctSlow->next;              // �൱��head
    ctSlow->next = nullptr;             // �൱��prePtr
    Node *node = nullptr;               // �൱��next
    while (ctFast != nullptr) {
        node = ctFast->next;
        ctFast->next = ctSlow;
        ctSlow = ctFast;
        ctFast = node;
    }
    node = ctSlow;                      // ���淭ת�������ͷ���
    /* ƥ������ */
    bool ret = true;
    ctFast = head;
    while ((ctFast != nullptr)) {
        if (ctFast->value != ctSlow->value) {
            ret = false;
            break;
        }
        ctFast = ctFast->next;
        ctSlow = ctSlow->next;
    }
    /* �ָ����� */
    ctSlow = node->next;                // �൱��head
    node->next = nullptr;               // �൱��prePtr
    while (ctSlow != nullptr) {
        ctFast = ctSlow->next;          // �൱��nextPtr
        ctSlow->next = node;
        node = ctSlow;
        ctSlow = ctFast;
    }

    return ret;
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


