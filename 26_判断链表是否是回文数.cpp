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
void printLinkList(Node *head);

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
    Node *ctSlow = head;            // 遍历结束时指向, 偶数个元素指向中间节点前一个节点, 奇数个元素时指向中间节点
    // 与上面效果相同, 只是最后sk中多比较一个元素
    //Node *ctSlow = head->next;    // 遍历结束时指向, 偶数个元素指向中间节点后一个节点, 奇数个元素时指向中间节下一个点
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
    Node *ctSlow = head;                // 偶数个节点到中间两节点前一位置, 奇数恰好到中间节点
    Node *ctFast = head;
    while ((ctFast->next != nullptr) && (ctFast->next->next != nullptr)) {
        ctSlow = ctSlow->next;
        ctFast = ctFast->next->next;
    }

    /* 反转以ctSlow开头的单链表 */
    ctFast = ctSlow->next;              // 相当于node
    ctSlow->next = nullptr;             // 相当于pre
    Node *node = nullptr;               // 相当于next
    while (ctFast != nullptr) {
        node = ctFast->next;
        ctFast->next = ctSlow;
        ctSlow = ctFast;
        ctFast = node;
    }
    node = ctSlow;                      // 保存翻转后链表的头结点

    /* 匹配数字 */
    bool ret = true;
    ctFast = head;
    while ((ctFast != nullptr)) {       // 不能使用ctSlow来判断
        if (ctFast->value != ctSlow->value) {
            ret = false;
            break;
        }
        ctFast = ctFast->next;
        ctSlow = ctSlow->next;
    }

    /* 恢复链表 */
    ctSlow = node->next;                // 相当于node
    node->next = nullptr;               // 相当于pre
    while (ctSlow != nullptr) {
        ctFast = ctSlow->next;          // 相当于next
        ctSlow->next = node;
        node = ctSlow;
        ctSlow = ctFast;
    }

    return ret;
}

int main() {
    Node *head = nullptr;
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;
    
    head = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(3);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(3);
    head->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(2);
    head->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(3);
    head->next->next->next = &Node(3);
    head->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(3);
    head->next->next->next = &Node(3);
    head->next->next->next->next = &Node(2);
    head->next->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(4);
    head->next->next->next = &Node(3);
    head->next->next->next->next = &Node(2);
    head->next->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(3);
    head->next->next->next = &Node(4);
    head->next->next->next->next = &Node(3);
    head->next->next->next->next->next = &Node(2);
    head->next->next->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(2);
    head->next = &Node(2);
    head->next->next = &Node(3);
    head->next->next->next = &Node(4);
    head->next->next->next->next = &Node(3);
    head->next->next->next->next->next = &Node(2);
    head->next->next->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    head = &Node(1);
    head->next = &Node(2);
    head->next->next = &Node(2);
    head->next->next->next = &Node(4);
    head->next->next->next->next = &Node(3);
    head->next->next->next->next->next = &Node(2);
    head->next->next->next->next->next->next = &Node(1);
    printLinkList(head);
    cout << isPalindrome_1(head) << " | ";
    cout << isPalindrome_2(head) << " | ";
    cout << isPalindrome_3(head) << endl;
    printLinkList(head);
    cout << "========================================" << endl;

    return 0;
}

void printLinkList(Node *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}