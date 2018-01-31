#include "Test.h"
#include <iostream>

using namespace std;

bool Test::Init() {
    cout << "Test Init" << endl;
    return true;
}

bool Test::Launch() {
    cout << "Test Launch" << endl;
    tcore::GetCoreInstance()->StartTcpServer("0.0.0.0", 8089, new TestServer());
    // tcore::GetCoreInstance()
    return true;
}

bool Test::Destory() {
    cout << "Test Destory" << endl;
    return true;
}