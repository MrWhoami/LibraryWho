//
//  main.cpp
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Whoami.
//

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin("/Users/apple/Documents/programs/cookies/test.txt");
    string a, b;
    fin >> a >> b;
    int c, d;
    sscanf(a.c_str(), "%d-%d", &c, &d);
    cout << a << ' ' << b << ' ' << c << d << endl;;
    return 0;
}
