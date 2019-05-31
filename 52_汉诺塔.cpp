#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

void moveLeftToRight(int N);
void moveRightToLeft(int N);
void moveLeftToMid(int N);
void moveMidToLeft(int N);
void moveRightToMid(int N);
void moveMidToRight(int N);

/*
    汉诺塔
*/

void process(int N, string from, string to, string help) {
    if (N == 1) {
        printf("Move %d from %s to %s\n", N, from.c_str(), to.c_str());
    }
    else {
        process(N - 1, from, help, to);     // 借助to, 从from移到help上
        printf("Move %d from %s to %s\n", N, from.c_str(), to.c_str());
        process(N - 1, help, to, from);     // 借助from, 从help移动到to上
    }
}

void moveLeftToRight(int N) {
    if (N == 1) {
        //System.out.println("move 1 from left to right");
        printf("move 1 from left to right\n");
    }
    moveLeftToMid(N - 1);
    //System.out.println("move " + N + "from left to right");
    printf("move %dfrome left to right\n", N);
    moveMidToRight(N - 1);
}

void moveRightToLeft(int N) {

}

void moveLeftToMid(int N) {
    if (N == 1) {
        //System.out.println("move 1 from left to mid");
        printf("move 1 from left to mid\n");
    }
    moveLeftToRight(N - 1);
    //System.out.println("move " + N + "from left to mid");
    printf("move %dfrom left to mid\n", N);
    moveRightToMid(N - 1);
}

void moveMidToLeft(int N) {

}

void moveRightToMid(int N) {

}

void moveMidToRight(int N) {
    if (N == 1) {
        //System.out.println("move 1 from mid to right");
        printf("move 1 from mid to right\n");
    }
    moveMidToLeft(N - 1);
    //System.out.println("move " + N + "from mid to right");
    printf("move %dfrom mid to right\n", N);
    moveLeftToRight(N - 1);
}

int main() {
    process(3, "左", "右", "中");

    return 0;
}