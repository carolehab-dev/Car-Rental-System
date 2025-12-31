#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include <string>

using namespace std;

class Driver 
{
public:
    int id;
    string uname;
    string phone;
    string r;
    string nid;
    bool status;   // Available or not

    Driver();
    Driver(int id, string uname,  string phone,
        string r, string nid, bool s);

    bool isAvailable() const { return status; }
    void assign() { status = false; }
    void makeAvailable() { status = true; }
};

#endif
