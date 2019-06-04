#include <iostream>
using namespace std;

/*
    母牛每年生一只母牛, 新出生的母牛成长三年后也能每年生一只母牛, 假设不会死. 
    求N年后, 母牛的数量
    如果每只母牛只能活10年, 求N年后母牛的数量(暂无答案)
*/

/* 递归版 */
int cowNumber_1(int n) {
    if (n < 1) {
        return 0;
    }
    if ((n == 1) || (n == 2) || (n == 3)) {
        return n;
    }
    return (cowNumber_1(n - 1) + cowNumber_1(n - 3));
}

/* 非递归版 */
int cowNumber_2(int n) {
    if (n < 1) {
        return 0;
    }
    if ((n == 1) || (n == 2) || (n == 3)) {
        return n;
    }
    int res = 3;
    int pre = 2;
    int prepre = 1;
    int tmp1 = 0;
    int tmp2 = 0;
    for (int i = 4; i <= n; i++) {
        tmp1 = res;
        tmp2 = pre;
        res = res + prepre;
        pre = tmp1;
        prepre = tmp2;
    }
    return res;
}

int main() {

    cout << cowNumber_1(10) << endl;
    cout << cowNumber_2(10) << endl;

    return 0;
}