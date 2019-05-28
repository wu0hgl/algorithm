#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdio.h>
using namespace std;

bool myCompare(string str1, string str2) {
    return ((str1 + str2).compare(str2 + str1) < 0);
}

string lowestString(vector<string> arr) {
    sort(arr.begin(), arr.end(), myCompare);
    string res;
    for (size_t i = 0; i < arr.size(); i++) {
        res += arr[i];
    }
    return res;
}


int main() {
    vector<string> arr;
    arr.push_back("b");
    arr.push_back("ba");
    //arr.push_back("jibw");
    //arr.push_back("ji");
    //arr.push_back("jp");
    //arr.push_back("bw");
    //arr.push_back("jibw");

    printf("%s\n", lowestString(arr).c_str());

    return 0;
}