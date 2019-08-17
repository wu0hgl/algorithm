#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
void*Memcpy(void *dst, const void *src, size_t size);
void* my_memcpy(void *dst, const void* src, size_t n);

int main() {
    char buf[100] = "abcdefghijk";
    printf("%s\n", buf);
    //memcpy(buf + 2, buf, 5);
    Memcpy(buf + 2, buf, 5);
    //my_memcpy(buf + 2, buf, 5);
    printf("%s\n", buf + 2);

    return 0;
}

// 32位总线可以每次复制一个int，64位总线可以一次性复制long long。所以要分成int和char类型来处理，优先int型处理方式。
void* my_memcpy(void *dst, const void* src, size_t n) {
    assert(dst != NULL && src != NULL && n >= 0);

    void *ret = dst;  //avoid dst move to back

    int wordnum = n >> 2;   //int，x/4
    int slice = n & 3;      //char,x%4

    if (dst <= src || (char*)src + n <= (char*)dst){    //'=' is ok, because the max is src+n-1
        while (wordnum--){
            *(int *)dst = *(int *)src;
            dst = (int *)dst + 1;
            src = (int *)src + 1;
        }
        while (slice--){
            //*(char* )dst++ = *(char *)src++;   //it will get warning.ISO C++ forbids incrementing a pointer of type ‘const void*’
            *(char *)dst = *(char *)src;
            dst = (char *)dst + 1;
            src = (char *)src + 1;
        }
    }
    else{
        dst = (char *)dst + n;
        src = (char *)src + n;
        while (wordnum--){
            dst = (int *)dst - 1;
            src = (int *)src - 1;
            *(int *)dst = *(int *)src;
        }
        while (slice--){
            dst = (char *)dst - 1;
            src = (char *)src - 1;
            *(char *)dst = *(char *)src;
        }
    }

    return ret;
}

void*Memcpy(void *dst, const void *src, size_t size) {
    char *psrc;
    char *pdst;

    if (NULL == dst || NULL == src) {
        return NULL;
    }

    if ((src < dst) && (char *)src + size >(char *)dst){    // 自后向前拷贝
        psrc = (char *)src + size - 1;
        pdst = (char *)dst + size - 1;
        while (size--) {
            *pdst-- = *psrc--;
        }
    }
    else {
        psrc = (char *)src;
        pdst = (char *)dst;
        while (size--) {
            *pdst++ = *psrc++;
        }
    }

    return dst;
}