#include <iostream>
#include <string>
#include <hash_map>
#include <exception>
using namespace std;

/*
    设计一种缓存结构, 该结构在构造时确定大小, 假设大小为K, 并有两个功能: 
        (1)set(key,value): 将记录(key,value)插入该结构; (2)get(key): 返回key对应的value值
    要求: 
        (1)set和get方法的时间复杂度为O(1); 
        (2)某个key的set或get操作一旦发生, 认为这个key的记录成了最经常使用的; 
        (3)当缓存的大小超过K时, 移除最不经常使用的记录, 即set或get最久远的
*/

template<typename V>
class Node {
public:
    Node(V value) {
        this->value = value;
        pre = nullptr;
        next = nullptr;
    }
    V value;
    Node<V> *pre;
    Node<V> *next;
};

template<typename V>
class NodeDoubleLinkedList {
public:
    NodeDoubleLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void addNode(Node<V>* newNode) {
        if (newNode == nullptr) {
            return;
        }
        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        }
        else {
            newNode->pre = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }

    /* 调用条件式node一定在链表中 */
    void moveNodeToTail(Node<V>* node) {
        if (node == this->tail) {       // 移动的节点是尾节点
            return;
        }

        if (node == this->head) {       // 移动的节点是头节点
            this->head = node->next;
            this->head->pre = nullptr;
        }
        else {                          // 移动的节点是中间节点
            node->pre->next = node->next;
            node->next->pre = node->pre;
        }
        /* 处理尾节点 */
        node->pre = this->tail;
        node->next = nullptr;
        this->tail->next = node;
        this->tail = node;
    }

    Node<V>* removeHead() {
        if (this->head == nullptr) {
            return nullptr;
        }

        Node<V> *res = this->head;
        if (this->tail == this->head) {
            this->tail = this->head = nullptr;
        }
        else {
            this->head = res->next;
            this->head->pre = nullptr;
            res->next = nullptr;
        }

        return res;
    }

    bool isEmpty() {
        return head == nullptr;
    }

private:
    Node<V> *head;
    Node<V> *tail;
};

template<typename K, typename V>
class MyCache {
public:
    MyCache(int capacity) {
        if (capacity < 1) {
            exit(-1);
        }
        this->capacity = capacity;
    }

    ~MyCache() {
        while (!this->nodeList.isEmpty()) {
            removeMostUnusedCache();
        }
    }

    V get(K key) {
        if (this->keyNodeMap.count(key)) {
            Node<V> *res = this->keyNodeMap[key];
            this->nodeList.moveNodeToTail(res);
            return res->value;
        }
        else {
            throw "Key is wrong!";
        }
    }

    void set(K key, V value) {
        if (this->keyNodeMap.count(key)) {
            Node<V> *node = this->keyNodeMap[key];
            node->value = value;
            this->nodeList.moveNodeToTail(node);
        }
        else {
            Node<V> *newNode = new Node<V>(value);
            this->keyNodeMap[key] = newNode;
            this->nodeKeyMap[newNode] = key;
            this->nodeList.addNode(newNode);
            if (this->keyNodeMap.size() == this->capacity + 1) {
                this->removeMostUnusedCache();
            }
        }
    }

    void removeMostUnusedCache() {
        Node<V> *removeNode = this->nodeList.removeHead();
        K removeKey = this->nodeKeyMap[removeNode];
        this->nodeKeyMap.erase(removeNode);
        this->keyNodeMap.erase(removeKey);
        delete removeNode;
    }

private:
    int capacity;
    hash_map<K, Node<V>*>    keyNodeMap;    // key: 类型, value: 内存地址
    hash_map<Node<V>*, K>    nodeKeyMap;    // key: 内存地址, value: 类型
    NodeDoubleLinkedList<V>  nodeList;
};

void func() {
    MyCache<string, string> testCache(3);

    testCache.set("A", "1");
    testCache.set("B", "2");
    testCache.set("C", "3");

    try {
        cout << testCache.get("B") << endl;
        cout << testCache.get("A") << endl;
        cout << testCache.get("C") << endl;
        cout << testCache.get("D") << endl; // D未插入LRU中, 异常报错
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }

    cout << "===================" << endl;

    testCache.set("D", "4");
    testCache.set("C", "4");
    try {
        cout << testCache.get("D") << endl;
        cout << testCache.get("C") << endl;
        cout << testCache.get("B") << endl; // 此时B已经被移除了, 异常报错
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}

int main() {

    func();
    return 0;
}