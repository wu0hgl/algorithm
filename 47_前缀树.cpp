#include <iostream>
#include <string>
using namespace std;

/*
    前缀树
*/

class TrieNode {
public:
    TrieNode() : path(0), end(0){
        memset(nexts, 0, (sizeof(TrieNode*) *  maxBranchNum));
    }

    const static int maxBranchNum = 26;
    int path;   // 到达过
    int end;    // 以该结点为结尾
    TrieNode *nexts[maxBranchNum];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        freeNode(root);
    }

    void insertStr(const string word) {
        if (word.size() == 0) {
            return;
        }
        TrieNode *node = root;
        int index = 0;
        for (size_t i = 0; i < word.size(); i++) {
            index = word[i] - 'a';
            if (node->nexts[index] == nullptr) {
                node->nexts[index] = new TrieNode();
            }
            node = node->nexts[index];
            node->path++;
        }
        node->end++;
    }

    void deleteStr(const string word) {
        if (search(word) != 0) {
            TrieNode *node = root;
            int index = 0;
            for (size_t i = 0; i < word.size(); i++) {
                index = word[i] - 'a';
                if (--node->nexts[index]->path == 0) {  // path==0, 说明底下链已经为没有共用的节点, 可以直接删除, end不需要-1
                    freeNode(node->nexts[index]);       // 释放节点
                    node->nexts[index] = nullptr;       // 必须置空, 否则析构时有问题
                    return;
                }
                node = node->nexts[index];
            }
            node->end--;
        }
    }

    int search(const string word) {
        if (word.size() == 0) {
            return 0;
        }

        TrieNode *node = root;
        int index = 0;
        for (size_t i = 0; i < word.size(); i++) {
            index = word[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }

    int prefixNumber(const string pre) {
        if (pre.size() == 0) {
            return 0;
        }
        TrieNode *node = root;
        int index = 0;
        for (size_t i = 0; i < pre.size(); i++) {
            index = pre[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->path;
    }

private:
    void freeNode(TrieNode *node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < node->maxBranchNum; i++) {
            freeNode(node->nexts[i]);
        }
        delete node;
        node = nullptr;
        return;
    }

    TrieNode *root;
};

int main() {
    Trie trie;
    
    cout << trie.search("zyb") << endl;
    trie.insertStr("zyb");
    cout << trie.search("zyb") << endl;
    trie.deleteStr("zyb");
    cout << trie.search("zyb") << endl;
    cout << "===============================" << endl;

    trie.insertStr("zyb");
    trie.insertStr("zyb");
    cout << trie.search("zyb") << endl;
    trie.deleteStr("zyb");
    cout << trie.search("zyb") << endl;
    trie.deleteStr("zyb");
    cout << trie.search("zyb") << endl;
    cout << "===============================" << endl;

    trie.insertStr("zybhaha");
    trie.insertStr("zybhehe");
    trie.insertStr("zybhij");
    trie.insertStr("zybwuwu");
    cout << trie.prefixNumber("zybh") << endl;
    cout << trie.prefixNumber("zyb") << endl;

    return 0;
}