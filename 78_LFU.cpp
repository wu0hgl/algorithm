#include <iostream>
#include <hash_map>
#include <map>
#include <memory>
using namespace std;

class Node {
public:
    Node(int key, int value, int time) {
        this->key = key;
        this->value = value;
        this->times = times;
        this->up = this->down = nullptr;
    }
    int key;
    int value;
    int times;
    shared_ptr<Node> up;
    shared_ptr<Node> down;
};

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->headList = nullptr;
    }

    void set(int key, int value) {
        if (this->capacity == 0) {
            return;
        }
        if (this->records.count(key)) {
            shared_ptr<Node> node = this->records[key];    // 通过key等到Node
            node->value = value;                // 设置新值
            node->times++;                      // 词频+1
            shared_ptr<NodeList> curNodeList = this->heads.at(node);  // 得到修改之前词频链表指针
            move(node, curNodeList);
        }
        else {
            if (this->size == this->capacity) {     // 容量已满, 先删除最不经常使用的
                shared_ptr<Node> node = this->headList->tail;  // 找到词频次数最少的链表的尾元素
                this->headList->deleteNode(node);
                modifyHeadList(this->headList);     // 调整头次频链表
                this->records.erase(node->key);     // 节点记录删除
                this->heads.erase(node);            // 词频链表记录删除
                this->size--;
            }
            shared_ptr<Node> node = shared_ptr<Node>(new Node(key, value, 1));
            if (this->headList == nullptr) {        // 词频链表的头指针为空, 即初始状态
                this->headList = shared_ptr<NodeList>(new NodeList(node));
            }
            else {
                if (this->headList->head->times == node->times) {   // 词频为1的链表存在
                    this->headList->addNodeFromHead(node);
                }
                else {                                              // 若不存在, 新建一个词频为1的链表
                    shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node));
                    newList->next = this->headList;
                    this->headList->pre = newList;
                    this->headList = newList;
                }
            }
            this->records.insert(pair<int, shared_ptr<Node>>(key, node));
            //this->records[key] = node;
            this->heads.insert(pair<shared_ptr<Node>, shared_ptr<NodeList>>(node, this->headList));
            //this->heads.insert[node] = this->headList;
            this->size++;
        }
    }

    int  get(int key) {
        if (!records.count(key)) {  // 不存在返回-1
            return -1;
        }
        shared_ptr<Node> node = this->records.at(key);
        node->times++;
        shared_ptr<NodeList> curNodeList = this->heads.at(node);  // 的到当前词频链表指针
        move(node, curNodeList);    // 把当前节点移向下一个词频链表
        return node->value;
    }

public:
    class NodeList {
    public:
        NodeList(shared_ptr<Node> node) {
            this->head = this->tail = node;
            this->pre = this->next = nullptr;
        }
        ~NodeList() {
            //while (!isEmpty()) {
            //    deleteNode(this->head);
            //}
        }

        void addNodeFromHead(shared_ptr<Node> newHead) {   // 新加链表不用调整tail指针, 
            newHead->down = this->head;
            this->head->up = newHead;
            this->head = newHead;
        }

        bool isEmpty() {
            return (this->head == nullptr);
        }

        void deleteNode(shared_ptr<Node> node) {            // 调用条件式node一定在链表中
            if (this->head == this->tail) { // 都为空或者只有一个节点(node一定在链表中, 还只剩一个节点了, 没必要判断head == node)
                this->head = this->tail = nullptr;
            }
            else {
                if (node == this->head) {
                    this->head = node->down;
                    this->head->up = nullptr;
                }
                else if (node == this->tail) {
                    this->tail = node->up;
                    this->tail->down = nullptr;
                }
                else {
                    node->up->down = node->down;
                    node->down->up = node->up;
                }
                node->up = nullptr;
                node->down = nullptr;
                //delete node;
            }
        }

        shared_ptr<Node> head;         // 词频链表内头指针
        shared_ptr<Node> tail;         // 词频链表内尾指针
        shared_ptr<NodeList> pre;      // 词频链表前一个节点
        shared_ptr<NodeList> next;     // 词频链表下一个节点
    };

    void move(shared_ptr<Node> node, shared_ptr<NodeList> oldNodeList) {
        oldNodeList->deleteNode(node);

        /* node进入一个新的词频链表, 找到这个新词频链表的前一个词频链表 */
        shared_ptr<NodeList> preList = modifyHeadList(oldNodeList) ? oldNodeList->pre // 旧词频链表没有元素被删除了, 找旧词频链表的前一个词频链表
            : oldNodeList;      // 就链表还有元素
        shared_ptr<NodeList> nextList = oldNodeList->next; // 就词频链表下一个
        if (nextList == nullptr) {                  // 原来所在词频链表是最高词频, 要去的新词频链表不存在
            shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node));
            /* 前后链表重连 */
            if (preList != nullptr) {
                preList->next = newList;
            }
            newList->pre = preList;
            if (this->headList == nullptr) {
                this->headList = newList;
            }
            /* 词频链表map记录 */
            this->heads.at(node) = newList;
        }
        else {
            if (nextList->head->times == node->times) { // 下一个链表的词频是当前节点的词频, 例如 3->4
                nextList->addNodeFromHead(node);
                this->heads.at(node) = nextList;
            }
            else {
                shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node)); // 下一个链表的词频不是当前节点的词频, 新建一个+1词频的链表,
                if (preList != nullptr) {               // 如原链表3->6, 新建一个4, 连链表3->4->6
                    preList->next = newList;
                }
                newList->pre = preList;
                newList->next = nextList;
                nextList->pre = newList;
                if (this->headList == nextList) {
                    this->headList = newList;
                }
                this->heads.at(node) = newList;
            }
        }
    }

    /* 调用时机: 把一个node从NodeLists中delete掉, 判断这个链表是否还需要存在 */
    bool modifyHeadList(shared_ptr<NodeList> nodeList) {
        if (nodeList->isEmpty()) {
            if (this->headList == nodeList) {       // 要删除的NodeList是否为整个链表的第一个词频链表
                /* 换头操作 */
                this->headList = nodeList->next;
                if (this->headList != nullptr) {    // 新头为空时, 表示大链表已经没有了;
                    this->headList->pre = nullptr;  // 新头不为空时, 要把新头的pre置null
                }
            }
            else {
                nodeList->pre->next = nodeList->next;
                if (nodeList->next != nullptr) {
                    nodeList->next->pre = nodeList->pre;
                }
            }
            return true;
        }
        return false;                           // 删除节点后NodeLists链表不为空, 直接返回
    }

    int capacity;                       // 容量
    int size;                           // 当前节点
    hash_map<int, shared_ptr<Node>> records;    // 节点记录, 即记录key值是否出现过
    hash_map<shared_ptr<Node>, shared_ptr<NodeList>> heads;     // 当前节所在词频链表的头节点
    shared_ptr<NodeList> headList;     // 保存第一词频链表
};

int main() {
    LFUCache test(3);
    test.set(2, 2);
    test.set(1, 1);
    cout << test.get(2) << endl;
    cout << test.get(1) << endl;
    cout << test.get(2) << endl;
    test.set(3, 3);
    test.set(4, 4);
    cout << test.get(3) << endl;
    cout << test.get(2) << endl;
    cout << test.get(1) << endl;
    cout << test.get(4) << endl;

    return 0;
}

/* LeetCode 测试版, 对空指针检查的有点BT
class Node {
public:
    Node(int key, int value, int time) {
        this->key = key;
        this->value = value;
        this->times = times;
        this->up = this->down = nullptr;
    }
    int key;
    int value;
    int times;
    shared_ptr<Node> up;
    shared_ptr<Node> down;
};

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->headList = nullptr;
    }

    void put(int key, int value) {
        if (this->capacity == 0) {
            return;
        }
        if (this->records.count(key)) {
            shared_ptr<Node> node = this->records[key];    // 通过key等到Node
            node->value = value;                // 设置新值
            node->times++;                      // 词频+1
            shared_ptr<NodeList> curNodeList = this->heads.at(node);  // 得到修改之前词频链表指针
            move(node, curNodeList);
        }
        else {
            if (this->size == this->capacity) {     // 容量已满, 先删除最不经常使用的
                shared_ptr<Node> node = nullptr;
                if (this->headList != nullptr && this->headList->tail != nullptr) {
                    node = this->headList->tail;  // 找到词频次数最少的链表的尾元素
                }
                if (this->headList != nullptr) {
                    this->headList->deleteNode(node);
                }
                modifyHeadList(this->headList);     // 调整头次频链表
                if (node != nullptr) {
                    this->records.erase(node->key);     // 节点记录删除
                }
                this->heads.erase(node);            // 词频链表记录删除
                this->size--;
            }
            shared_ptr<Node> node = shared_ptr<Node>(new Node(key, value, 1));
            if (this->headList == nullptr) {        // 词频链表的头指针为空, 即初始状态
                this->headList = shared_ptr<NodeList>(new NodeList(node));
            }
            else {
                if (this->headList->head->times == node->times) {   // 词频为1的链表存在
                    this->headList->addNodeFromHead(node);
                }
                else {                                              // 若不存在, 新建一个词频为1的链表
                    shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node));
                    newList->next = this->headList;
                    this->headList->pre = newList;
                    this->headList = newList;
                }
            }
            this->records.insert(pair<int, shared_ptr<Node>>(key, node));
            //this->records[key] = node;
            this->heads.insert(pair<shared_ptr<Node>, shared_ptr<NodeList>>(node, this->headList));
            //this->heads.insert[node] = this->headList;
            this->size++;
        }
    }

    int  get(int key) {

        if (!records.count(key)) {  // 不存在返回-1
            return -1;
        }
        shared_ptr<Node> node = this->records.at(key);
        node->times++;
        shared_ptr<NodeList> curNodeList = this->heads.at(node);  // 的到当前词频链表指针
        move(node, curNodeList);    // 把当前节点移向下一个词频链表
        return node->value;
    }

public:
    class NodeList {
    public:
        NodeList(shared_ptr<Node> node) {
            this->head = this->tail = node;
            this->pre = this->next = nullptr;
        }
        ~NodeList() {
            //while (!isEmpty()) {
            //    deleteNode(this->head);
            //}
        }

        void addNodeFromHead(shared_ptr<Node> newHead) {   // 新加链表不用调整tail指针,
            newHead->down = this->head;
            this->head->up = newHead;
            this->head = newHead;
        }

        bool isEmpty() {
            return (this->head == nullptr);
        }

        void deleteNode(shared_ptr<Node> node) {       // 调用条件式node一定在链表中
            if (this->head == this->tail) { // 都为空或者只有一个节点(node一定在链表中, 还只剩一个节点了, 没必要判断head == node)
                this->head = this->tail = nullptr;
            }
            else {
                if (node == this->head) {
                    this->head = node->down;
                    this->head->up = nullptr;
                }
                else if (node == this->tail) {
                    this->tail = node->up;
                    this->tail->down = nullptr;
                }
                else {
                    node->up->down = node->down;
                    node->down->up = node->up;
                }
                node->up = nullptr;
                node->down = nullptr;
                //delete node;
            }
        }

        shared_ptr<Node> head;         // 词频链表内头指针
        shared_ptr<Node> tail;         // 词频链表内尾指针
        shared_ptr<NodeList> pre;      // 词频链表前一个节点
        shared_ptr<NodeList> next;     // 词频链表下一个节点
    };

    void move(shared_ptr<Node> node, shared_ptr<NodeList> oldNodeList) {
        oldNodeList->deleteNode(node);

        // node进入一个新的词频链表, 找到这个新词频链表的前一个词频链表 
        shared_ptr<NodeList> preList = modifyHeadList(oldNodeList) ? oldNodeList->pre // 旧词频链表没有元素被删除了, 找旧词频链表的前一个词频链表
            : oldNodeList;     // 就链表还有元素
        shared_ptr<NodeList> nextList = oldNodeList->next; // 就词频链表下一个
        if (nextList == nullptr) {              // 原来所在词频链表是最高词频, 要去的新词频链表不存在
            shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node));
            // 前后链表重连 
            if (preList != nullptr) {
                preList->next = newList;
            }
            newList->pre = preList;
            if (this->headList == nullptr) {
                this->headList = newList;
            }
            // 词频链表map记录 
            this->heads.at(node) = newList;
        }
        else {
            if (nextList->head->times == node->times) { // 下一个链表的词频是当前节点的词频, 例如 3->4
                nextList->addNodeFromHead(node);
                this->heads.at(node) = nextList;
            }
            else {
                shared_ptr<NodeList> newList = shared_ptr<NodeList>(new NodeList(node)); // 下一个链表的词频不是当前节点的词频, 新建一个+1词频的链表,
                if (preList != nullptr) {               // 如原链表3->6, 新建一个4, 连链表3->4->6
                    preList->next = newList;
                }
                newList->pre = preList;
                newList->next = nextList;
                nextList->pre = newList;
                if (this->headList == nextList) {
                    this->headList = newList;
                }
                this->heads.at(node) = newList;
            }
        }
    }

    // 调用时机: 把一个node从NodeLists中delete掉, 判断这个链表是否还需要存在 
    bool modifyHeadList(shared_ptr<NodeList> nodeList) {
        if (nodeList != nullptr) {
            if (nodeList->isEmpty()) {
                if (this->headList == nodeList) {   // 要删除的NodeList是否为整个链表的第一个词频链表
                    // 换头操作 
                    this->headList = nodeList->next;
                    if (this->headList != nullptr) {      // 新头为空时, 表示大链表已经没有了;
                        this->headList->pre = nullptr;    // 新头不为空时, 要把新头的pre置null
                    }
                }
                else {
                    nodeList->pre->next = nodeList->next;
                    if (nodeList->next != nullptr) {
                        nodeList->next->pre = nodeList->pre;
                    }
                }
                return true;
            }
        }
        return false;                           // 删除节点后NodeLists链表不为空, 直接返回
    }

    int capacity;           // 容量
    int size;               // 当前节点
    map<int, shared_ptr<Node>> records;   // 
    map<shared_ptr<Node>, shared_ptr<NodeList>> heads;     // 当前节所在词频链表的头节点
    shared_ptr<NodeList> headList;     // 保存第一词频链表
};
*/