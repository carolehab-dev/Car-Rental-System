#ifndef DRIVER_H
#define DRIVER_H
#include "Reservation.h"
#include "User.h"
#include <string>

using namespace std;

class Driver : public User
{
public:
    int id; //driver id
    string uname;
    string phone;
    string r;
    string nid;
    bool status;   // Available or not

    Driver();
    Driver(int driverId,
        int userId,
        const string& username,
        const string& phone,
        const string& role,
        const string& nid,
        bool status);
    bool login() override;
    void showMenu() override;
    bool isAvailable() const { return status; }
    void assign() { status = false; }
    void makeAvailable() { status = true; }
private:
    void viewMyShifts();
    void reportIssue();
};

#endif
