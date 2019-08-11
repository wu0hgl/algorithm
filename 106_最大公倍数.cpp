#include <iostream>
using namespace std;

/*
    最大公约数/最小公倍数
*/

int func(int a, int b){

    if (b == 0) {
        return a;
    }

    return maxyue(b, a%b);
}

int main(){
    int a, b;
    while (cin >> a >> b){
        cout << a * b / func(a, b) << endl;
    }
    return 0;
}