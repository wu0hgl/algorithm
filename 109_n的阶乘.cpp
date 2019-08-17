#include <iostream>  
#define MAX 40000       // 定义最多能存多少位
using namespace std;

int main(void)
{
    int n = 0;
    while (scanf("%d", &n) != EOF && (n > 0)) {
        int h = 0;  // 记录进位
        int p = 1;  // 记录当前位数
        int a[MAX] = { 0 };
        a[1] = 1;
        int i, j;
        //int j = 0;
        for (i = 2; i <= n; i++) {
            for (j = 1, h = 0; j <= p; j++) {
                a[j] = a[j] * i + h;
                h = a[j] / 10;
                a[j] = a[j] % 10;
            }
            while (h > 0) { // h不为0说明有进位
                a[j] = h % 10;
                j++;
                h = h / 10;
            }
            p = j - 1;  // 进位之后处理当前位数
        }
        for (j = p; j >= 2; j--) {
            printf("%d", a[j]);
        }
        printf("%d\n", a[1]);
    }

    return 0;
}