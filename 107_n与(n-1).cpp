#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

void func_1() {         // 判断一个数是否是2的幂
    int n, count = 0;
    cin >> n;
    if ((n > 0) && (!(n & (n - 1))))
        cout << "这个数是2的幂" << endl;
    else
        cout << "这个数不是2的幂" << endl;
}

void func_2() {         // 统计一个数二进制表达式中1的个数
    int n, count = 0;
    cin >> n;
    while (n > 0)
    {
        count++;
        n &= (n - 1);
    }
    cout << count << endl;
}

int main()
{
    func_1();
    func_2();
    return 0;
}
