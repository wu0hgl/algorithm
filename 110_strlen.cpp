#include <iostream>
using namespace std;

/* 不用中间变量，用递归实现，很容易看懂 */
int strlen_1(const char *str) {
    if ('\0' == *str)
        return 0;
    else
        return strlen(str + 1) + 1;
}

/* 不用中间变量，也是用递归实现，写得更简洁而已 */
int strlen_2(const char *str) {
    return *str ? (strlen(++str) + 1) : 0;
}

int strlen_3(const char * str) {
    const char *eos = str;

    while (*eos++);

    return(eos - str - 1);
}

int main() {
    const char str[] = " ";
    cout << strlen(str) << endl;;
    cout << strlen_1(str) << endl;;
    cout << strlen_2(str) << endl;;
    cout << strlen_3(str) << endl;;
}