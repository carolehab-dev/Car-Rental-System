#include "Driver.h"

// Default constructor
Driver::Driver() 
{
    status = true;
}

// Parameterized constructor
Driver::Driver(int id, string uname, string phone,
    string r, string nid, bool s)
    
{
    status = s;
}