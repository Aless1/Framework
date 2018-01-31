#include "Event.h"
#include <iostream>

using namespace std;

bool Event::Init() {
    cout << "Event Init" << endl;
    return true;
}

bool Event::Launch() {
    cout << "Event Launch" << endl;
    return true;
}

bool Event::Destory() {
    cout << "Event Destory" << endl;
    return true;
}