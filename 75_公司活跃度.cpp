#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
    一个公司的上下节关系是一棵多叉树, 这个公司要举办晚会, 作为组织者已经摸清了大家的心理: 
    一个员工的直接上级如果到场, 这个员工肯定不会来. 
    每个员工都有一个活跃度的值, 决定谁来你会给这个员工发邀请函, 怎么让舞会的气氛最活跃? 
    返回最大的活跃值
*/

class Employee {
public:
    int happy;  // 员工活跃值
    list<Employee*> subordinates;
    Employee(int happy) {
        this->happy = happy;
    }
};

class ReturnData {
public:
    int yesHeadMax; // 树的头结点来的情况下, 整棵树最大受益
    int noHeadMax;  // 树的头结点不来的情况下, 整棵树的最大受益
    ReturnData(int yesHeadMax, int noHeadMax) {
        this->yesHeadMax = yesHeadMax;
        this->noHeadMax = noHeadMax;
    }
};

ReturnData process(Employee* X) {
    int yesX = X->happy;    // X来的情况
    int noX = 0;            // X不来的情况

    if (X->subordinates.empty()) {       // X没有直接下属
        return ReturnData(yesX, noX);   
    }
    else {
        for (auto next : X->subordinates) { 
            // 递归调用process, 得到以next为 头结点 的子树
            // 在next 来 和 不来 的情况下分别获得的最大受益
            ReturnData subTreeInfo = process(next);
            yesX += subTreeInfo.noHeadMax;                              // 领导来, 员工肯定不来
            noX += max(subTreeInfo.yesHeadMax, subTreeInfo.noHeadMax);  // 领导不来时, 员工分为 来 或 不来 取最大值
        }
        return ReturnData(yesX, noX);
    }
}
int getMaxHappy(Employee* boss) {
    ReturnData allTreeInfo = process(boss);

    return max(allTreeInfo.yesHeadMax, allTreeInfo.noHeadMax);
}

int main() {
    //vector<vector<int>> = { { 1, 8 }, { 1, 9 }, { 1, 10 } };
    Employee boss(1);
    Employee A(50);
    Employee B(40);
    boss.subordinates.push_back(&A);
    boss.subordinates.push_back(&B);
    Employee C(6);
    Employee D(7);
    Employee E(9);
    A.subordinates.push_back(&C);
    A.subordinates.push_back(&D);
    A.subordinates.push_back(&E);
    Employee F(3);
    Employee G(10);
    B.subordinates.push_back(&F);
    B.subordinates.push_back(&G);

    cout << getMaxHappy(&boss) << endl;

    return 0;
}