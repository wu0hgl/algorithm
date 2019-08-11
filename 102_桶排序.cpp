#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    Ͱ����
*/

const int BUCKET_NUM = 10;
struct ListNode{
    explicit ListNode(int i = 0) :mData(i), mNext(NULL){}
    ~ListNode() { 
        //cout << "~ListNode" << endl; 
    }
    ListNode* mNext;
    int mData;
};

ListNode* insert(ListNode* head, int val){
    //ListNode* newNode = new ListNode(val);
    //ListNode* cur = head;
    //ListNode* pre = nullptr;
    //while (cur != nullptr && (cur->mData <= val)) {
    //    pre = cur;
    //    cur = cur->mNext;
    //}
    //newNode->mNext = cur;
    //pre->mNext = newNode;         // preΪ��ʱԽ��
    //return head;

    ListNode dummyNode;             // �൱���Լ�����һ��ͷ�ڵ�
    ListNode* pre = &dummyNode;     // �����һ������ͷ�ڵ�, Ϊ�˷�ֹ����Ϊ��ʱpre->next����Խ��
    ListNode* cur = head;
    ListNode *newNode = new ListNode(val);
    dummyNode.mNext = head;
    while (NULL != cur && cur->mData <= val){
        pre = cur;
        cur = cur->mNext;
    }
    newNode->mNext = cur;
    pre->mNext = newNode;
    return dummyNode.mNext;
}

ListNode* Merge(ListNode *head1, ListNode *head2){
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;
    while (NULL != head1 && NULL != head2){
        if (head1->mData <= head2->mData){
            dummy->mNext = head1;
            head1 = head1->mNext;
        }
        else{
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }
    if (NULL != head1) dummy->mNext = head1;
    if (NULL != head2) dummy->mNext = head2;

    return dummyNode.mNext;
}

void BucketSort(vector<int>& arr){
    vector<ListNode*> buckets(BUCKET_NUM, (ListNode*)(0));

    for (int i = 0; i<arr.size(); ++i){
        int index = arr[i] / BUCKET_NUM;
        ListNode *head = buckets.at(index);
        buckets.at(index) = insert(head, arr[i]);
    }

    ListNode *head = buckets.at(0);
    for (int i = 1; i<BUCKET_NUM; ++i){
        head = Merge(head, buckets.at(i));
    }

    for (int i = 0; i<arr.size(); ++i){
        arr[i] = head->mData;
        ListNode* temp = head;
        head = head->mNext;
        delete temp;
    }
}

int main() {
    //vector<int> arr = { 1, 2 };
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 20, 50);
    printVector(arr);
    BucketSort(arr);
    printVector(arr);

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    for (int i = 0; i < len; i++) {
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // �������������
        temp = static_cast<int>(rand() % (maxValue + 1));          // �����������
        vt.push_back(temp);
    }
}