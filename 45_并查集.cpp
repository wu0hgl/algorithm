#include <hash_map>
#include <list>
using namespace std;

/*
    并查集
*/

class Node {
    // 任意数据类型
};

class UnionFindSet
{
public:
    UnionFindSet(list<Node> &nodes)
    {
        makeSets(nodes);
    }

    bool siSameSet(Node *a, Node *b)
    {
        return (findHead(a) == findHead(b));
    }

    void unionSet(Node *a, Node *b)
    {
        if (a == nullptr || b == nullptr)
        {
            return;
        }
        Node *aHead = findHead(a);
        Node *bHead = findHead(b);
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
    void makeSets(list<Node> &nodes)
    {
        for (auto node : nodes)
        {
            //fatherMap.insert(pair<Node*, Node*>(&node, &node));
            fatherMap[&node] = &node;
            sizeMap[&node] = 1;
        }
    }

    Node* findHead(Node *node)
    {
        Node *father = fatherMap[node];
        if (father != node)
        {
            father = findHead(father);
        }
        fatherMap[node] = father;
        return father;
    }

    hash_map<Node*, Node*> fatherMap;   // key : node, value : father
    hash_map<Node*, int>  sizeMap;
};

int main()
{
    return 0;
}