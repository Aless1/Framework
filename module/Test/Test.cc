#include "Test.h"
#include <iostream>

using namespace std;

bool Test::Init() {
    cout << "Test Init" << endl;
    return true;
}

bool Test::Launch() {
    cout << "Test Launch" << endl;
    return true;
}

bool Test::Destory() {
    cout << "Test Destory" << endl;
    return true;
}
