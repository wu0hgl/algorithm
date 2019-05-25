#include <iostream>
#include <string>
#include <hash_map>
#include <ctime>
using namespace std;

class RandomPool
{
public:
    RandomPool()
    {
        this->size = 0;
    }
    void insert(string k) 
    {
        if ((keyIndexMap.find(k) == keyIndexMap.end())) 
        {
            keyIndexMap[k] = size;
            indexKeyMap[size] = k;
            size++;
        }
    }

    string getRandom()
    {
        if (this->size == 0) 
        {
            return nullptr;
        }
        int randomIndex = static_cast<int> (rand() % this->size);
        return indexKeyMap[randomIndex];
    }

    void remove(string key) 
    {
        if ((keyIndexMap.find(key) != keyIndexMap.end()))
        {
            int deleteIndex = keyIndexMap[key];

            int lastIndex = --this->size;               // 最后插入元素的index
            string lastKey = indexKeyMap[lastIndex];

            keyIndexMap[lastKey] = deleteIndex;         // 修改最后一个key对应的index
            indexKeyMap[deleteIndex] = lastKey;         // 填坑

            keyIndexMap.erase(key);
            indexKeyMap.erase(lastIndex);
        }
    }

private:
    hash_map<string, int> keyIndexMap;
    hash_map<int, string> indexKeyMap;
    int size;
};

int main()
{
    srand(static_cast<int>(time(NULL)));
    RandomPool pool;
    pool.insert("zyb");
    pool.insert("haha");
    pool.insert("hehe");
    pool.remove("hehe");
    pool.remove("haha");
    printf("%s\n", pool.getRandom().c_str());
    printf("%s\n", pool.getRandom().c_str());
    printf("%s\n", pool.getRandom().c_str());
    return 0;
}