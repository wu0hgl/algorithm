#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

/*
    给定一个没有重复的整型数组arr, 初始认为arr中每一个数都各自是一个单独的集合. 
    设计一种结构, 提供isSameSet查询是否处于一个集合与unionSet合并集合. 
    要求: 如果调用isSameSet与unionSet的总次数逼近或者超过O(N), 做到单次调用isSameSet或unionSet方法的平均时间复杂度为O(1)
*/

template<typename T>
class Node {
    // 任意数据类型
public:
    T value;
    Node(T value)
    { this->value = value; }
};

template<typename T>
class UnionFindSet
{
public:
    UnionFindSet(list<Node<T>*> &nodes)
    {
        makeSets(nodes);
    }

    bool isSameSet(Node<T>* a, Node<T>* b)
    {
        return (findHead(a) == findHead(b));
    }

    void unionSet(Node<T>* a, Node<T>* b)
    {
        if (a == nullptr || b == nullptr)
        {
            return;
        }
        Node<T>* aHead = findHead(a);
        Node<T>* bHead = findHead(b);
        if (aHead != bHead)
        {
            int aSetSize = sizeMap.at(aHead);
            int bSetSize = sizeMap.at(bHead);
            if (aSetSize <= bSetSize)
            {
                fatherMap[aHead] = bHead;
                sizeMap[bHead] = aSetSize + bSetSize;
            }
            else
            {
                fatherMap[bHead] = aHead;
                sizeMap[aHead] = aSetSize + bSetSize;
            }
        }
    }

private:
    void makeSets(list<Node<T>*> &nodes)    // 初始化并查集
    {
        fatherMap.clear();
        sizeMap.clear();
        for (auto node : nodes)
        {
            fatherMap[node] = node;
            sizeMap[node] = 1;
        }
    }

    Node<T>* findHead(Node<T> *node)        // 查找头结点
    {
        Node<T>* father = fatherMap[node];
        if (father != node)
        {
            father = findHead(father);
        }
        fatherMap[node] = father;
        return father;
    }

    unordered_map<Node<T>*, Node<T>*> fatherMap;    // key : node, value : father
    unordered_map<Node<T>*, int>  sizeMap;          // 合并后并查集的大小
};

int main()
{
    Node<string> n1("n1");
    Node<string> n2("n2");
    Node<string> n3("n3");
    Node<string> n4("n4");
    list<Node<string>*> lt;
    lt.push_back(&n1);
    lt.push_back(&n2);
    lt.push_back(&n3);
    
    UnionFindSet<string> uSet(lt);

    if (uSet.isSameSet(&n1, &n2)) {
        cout << n1.value.c_str() << " and " << n2.value.c_str() << " is the same set" << endl;
    }
    else {
        cout << n1.value.c_str() << " and " << n2.value.c_str() << " is not the same set" << endl;
    }
    cout << "=====================================" << endl;

    cout << "union n1 and n2" << endl;
    uSet.unionSet(&n1, &n2);
    cout << "=====================================" << endl;

    if (uSet.isSameSet(&n1, &n2)) {
        cout << n1.value.c_str() << " and " << n2.value.c_str() << " is the same set" << endl;
    }
    else {
        cout << n1.value.c_str() << " and " << n2.value.c_str() << " is not the same set" << endl;
    }
    cout << "=====================================" << endl;

    if (uSet.isSameSet(&n1, &n3)) {
        cout << n1.value.c_str() << " and " << n3.value.c_str() << " is the same set" << endl;
    }
    else {
        cout << n1.value.c_str() << " and " << n3.value.c_str() << " is not the same set" << endl;
    }
    cout << "=====================================" << endl;

    cout << "union n2 and n3" << endl;
    uSet.unionSet(&n2, &n3);
    cout << "=====================================" << endl;

    if (uSet.isSameSet(&n1, &n3)) {
        cout << n1.value.c_str() << " and " << n3.value.c_str() << " is the same set" << endl;
    }
    else {
        cout << n1.value.c_str() << " and " << n3.value.c_str() << " is not the same set" << endl;
    }

    //uSet.unionSet(&n2, &n4);  // &n4不在并查集中, 报错

    return 0;
}