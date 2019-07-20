#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    一些项目要占用一个会议室宣讲, 会议室不能同时容纳两个项目的宣讲. 
    给你每一个项目开始的时间和结束的时间(给你一个数组, 里面是一个个具体的项目), 安排宣讲的日程.
    要求会议室进行的宣讲的场次最多. 返回这个最多的宣讲场次。
*/

class Program {
public:
    Program(int start, int end) : start(start), end(end) {}
    int start;
    int end;
};
void printPrograms(vector<Program*> &programs);

bool ProgramComparator(Program *p1, Program *p2) {
    return p1->end < p2->end;
}

int bestArray(vector<Program*> &programs, int cur) {
    sort(programs.begin(), programs.end(), ProgramComparator);
    printPrograms(programs);
    int res = 0;
    for (size_t i = 0; i < programs.size(); i++) {
        if (cur <= programs[i]->start) {
            res++;
            cout << "(" << programs[i]->start << "," << programs[i]->end << ") ";
            cur = programs[i]->end;
        }
    }

    return res;
}

int main() {
    vector<Program*> arr;
    Program p1(4, 9);
    arr.push_back(&p1);
    Program p2(2, 6);
    arr.push_back(&p2);
    Program p3(1, 4);
    arr.push_back(&p3);
    Program p4(4, 5);
    arr.push_back(&p4);
    Program p5(6, 8);
    arr.push_back(&p5);


    cout << bestArray(arr, 0) << endl;;

    return 0;
}

void printPrograms(vector<Program*> &programs) {
    for (size_t i = 0; i < programs.size(); i++) {
        cout << "(" << programs[i]->start << "," << programs[i]->end << ") ";
    }
    cout << endl;
}