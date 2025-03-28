#ifndef PANEL_H
#define PANEL_H
#include <iostream>

using namespace std;

class Panel{
    public:
    string name;

    Panel(string name) {
        this->name =name;
    }
    string getName() {
        return name;
    }
};

#endif