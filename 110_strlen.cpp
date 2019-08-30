#include <iostream>
#include <assert.h>
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
    return *str ? (strlen_2(++str) + 1) : 0;
}

int strlen_3(const char * str) {
    const char *eos = str;

    while (*eos++);

    return(eos - str - 1);
}

char* strcat(char* des, const char* src) {   // const表明为输入参数 
    assert((des != NULL) && (src != NULL));
    char* address = des;
    while (*des != '\0')  // 移动到字符串末尾
        ++des;
    while (*des++ = *src++)
        ;
    return address;
}

int strcmp(const char *s1, const char *s2) {
    assert((s1 != NULL) && (s2 != NULL));
    while (*s1 == *s2)
    {
        if (*s1 == '\0')
            return 0;

        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}

int main() {
    const char str[] = "asd ";
    cout << strlen(str) << endl;;
    cout << strlen_1(str) << endl;;
    cout << strlen_2(str) << endl;;
    cout << strlen_3(str) << endl;;
}